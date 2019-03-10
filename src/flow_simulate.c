#include "libft.h"
#include "lem_in.h"

t_gate_data 		*get_data(t_list *data_list, int flow)
{
	t_list			*elem;
	t_gate_data		*data;

	elem = data_list;
	while (elem)
	{
		data = (t_gate_data*)(elem->content);
		if (data->flow == flow)
			return (data);
		elem = elem->next;
	}
	return (NULL);
}

t_node				*get_best_gate(t_node *source, int flow)
{
	void			*best_gate;
	int				best_len;
	t_list			*edge;
	t_gate_data		*data;

	edge = source->edges;
	best_len = -1;
	while (edge)
	{
		data = get_data(((t_node*)(edge->content))->gate_data, flow);
		if (data && (best_len < 0
				|| data->path_len + data->crowding < best_len))
		{
			best_gate = edge->content;
			best_len = data->path_len + data->crowding;
		}
		edge = edge->next;
	}
	return ((t_node*)best_gate);
}

int					get_cost(t_gate_data *data)
{
	if (data && data->crowding != 0)
		return (data->path_len + data->crowding - 1);
	return (0);
}

void				flow_simulate(t_graph *graph, t_node *source, int flow)
{
	int				remaining;
	int				cost;
	int				max_cost;
	t_list			*edge;

	remaining = graph->source_capacity;
	while (remaining--)
		get_data(get_best_gate(source, flow)->gate_data, flow)->crowding += 1;
	max_cost = 0;
	edge = source->edges;
	while (edge)
	{
		cost = get_cost(get_data(((t_node*)(edge->content))->gate_data, flow));
		if (cost && (!max_cost || cost > max_cost))
			max_cost = cost;
		edge = edge->next;
	}
	if (!graph->flow_best_cost || max_cost < graph->flow_best_cost)
	{
		graph->flow_best = flow;
		graph->flow_best_cost = max_cost;
	}
}
