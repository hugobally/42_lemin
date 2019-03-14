#include "libft.h"
#include "lem_in.h"

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

/* ** Check for legal edge
*/

static uint8_t		legal_edge(t_node *parent, t_node *child, int flow)
{
	t_list			*hop;
	t_list			*next_hop;

	hop = parent->hop_data;
	next_hop = child->hop_data;

	if (child->bfs_data.last_visited == flow
			|| child->type == START || parent->type == END)
		return (0);
	if (parent->bfs_data.residual == flow)
		return (1);
	if (hop_get(next_hop) == parent)
	{
		child->bfs_data.residual = flow;
		return (1);
	}
	if (hop_get(hop))
	{
		if (parent->type == START && !(hop_get(next_hop)))
			return (1);
		return (0);
	}
	return (1);
}

/*
** Updates node data with check_node
** If sink is found, a path is built from parent pointers and
** level + frontier are discarded
*/

static void			build_path(t_wrap *wrap, t_node *start)
{
	t_node			*node;
	t_list			*path;

	path = NULL;
	node = start;
	while (node)
	{
		add_start(wrap, (void*)node, &path);
		node = node->bfs_data.parent;
	}
	if (wrap->bfs_output)
		del_all(wrap, &(wrap->bfs_output));
	wrap->bfs_output = path;
}

static uint8_t		check_node(t_wrap *wrap, t_node *parent, t_node *child,
									int flow)
{
	child->bfs_data.last_visited = flow;
	child->bfs_data.parent = parent;
	if (child->type == END)
	{
		build_path(wrap, child);
		del_all(wrap, &(wrap->bfs_state->level));
		del_all(wrap, &(wrap->bfs_state->frontier));
		return (1);
	}
	return (0);
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
					if (check_node(wrap, parent, child, flow))
						break;
					add_start(wrap, child, &(bfs.frontier));
				}
				edge = edge->next;
			}
			del_start(wrap, &(bfs.level));
		}
}
