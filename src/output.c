#include "lem_in.h"
#include "libft.h"

/*
** TODO change name of bfs structure
*/

void				print_move(int counter, t_node *destination, int flag)
{
	static uint8_t	not_at_start;
	
	if (flag == TURN_END)
	{
		ft_printf("\n");
		not_at_start = 0;
	}
	else
	{
		if (not_at_start)
			ft_printf(" ");
		ft_printf("L%d-%s",
					counter,
					destination ? destination->name : NULL);
		(void)counter;
		(void)destination;
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
		if (wrap->viz_option || 1)//
			move_to_file(wrap, wrap->graph.source, node, counter);
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
		if (wrap->viz_option || 1)//
			move_to_file(wrap, node, dest, node->guest);
		elem = elem->next;
	}
}

void				turn_control(t_wrap *wrap, int flag, int last_turn)
{
	if (flag == TURN_START && (wrap->viz_option || 1))//
		move_to_file(wrap, NULL, NULL, TURN_START);
	if (flag == TURN_END)
	{
		if (wrap->viz_option || 1)//
			move_to_file(wrap, NULL, NULL,
							last_turn ? LAST_TURN_END : TURN_END);
		print_move(0, NULL, TURN_END);
	}
}

void				output(t_wrap *wrap, t_node *source, int flow, int remain)
{
	t_bfs			sim;
	t_list			*edge;
	int				counter;
	int				turn_counter;//DEBUG

	ft_bzero((void*)&sim, sizeof(t_bfs));
	wrap->bfs_state = &sim;
	counter = 0;
	turn_counter = 0;//DEBUG
	while (!counter || update_level(&(sim.level), &(sim.frontier)))
	{
		turn_control(wrap, TURN_START, 0);
		edge = source->edges;
		push(wrap, flow, &sim);
		while (edge && remain)
		{
			if (send(wrap, (t_node*)(edge->content), &sim, counter + 1))
			{
				counter++;
				remain--;
			}
			edge = edge->next;
		}
		turn_control(wrap, TURN_END, sim.frontier == NULL);
		turn_counter++;//DEBUG
	}
	ft_printf("%d\n", turn_counter);
}
