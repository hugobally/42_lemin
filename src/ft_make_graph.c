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

void        ft_make_node(t_wrap *wraper, char *str, t_graph *graph, int type)
{
    t_node *new_node;
    int index;

    new_node = (t_node *)ft_memalloc(sizeof(t_node));
    if (!((new_node->name = ft_strcdup(str, ' '))))
        collector(wraper, KO);
    new_node->type = type;
    ft_get_coord(str, &new_node);
    index = hash((unsigned char *)new_node->name) % graph->table_size;
    ft_insert_in_tab(wraper, graph, index, new_node);
	if (type == START)
		graph->source = new_node;
	if (type == END)
		graph->sink = new_node;
}

void        ft_add_link(t_wrap *wraper, char *str, t_graph *graph)
{
    char    *room_1;
    char    *room_2;

    ft_get_edges(&room_1, &room_2, str, wraper);
    if (!(ft_add_edges(room_1, room_2, wraper, graph)))
        collector(wraper, KO);
    if (!(ft_add_edges(room_2, room_1, wraper, graph)))
        collector(wraper, KO);
}

int         ft_make_graph(t_wrap *wraper, int size, t_graph *graph)
{
    int     i;
    t_list  *input;
    int     flag;
    char    *str;

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
        else if (ft_is_link(input->content, wraper))
            ft_add_link(wraper, input->content, graph);
        input = input->next;
        i++;
    }
    wraper->graph = *graph; 
    return(0);
}
