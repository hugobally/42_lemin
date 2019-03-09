#include "lem_in_test.h"

void		flow_test(void)
{
	t_wrap wrap;
	t_node *nodes;
	
	ft_bzero(&wrap, sizeof(t_wrap));
	ft_bzero(&(wrap.graph), sizeof(t_graph));
	
	nodes = (t_node*)(ft_memalloc(sizeof(t_node) * 8));

	wrap.graph.source = node[0];
	node[0] = wrap.graph.source;
	node[0]->type = START;
	node[0]->name = ft_strdup("SOURCE");
	node[1]->name = ft_strdup("A");
	node[2]->name = ft_strdup("B");
	node[3]->name = ft_strdup("C");
	node[4]->name = ft_strdup("D");
	node[5]->name = ft_strdup("E");
	node[6]->name = ft_strdup("F");
	node[7]->name = ft_strdup("SINK");
	node[7]->type = END;
	add_start(&wrap, (void*)(&(node[1])), &(node[0].edges));
	add_start(&wrap, (void*)(&(node[2])), &(node[0].edges));
	add_start(&wrap, (void*)(&(node[3])), &(node[1].edges));
	add_start(&wrap, (void*)(&(node[1])), &(node[3].edges));
	add_start(&wrap, (void*)(&(node[4])), &(node[3].edges));
	add_start(&wrap, (void*)(&(node[3])), &(node[4].edges));
	add_start(&wrap, (void*)(&(node[7])), &(node[4].edges));
	add_start(&wrap, (void*)(&(node[4])), &(node[2].edges));
	add_start(&wrap, (void*)(&(node[2])), &(node[4].edges));
	add_start(&wrap, (void*)(&(node[5])), &(node[2].edges));
	add_start(&wrap, (void*)(&(node[2])), &(node[5].edges));
	add_start(&wrap, (void*)(&(node[5])), &(node[6].edges));
	add_start(&wrap, (void*)(&(node[6])), &(node[5].edges));
	add_start(&wrap, (void*)(&(node[7])), &(node[6].edges));

	wrap.graph.flow_max = 1;
}
