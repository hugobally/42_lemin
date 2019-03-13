#include "libft.h"
#include "lem_in.h"

int                 ft_nbr_size(int nbr)
{
    int len;

    len = 1;
    while (nbr > 9)
    {
        nbr = nbr / 10;
        len++;
    }
    return (len);
}

int                 ft_ants(char *line, t_wrap *wraper)
{
    int x;
    int len;
    int new_len;

    len = ft_strlen(line);
    x = ft_atoi(line);
    new_len = ft_nbr_size(x);
    if ((x > 2147483647 || x < -2147483648) || (len != new_len))
        collector(wraper, KO);
    return(x);
}

unsigned long       hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

int                 ft_is_comment(char *str)
{
    int flag;

    flag = 0;
    if (ft_strcmp(str, "##start") == 0)
        flag = 1;
    else if (ft_strcmp(str, "##end") == 0)
        flag = 2;
    return(flag);
}

void        ft_insert_in_tab(t_wrap *wraper, t_graph *graph, int index, t_node *new_node)
{
    t_list **tab;

    tab = graph->nodes;
    add_start(wraper, new_node, &tab[index]);
}