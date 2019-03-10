#include "libft.h"
#include "lem_in.h"

/*
** And edge is considered legal if it has not been visited on the current
** BFS iteration and if there is no hop from current node to next_node
** (going in the reverse direction in an existing path is allowed)
*/

/*
** TODO if edge is a dead-end don't add it
*/


static uint8_t		legal_edge(t_node *node, t_node *next_node, int flow)
{
	t_list			*hop;
	t_node			*hop_to;

	hop = node->hop_data;
	if (hop)
		hop_to = ((t_hop*)(hop->content))->hop_to;

	//Check if vertex has already been touched in this BFS
	if (next_node->bfs_data.last_visited == flow)
		return (0);
	//Check if edge not in path
	if (hop && hop_to != NULL)
	{
		//If edge is part of path but we're going back up the path,
		//it's a legal move
		if (next_node->hop_data
				&& ((t_hop*)(next_node->hop_data->content))->hop_to == node)
			return (1);
		else
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

static uint8_t		check_node(t_wrap *wrap, t_node *parent, t_node *node,
									int flow)
{
	node->bfs_data.last_visited = flow;
	node->bfs_data.parent = parent;
	if (node->type == END)
	{
		build_path(wrap, node);
		del_all(wrap, &(wrap->bfs_state->level));
		del_all(wrap, &(wrap->bfs_state->frontier));
		return (1);
	}
	return (0);
}

/*
** End of loop reset
*/

static uint8_t		update_level(t_list **level, t_list **frontier)
{
	*level = *frontier;
	*frontier = NULL;
	if (*level == NULL)
		return (0);
	return (1);
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
	t_node			*node;
	t_node			*next_node;

	ft_bzero(&bfs, sizeof(t_bfs));
	wrap->bfs_state = &bfs;
	add_start(wrap, (void*)source, &(bfs.frontier));
	while (update_level(&(bfs.level), &(bfs.frontier)))
		while (bfs.level)
		{
			node = (t_node*)(bfs.level->content);
			edge = node->edges;
			while (edge)
			{
				next_node = (t_node*)(edge->content);
				if (legal_edge(node, next_node, flow))
				{
					if (check_node(wrap, node, next_node, flow))
						break;
					add_start(wrap, next_node, &(bfs.frontier));
				}
				edge = edge->next;
			}
			del_start(wrap, &(bfs.level));
		}
} // |!| 26 Lines
