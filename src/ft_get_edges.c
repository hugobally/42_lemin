#include "libft.h"
#include "lem_in.h"

void        ft_get_edges(char **room_1, char **room_2, char *str, t_wrap *wraper)
{
    int len_1;
    int len_2;

    len_1 = ft_strclen(str, '-');
    if (!((*room_1) = ft_strcdup(str, '-')))
        collector(wraper, KO);
    len_1 = len_1 + 1;
    len_2 = ft_strlen(&str[len_1]);
    if (!((*room_2) = ft_strdup(&str[len_1])))
        collector(wraper, KO);
}

t_node      *ft_get_hashed(char *str, t_wrap *wraper, t_graph *graph)
{
    t_list **tab;
    t_list *lst;
    t_node *node;
    int index;

    index = hash((unsigned char *)str) % graph->table_size;
    tab = graph->nodes;
    lst = tab[index];
    if (!lst || lst == NULL)
        collector(wraper, KO);
    else
    {
        while (lst != NULL)
        {
            node = lst->content;
            if (ft_strcmp(node->name, str) == 0)
                return(node);
            lst = lst->next;
        }
    }
    collector(wraper, KO);
    return (NULL);
}

int         ft_add_edges(char *room_1, char *room_2, t_wrap *wraper, t_graph *graph)
{
    t_node *node;
    t_node *edge;

    if (!(node = ft_get_hashed(room_1, wraper, graph)))
        collector(wraper, KO);
    if (!(edge = ft_get_hashed(room_2, wraper, graph)))
        collector(wraper, KO);
    if (edge->type != 1)
        add_start(wraper, edge, &node->edges);
    return (1);
}

void        ft_print_hash_tab(t_graph *graph, int full)
{
    int     i;
    int     size;
    t_list  **tab;
    t_list  *list;
    t_list  *edges;
    char    *str;
    t_node  *node;

    tab = graph->nodes;
    i = 0;
    size = graph->table_size;
    while (i < size)
    {
        if (tab[i] && tab[i] != NULL && tab[i]->content && tab[i]->content != NULL)
        {
            list = tab[i];
            while (list != NULL)
            {
                node = list->content;
                if (node->name != NULL && node && node->name)
                {
                    str = node->name;
                    edges = node->edges;
                    if (str && str != NULL && full != 2)
                    {
                        ft_printf("tab[%d] : %s | type %d | ", i, str, node->type);
                        if (full == 0)
                            ft_printf("\n");
                    }
                    if (edges && edges != NULL && (full == 1 || full == 2))
                    {
                        if (full != 2)
                        ft_printf("edges[%d] :", i);
                        while (edges != NULL)
                        {
                            node = edges->content;
                            if (full == 2)
                                ft_printf("edges[%d] :", i);
                            ft_printf(" %s | ", node->name);
                            if (full == 2)
                                ft_printf("\n");
                            edges = edges->next;
                        }
                    }
                }
                list = list->next;
            }
            if (full == 1)
                ft_printf("\n");
        }
        i++;
    }
}