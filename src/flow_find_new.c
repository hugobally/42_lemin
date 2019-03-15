#include "libft.h"
#include "lem_in.h"
#include <unistd.h>//DEBUG

/*
** And edge is considered legal if it has not been visited on the current
** BFS iteration and if there is no hop from current node to next_node
** (going in the reverse direction in an existing path is allowed)
*/

/*
** TODO
** - if edge is a dead-end don't add it
** - extract hop_get 
** - handle node already visited when backtracking
** - there should be no reverse edges between source and gates and 
** 	 between sink and sink parents
*/

/* TODO 
** ** Check for legal edge
** 1. if child has already been visited, or if we're going to source or from sink -> reject
** 2. if we know we're on an existing path -> accept
** 3. if child has a hop that goes to parent : we're on an existing path -> accept
** 4. if parent has any hop and we're not at start going to a fresh child -> reject
** 5. accept
*/

static uint8_t		legal_edge(t_node *parent, t_node *child, int flow)
{
	t_list			*parent_hop;
	t_list			*child_hop;

	parent_hop = parent->hop_data;
	child_hop = child->hop_data;

	if (child->last_visited == flow
			|| child->type == START
			|| parent->type == END)
		return (0);
	if (parent->residual == flow)
	{
		if (hop_get(child_hop) == parent)
		{
			child->residual = flow;
		}
		return (1);
	}
	if (hop_get(child_hop) == parent)
	{
		child->residual = flow;
		return (1);
	}
	if (hop_get(parent_hop))
	{
		if (parent->type == START && !(hop_get(child_hop)))
			return (1);
		return (0);
	}
	return (1);
}

static void			check_node(t_wrap *wrap, t_node *parent, t_node *child,
									int flow)
{
	if (child->type == END)
	{
		if (parent->type == START)
			child->last_visited = flow;
		add_start(wrap, (void*)parent, &(wrap->bfs_output)); 
	}
	else
	{
		child->last_visited = flow;
		child->parent = parent;
	}
}

/*
** BFS : starting from source, nodes are added to the 'level' list.
** (level 1 is all nodes 1 hop away from the source, level 2 is 2 hops away etc)
** Every node that is reachable from the current level, has not been visited,
** and is legal in the residual graph (see Ford-Fulkerson), becomes part of the
** 'frontier' list. Then the frontier becomes the level.
** Stops when the sink node is found or all nodes have been explored.
** If the sink was found, the resulting shortest path from source to sink
** is stored in wrap->bfs_output
*/

void				flow_find_new(t_wrap *wrap, int flow, t_node *source)
{
	t_bfs			bfs;
	t_list			*edge;
	t_node			*parent;
	t_node			*child;

	ft_bzero(&bfs, sizeof(t_bfs));
	wrap->bfs_state = &bfs;
	add_start(wrap, (void*)source, &(bfs.frontier));
	while (update_level(&(bfs.level), &(bfs.frontier)))
		while (bfs.level)
		{
			parent = (t_node*)(bfs.level->content);
			edge = parent->edges;
			while (edge)
			{
				child = (t_node*)(edge->content);
				if (legal_edge(parent, child, flow))
				{
					check_node(wrap, parent, child, flow);
					add_start(wrap, child, &(bfs.frontier));
				}
				edge = edge->next;
			}
			del_start(wrap, &(bfs.level));
		}
}
