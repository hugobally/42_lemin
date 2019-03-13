#include "../inc/lem_in.h"
#include "libft.h"

int			main(void)
{
	t_wrap 	wrap;
	t_graph graph;

	ft_bzero(&wrap, sizeof(t_wrap));
	ft_bzero(&graph, sizeof(t_graph));
	ft_read_map(&wrap, &graph);
	ft_print_hash_tab(&(wrap.graph), 1);
//	flow_create_all(&wrap, &(wrap.graph));
//	output(&wrap, wrap.graph.source, wrap.graph.flow_best, wrap.graph.source_capacity);
	return (0);
}
