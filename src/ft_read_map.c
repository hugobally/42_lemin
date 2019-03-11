#include "lem_in.h"
#include "libft.h"

int     ft_nbr_size(int nbr)
{
    int len;

    len = 1;
    while (nbr > 9)
    {
        nbr = nbr % 10;
        len++;
    }
    return (len);
}

int     ft_ants(char *line, t_wrap *wraper)
{
    int x;
    int len;
    int new_len;

    len = ft_strlen(line);
    x = ft_atoi(line);
    new_len = ft_nbr_size(x);
    if ((x > 2147483647 || x < -2147483648) || (len != new_len))
    {
        ft_printf("Error\n");
        collector(wraper, KO);
    }
    else
        return(x);
}

int     ft_count_nodes(char *line, int *nodes)
{
    int i;
    int count;
    int tiret;

    i = 0;
    count = 0;
    tiret = 0;
    while (line[i])
    {
        if (line[i] == ' ')
            count++;
        if (line[i] == '-')
            tiret++;
        i++;
    }
    if (count == 2 && tiret == 0)
    {
        (*nodes)++;
        return(0);
    }
    if (tiret == 1)
        return(1);
    return(0);
}

int     ft_is_node(char *line, t_wrap *wraper)
{
    int i;
    int count;
    int tiret;

    i = 0;
    count = 0;
    tiret = 0;
    while (line[i])
    {
        if (line[i] == ' ')
            count++;
        if (line[i] == '-')
            tiret++;
        i++;
    }
    if (count == 2 && tiret == 0)
        return (1);
    else
        return (0);
}

int     ft_is_link(char *line, t_wrap *wraper)
{
    int i;
    int count;
    int tiret;

    i = 0;
    count = 0;
    tiret = 0;
    while (line[i])
    {
        if (line[i] == '-')
            tiret++;
        i++;
    }
    if (tiret == 1)
        return (1);
    else
        return (0);
}

int     ft_read_standard(t_wrap *wraper)
{
    int ret;
    char *line;
    t_list *start;
    int i;
    int nodes;

    i = 0;
    nodes = 0;
    line = NULL;
    while ((ret = get_next_line(0, &line)) && ret > 0)
    {
        add_end(wraper, line, &start, &wraper->input_end);
        if (i == 0)
            i = ft_count_nodes(line, &nodes);
    }
    wraper->input_start = start;
    return(nodes);
}

unsigned long       hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

t_table              *ft_make_tab(int size, t_wrap *wraper, t_table *table)
{
    int     i;

    i = 0;
    if (!(table = (t_table*)malloc(sizeof(t_table))))
        collector(wraper, KO);
    if (!(table->tab= (t_list **)malloc(sizeof(t_node *) * (size + 1))))
        collector(wraper, KO);
    table->size = size;
    ft_bzero(&table->tab, sizeof(t_list**));
    return(table);
}

void    ft_get_coord(t_wrap *wraper, char *str, t_node **node)
{
    int i;
    t_vector *coord;

    if (!(coord=(t_vector*)malloc(sizeof(t_vector))))
        collector(wraper, KO);
    i = 0;
    while (str[i] != ' ')
        i++;
    i++;
    coord->x = ft_atoi(&str[i]);
    while (str[i] != ' ')
        i++;
    i++;
    coord->y = ft_atoi(&str[i]);
    (*node)->coord = *coord;
}

int     ft_make_node(t_wrap *wraper, char *str, t_table **table, int type)
{
    t_node *new_node;
    int index;

    if (!(new_node = (t_node *)malloc(sizeof(new_node))))
        collector(wraper, KO);
    ft_bzero(&new_node, sizeof(t_node*));
    new_node->name = ft_strdup(str);
    new_node->type = type;
    ft_get_coord(wraper, str, &new_node);
    index = hash(str) % (*table)->size;
    (*table)->tab[index] = new_node;
}

t_graph     ft_init_graph(t_wrap *wraper, t_table *table, t_graph **graph)
{
    if (!(*graph = (t_graph *)malloc(sizeof(t_graph))))
        collector(wraper, OK);
    ft_bzero(&graph, sizeof(t_graph));
    (*graph)->nodes = table->tab;
    (*graph)->table_size = table->size;
    return(*graph);
}

int     ft_make_graph(t_wrap *wraper, int size, t_list *input)
{
    int i;
    int ants;
    t_table *table;
    t_graph *graph;

    ants = 0;
    i = 0;
    table = ft_make_tab(size, wraper, table);
    graph = ft_init_graph(wraper, table, &graph);
    while (input != NULL)
    {
        if (i == 0)
            ants = ft_ants(input->content, wraper);
        else if (ft_is_node(input->content, wraper))
            ft_make_node(wraper, input->content, &graph->nodes, 0);
        else if (ft_is_link(wraper, input->content))
            ft_add_link(wraper, input->content);
        input = input->next;
        i++;
    }
    return(0);
}

int     ft_read_map(t_wrap *wraper)
{
    int size;

    size = ft_read_standard(wraper);
    ft_make_graph(wraper, size, wraper->input_start);
}