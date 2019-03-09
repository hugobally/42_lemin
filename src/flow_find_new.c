#include "libft.h"
#include "lem_in.h"

static uint8_t		update_level(t_list **level, t_list **frontier)
{
	*level = *frontier;
	*frontier = NULL;
	if (*level == NULL)
		return (0);
	return (1);
}

static uint8_t		check_node(t_wrap *wrap, t_node *parent, t_node *node,
									int flow)
{
	node->bfs_data.last_visited = flow;
	node->bfs_data.parent = parent;
	if (node->type == END)
	{
		del_all(wrap, &(wrap->bfs_state->level));
		del_all(wrap, &(wrap->bfs_state->frontier));
		return (1);
	}
	return (0);
}

static uint8_t		legal_edge(t_node *node, t_node *next_node, int flow)
{
	t_list			*hop;

	hop = node->hops_data;

	if (next_node->bfs_data.last_visited == flow
			|| (hop && (t_node*)(hop->content) == next_node))
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
