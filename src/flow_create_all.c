#include "lem_in.h"

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
	graph->flow_max = 1;
	flow_find_wrapper(wrap, graph);
	while (wrap->bfs_output)
	{
//		flow_update_nodes(wrap, graph, path);
//		flow_update_gates(wrap, graph);
//		del bfs_output
		graph->flow_max++;
		flow_find_wrapper(wrap, graph);
	}
}
