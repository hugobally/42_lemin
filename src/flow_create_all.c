#include "lem_in.h"

/*
** DEBUG
*/

#include "libft.h"
void		print_path(t_node *start)
{
	t_node	*node;

	node = start;
	while (node)
	{
		if (node->type != END)
			ft_printf("%s -> ", node->name);
		else
			ft_printf("%s\n", node->name);
		if (node->hop_data)
			node = ((t_hop*)(node->hop_data->content))->hop_to;
		else
			node = NULL;
	}
}

/*
** Wrapper
*/

void			flow_find_wrapper(t_wrap *wrap, t_graph *graph)
{
	graph->source->bfs_data.last_visited = graph->flow_max;
	flow_find_new(wrap, graph->flow_max, graph->source);
}

/*
** Implementation of Edmonds-Karp [max flow using iterative BFS]
** - find the next augmenting path using BFS (flow_find_new)
** - update graph using new path in (flow_update_nodes)
** - calculate and store length of new/updated paths (flow_update_gates)
*/

void			flow_create_all(t_wrap *wrap, t_graph *graph)
{

	t_list *node;
	graph->flow_max = 1;
	flow_find_wrapper(wrap, graph);
	while (wrap->bfs_output)
	{
		flow_update_nodes(wrap, wrap->bfs_output, graph->flow_max);
//		flow_update_gates(wrap, graph, graph->flow_max);
		del_all(wrap, &(wrap->bfs_output));
		//
		//DEBUG 
		node = graph->source->hop_data;
		while (node)
		{
			print_path(((t_hop*)(node->content))->hop_to);
			node = node->next;
		}
		ft_printf("-----\n");
		//END DEBUG
		//
		graph->flow_max++;
		flow_find_wrapper(wrap, graph);
	}
}
