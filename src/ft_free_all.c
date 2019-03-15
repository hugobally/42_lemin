#include "lem_in.h"
#include "stdlib.h"
#include "libft.h"

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

void				ft_free_nodes_list(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->content != NULL)
			ft_free_nodes((t_node *)lst->content);
		ft_memdel((void**)&lst);
		lst = tmp;
	}

}

void				ft_free_graph(t_graph *graph)
{
	t_list **tab;
	int i;

	tab = graph->nodes;
	i = 0;
	while (i < graph->table_size)
	{
		if (tab[i] != NULL)
			ft_free_nodes_list(tab[i]);
		i++;
	}
	if (tab != NULL)
		free(tab);
}

void				ft_free_list(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->content != NULL)
			free(lst->content);
		if (lst != NULL)
			free(lst);
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
