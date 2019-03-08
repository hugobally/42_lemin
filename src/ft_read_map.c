#include "../inc/lem_in.h"
#include "../libft/inc/libft.h"

int     ft_is_node(char *line, int *nodes)
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
    if (count == 3)
    {
        (*nodes)++;
        return(0);
    }
    if (tiret == 1)
        return(1);
    return(0);
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
            i = ft_is_node(wraper->input_end->content, &nodes);
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

t_list              **ft_make_tab(int size, t_wrap *wraper)
{
    t_list  **tab;
    int     i;

    i = 0;
    if (!(tab = (t_list **)malloc(sizeof(t_list*) * size + 1)))
        collector(wraper, 1);
    while (i < size + 1)
    {
        tab[i] = NULL;
        i++;
    }
    return(tab);
}

int     ft_make_graph(t_wrap *wraper, int size, t_list *input)
{
    int i;
    int ants;
    t_list **tab;

    ants = 0;
    i = 0;
    tab = ft_make_tab(size, wraper);
    while (input != NULL)
    {
        if (i == 0)
            ants = ft_atoi(input->content);
        if (ft_is_node(wraper, input->content))
            ft_make_node(wraper, input->content, tab);
        if (ft_is_link(wraper, input->content))
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