#include "lem_in.h"
#include "libft.h"

/*
** TODO change name of bfs structure
** TODO order of ants in output
*/

t_node				*hop_get_flow(t_list *hop_list, int flow)
{
	t_list			*elem;
	t_hop			*hop;

	elem = hop_list;
	while (elem)
	{
		hop = (t_hop*)(elem->content);
		if (hop->flow <= flow)
			return (hop->hop_to);
		elem = elem->next;
	}
	return (NULL);
}

void				print_move(int counter, t_node *destination, uint8_t reset)
{
	static uint8_t	not_at_start;

	if (reset)
	{
		ft_printf("\n");
		not_at_start = 0;
	}
	else
	{
		//DEBUG
		static int previous;
		int i;
		if (!not_at_start)
			for (i = 0 ; i < counter ; i++)
				ft_printf("\t");
		if (not_at_start && !(counter == previous + 1))
		{
			for (i = 1 ; i < counter - previous ; i++)
				ft_printf("\t");
		}
		previous = counter;
		//
		if (not_at_start)
			ft_printf("\t");
		ft_printf("L%d-%s",
					counter,
					destination ? destination->name : NULL);
		not_at_start = 1;
	}
}

uint8_t				send(t_wrap *wrap, t_node *node, t_bfs *sim, int counter)
{
	t_gate_data		*data;

	data = get_data(node->gate_data, wrap->graph.flow_best);
	if (data && data->crowding && data->sent < data->crowding)
	{
		data->sent++;
		node->guest = counter;
		if (node->type != END)
			add_end(wrap, (void*)node, &(sim->frontier), &(sim->frontier_end));
		print_move(counter, node, 0);
		return (1);
	}
	return (0);
}

void				push(t_wrap *wrap, int flow, t_bfs *sim)
{
	t_list			*elem;
	t_node			*node;
	t_node			*dest;

	elem = sim->level;
	while (elem)
	{
		node = ((t_node*)(elem->content));
		dest = hop_get_flow(node->hop_data, flow);
		dest->guest = node->guest;
		if (dest->type != END)
			add_end(wrap, (void*)dest, &(sim->frontier), &(sim->frontier_end));
		print_move(node->guest, dest, 0);
		elem = elem->next;
	}
}

void				output(t_wrap *wrap, t_node *source, int flow, int remain)
{
	t_bfs			sim;
	t_list			*edge;
	int				counter;

	ft_bzero((void*)&sim, sizeof(t_bfs));
	wrap->bfs_state = &sim;
	counter = 0;
	while (!counter || update_level(&(sim.level), &(sim.frontier)))

	{
		edge = source->edges;
		push(wrap, flow, &sim);
		while (edge && remain)
		{
			if (send(wrap, (t_node*)(edge->content), &sim, counter))
			{
				counter++;
				remain--;
			}
			edge = edge->next;
		}
		print_move(0, NULL, 1);
	}
}
