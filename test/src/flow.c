#include "lem_in_test.h"

void		flow_test(void)
{
	t_wrap wrap;
	t_node *nodes;
//	t_list *node;
//	t_hop *hop; 
	ft_bzero(&wrap, sizeof(t_wrap));
	ft_bzero(&(wrap.graph), sizeof(t_graph));
	
	/*
	//Basic split map
	nodes = (t_node*)(ft_memalloc(sizeof(t_node) * 8));
	wrap.graph.source = &(nodes[0]);
	nodes[0].type = START;
	nodes[0].name = ft_strdup("SOURCE");
	nodes[1].name = ft_strdup("A");
	nodes[2].name = ft_strdup("B");
	nodes[3].name = ft_strdup("C");
	nodes[4].name = ft_strdup("D");
	nodes[5].name = ft_strdup("E");
	nodes[6].name = ft_strdup("F");
	nodes[7].name = ft_strdup("SINK");
	nodes[7].type = END;
	add_start(&wrap, (void*)(&(nodes[1])), &(nodes[0].edges));
	add_start(&wrap, (void*)(&(nodes[2])), &(nodes[0].edges));
	add_start(&wrap, (void*)(&(nodes[3])), &(nodes[1].edges));
	add_start(&wrap, (void*)(&(nodes[1])), &(nodes[3].edges));
	add_start(&wrap, (void*)(&(nodes[4])), &(nodes[3].edges));
	add_start(&wrap, (void*)(&(nodes[3])), &(nodes[4].edges));
	add_start(&wrap, (void*)(&(nodes[7])), &(nodes[4].edges));
	add_start(&wrap, (void*)(&(nodes[4])), &(nodes[2].edges));
	add_start(&wrap, (void*)(&(nodes[2])), &(nodes[4].edges));
	add_start(&wrap, (void*)(&(nodes[5])), &(nodes[2].edges));
	add_start(&wrap, (void*)(&(nodes[2])), &(nodes[5].edges));
	add_start(&wrap, (void*)(&(nodes[5])), &(nodes[6].edges));
	add_start(&wrap, (void*)(&(nodes[6])), &(nodes[5].edges));
	add_start(&wrap, (void*)(&(nodes[7])), &(nodes[6].edges));
	*/

	//Crossing paths
	nodes = (t_node*)(ft_memalloc(sizeof(t_node) * 7));
	wrap.graph.source = &(nodes[0]);
	nodes[0].type = START;
	nodes[0].name = ft_strdup("SOURCE"); //S0
	nodes[1].name = ft_strdup("A"); 	 //A1
	nodes[2].name = ft_strdup("B"); 	 //B2
	nodes[3].name = ft_strdup("C");		 //C3
	nodes[4].name = ft_strdup("D");		 //D4
	nodes[5].name = ft_strdup("E");		 //E5
	nodes[6].name = ft_strdup("SINK");   //T6
	nodes[6].type = END;
					//             CHILD  <<<    PARENT
	add_start(&wrap, (void*)(&(nodes[1])), &(nodes[0].edges));
	add_start(&wrap, (void*)(&(nodes[2])), &(nodes[0].edges));
	add_start(&wrap, (void*)(&(nodes[3])), &(nodes[1].edges));
	add_start(&wrap, (void*)(&(nodes[1])), &(nodes[3].edges));
	add_start(&wrap, (void*)(&(nodes[3])), &(nodes[2].edges));
	add_start(&wrap, (void*)(&(nodes[2])), &(nodes[3].edges));
	add_start(&wrap, (void*)(&(nodes[4])), &(nodes[3].edges));
	add_start(&wrap, (void*)(&(nodes[3])), &(nodes[4].edges));
	add_start(&wrap, (void*)(&(nodes[5])), &(nodes[3].edges));
	add_start(&wrap, (void*)(&(nodes[3])), &(nodes[5].edges));
	add_start(&wrap, (void*)(&(nodes[6])), &(nodes[4].edges));
	add_start(&wrap, (void*)(&(nodes[6])), &(nodes[5].edges));


	flow_create_all(&wrap, &(wrap.graph));
	
	//node = wrap.graph.source->hop_data;
	//while (node)
//	{
//		print_path(((t_hop*)(node->content))->hop_to);
//		node = node->next;
//	}

}
