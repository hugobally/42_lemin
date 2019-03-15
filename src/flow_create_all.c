#include "lem_in.h"
#include "libft.h"//DEBUG for printf

/*
** Updates node data with check_node
** If sink is found, a path is built from parent pointers and
** level + frontier are discarded
*/

void				build_path(t_wrap *wrap, t_graph *graph, t_node *start)
{
	t_node			*node;
	t_list			**output;

	if (start)
	{
		del_all(wrap, &(wrap->bfs_output));
		output = &(wrap->bfs_output);
		node = graph->sink;
		node->parent = start;
		while (node)
		{
			add_start(wrap, (void*)node, output);
			node = node->parent;
		}
	}
}

int					get_path_value(t_node *path_start)
{
	t_node			*node;
	int				value;

	value = 1;
	node = path_start;
	while (node && node->parent)
	{
		value += hop_get(node->hop_data) ==node->parent ? -1 : 1;
		node = node->parent;
	}
	return (value);
}


void				choose_best_path(t_wrap *wrap, t_graph *graph,
										t_list *candidate)
{
	int				best_value;
	int				value;
	t_node			*node;
	t_node			*best_path;

	best_value = 0;
	best_path = NULL;
	while (candidate)
	{
		node = (t_node*)(candidate->content);
		value = get_path_value(node);
		if (best_value == 0 || value < best_value)
		{
			best_value = value;
			best_path = node;
		}
		candidate = candidate->next;
	}
	build_path(wrap, graph, best_path);
}

/*
** Wrapper
*/

void				flow_find_wrapper(t_wrap *wrap, t_graph *graph)
{
	del_all(wrap, &(wrap->bfs_output));
	graph->source->last_visited = graph->flow_max;
	flow_find_new(wrap, graph->flow_max, graph->source);
	wrap->bfs_state = NULL;
	choose_best_path(wrap, graph, wrap->bfs_output);
}

/*
** Implementation of Edmonds-Karp [max flow using iterative BFS]
** - find the next augmenting path using BFS (flow_find_new)
** - update graph using new path in (flow_update_nodes)
** - calculate and store length of new/updated paths (flow_update_gates)
*/

void				flow_create_all(t_wrap *wrap, t_graph *graph)
{
	graph->flow_max = 1;
	flow_find_wrapper(wrap, graph);
	while (wrap->bfs_output)
	{
		flow_update_nodes(wrap, wrap->bfs_output, graph->flow_max);
		flow_update_gates(wrap, graph->source, graph->flow_max);
		flow_simulate(graph, graph->source, graph->flow_max);
		graph->flow_max++;
		flow_find_wrapper(wrap, graph);
	}
}
