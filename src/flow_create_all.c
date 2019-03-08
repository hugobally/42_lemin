#include "lem_in.h"

void		flow_create_all(t_wrap *wrap, t_graph *graph)
{
	t_list	*path;

	while ((path = flow_find_new(wrap, graph->source, graph->sink)))
	{
		graph->flow_max++;
//		flow_update_nodes(wrap, graph, path);
//		flow_update_gates(wrap, graph);
		del_all(wrap, &path);
	}
}
