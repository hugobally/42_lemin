#include "lem_in.h"
#include "libft.h"

void     ft_make_tab(int size, t_wrap *wraper, t_graph *graph)
{
    int     i;

    i = 0;
    if (!(graph->nodes = (t_list **)ft_memalloc(sizeof(t_list *) * size)))
        collector(wraper, KO);
    graph->table_size = size;
}

void        ft_get_coord(char *str, t_node **node)
{
    int i;
    t_vector coord;

    i = 0;
    while (str[i] != ' ')
        i++;
    i++;
    coord.x = ft_atoi(&str[i]);
    while (str[i] != ' ')
        i++;
    i++;
    coord.y = ft_atoi(&str[i]);
    (*node)->coord = coord;
}

void        ft_insert_in_tab(t_wrap *wraper, t_graph *graph, int index, t_node *new_node)
{
    t_list **tab;

    tab = graph->nodes;
    add_start(wraper, new_node, &tab[index]);
}

void        ft_make_node(t_wrap *wraper, char *str, t_graph *graph, int type)
{
    t_node *new_node;
    int index;

    new_node = (t_node *)ft_memalloc(sizeof(t_node));
    if (!((new_node->name = ft_strcdup(str, ' '))))
        collector(wraper, KO);
    new_node->type = type;
    ft_get_coord(str, &new_node);
    index = hash((unsigned char *)str) % graph->table_size;
    ft_insert_in_tab(wraper, graph, index, new_node);
}

//void        ft_add_link(t_wrap *wraper, char *str, t_graph *graph)
//{
//}

int         ft_make_graph(t_wrap *wraper, int size, t_graph *graph)
{
    int i;
    t_list **tab;
    t_node *node;
    t_list *input;
    t_list *list;
    char *str;
    int flag;

    i = 0;
    input = wraper->input_start;
    ft_make_tab(size, wraper, graph);
    while (input != NULL)
    {
        str = input->content;
        if (i == 0)
            graph->source_capacity = ft_ants(input->content, wraper);
        if (str[0] == '#')
            flag = ft_is_comment(str);
        if (ft_is_node(input->content, wraper))
        {
            ft_make_node(wraper, input->content, graph, flag);
            flag = 0;
        }
        //else if (ft_is_link(wraper, input->content))
        //    ft_add_link(wraper, input->content, graph);
        input = input->next;
        i++;
    }
    tab = graph->nodes;
    i = 0;
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
                    if (str && str != NULL)
                        ft_printf("tab[%d] : %s type %d", i, str, node->type);
                }
                list = list->next;
            }
            ft_printf("\n");
        }
        i++;
    }
    return(0);
}