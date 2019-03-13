#include "lem_in.h"
#include "libft.h"

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
    else if (count > 2 && line[0] != '#')
        collector(wraper, KO);
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
    else if (tiret > 1)
        collector(wraper, KO);
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
    start = NULL;
    while ((ret = get_next_line(0, &line)) && ret > 0)
    {
        add_end(wraper, line, &start, &wraper->input_end);
        if (i == 0)
            i = ft_count_nodes(line, &nodes);
    }
    wraper->input_start = start;
    return(nodes);
}

int     ft_read_map(t_wrap *wraper, t_graph *graph)
{
    int size;

    size = ft_read_standard(wraper);
    ft_make_graph(wraper, size, graph);
    return(0);
}