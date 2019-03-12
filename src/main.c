#include "../inc/lem_in.h"
#include "libft.h"

int			main(void)
{
	t_wrap 	wrap;
	t_graph graph;

	ft_bzero(&wrap, sizeof(t_wrap));
	ft_bzero(&graph, sizeof(t_graph));
	ft_read_map(&wrap, &graph);	
	return (0);
}
