#include "libft.h"
#include "lem_in.h"

/*
** For each node on BFS output path, add or remove hop.
** TODO If no hop is removed, only the gate data for the newly created path
** needs to be updated. If hop is removed, store which path it belongs to.
*/

void			flow_update_nodes(t_wrap *wrap, t_list *path, int flow)
{
	t_list		*list_elem;
	t_node		*node;
	t_node		*next_node;
	t_hop		*hop;

	list_elem = path;
	while (list_elem->next)
	{
		node = (t_node*)(list_elem->content);
		next_node = (t_node*)(list_elem->next->content);
		hop = (t_hop*)ft_memalloc(sizeof(t_hop));
		hop->flow = flow;
		if (next_node->hop_data
				&& ((t_hop*)(next_node->hop_data->content))->hop_to == node)
		{
			hop->hop_to = NULL;
			add_start(wrap, (void*)hop, &(next_node->hop_data));
		}
		else
		{
			hop->hop_to = next_node;
			add_start(wrap, (void*)hop, &(node->hop_data));
		}
		list_elem = list_elem->next;
	}
}
