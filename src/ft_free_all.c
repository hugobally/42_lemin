#include "lem_in.h"
#include "stdlib.h"
#include "libft.h"

/*
void				ft_free_nodes(t_node *lst)
{
	t_list 	*edges;
	t_list	*tmp;

    edges = lst->edges;
	//if (lst->name != NULL)
	ft_memdel((void**)&lst->name);
	while (edges)
	{
		tmp = edges->next;
		ft_memdel((void**)&edges);
		edges = tmp;
	}
	ft_memdel((void**)&lst);
}
*/

void				ft_free_node(t_node *node)
{
	t_list			*hop;
	t_list			*gate_data;

	if (node->edges)
		del_all(&(node->edges));
	if (node->name)
		ft_memdel((void**)&(node->name));
	if (node->hop_data)
	{
		hop = node->hop_data;
		while (hop)
		{
			if (hop->content)
				ft_memdel((void**)&(hop->content));
			hop = hop->next;
		}
		del_all(&(node->hop_data));
	}
	if (node->gate_data)
	{
		gate_data = node->gate_data;
		while (gate_data)
		{
			if (gate_data->content)
				ft_memdel((void**)&(gate_data->content));
			gate_data = gate_data->next;
		}
		del_all(&(node->gate_data));
	}
	ft_memdel((void**)&node);
}

void				ft_free_nodes_list(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->content)
			ft_free_node((t_node*)lst->content);
		ft_memdel((void**)&lst);
		lst = tmp;
	}
}

void				ft_free_graph(t_graph *graph)
{
	t_list **tab;
	int size;
	int i;

	if (graph->nodes)
	{
		tab = graph->nodes;
		size = graph->table_size;
		i = 0;
		while (i < size)
		{
			if (tab[i])
				ft_free_nodes_list(tab[i]);
			i++;
		}
		free(graph->nodes);
		graph->nodes = NULL;
	}
}

void				ft_free_list(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->content != NULL)
			ft_memdel((void**)&(lst->content));
		ft_memdel((void**)&(lst));
		lst = tmp;
	}
}

void				ft_free_wrap(t_wrap *wrap)
{
	ft_free_list(wrap->input_start);
    wrap->input_end = NULL;
	ft_free_graph(&(wrap->graph));
	//free bfs_output
	//free bfs_state
	//viz_option
	//out_fd
}
