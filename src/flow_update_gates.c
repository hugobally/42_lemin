#include "libft.h"
#include "lem_in.h"

static int			get_path_len(t_node *start)
{
	t_node			*node;
	int				hop_count;

	node = start;
	hop_count = 1;
	while (node->hop_data)
	{
		node = ((t_hop*)(node->hop_data->content))->hop_to;
		hop_count++;
	}
	return (hop_count);
}

void				flow_update_gates(t_wrap *wrap, t_node *source, int flow)
{
	t_list			*hop;
	t_node			*gate;
	t_gate_data		*data;

	hop = source->hop_data;
	while (hop)
	{
		gate = ((t_hop*)(hop->content))->hop_to;
		data = (t_gate_data*)ft_memalloc(sizeof(t_gate_data));
		data->flow = flow;
		data->path_len = get_path_len(gate);
		add_start(wrap, (void*)data, &(gate->gate_data));
		hop = hop->next;
	}
}
