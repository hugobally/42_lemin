#include "lem_in_test.h"

void		print_gatedata(t_node *node, int flow)
{
	t_gate_data	*data;

	data = get_data(node->gate_data, flow);
	if (data)
	{
	ft_printf("gate %s, flow %d : pathlen %d | crowding : %d | sent : %d\n", node->name, flow,
				data->path_len, data->crowding, data->sent);
	}
	else
		ft_printf("gate %s, flow %d : no data\n", node->name, flow);
}

void		flow_test(void)
{
	t_wrap wrap;
	t_node *nodes;
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

	//Basic split map + 1 node on the right
	nodes = (t_node*)(ft_memalloc(sizeof(t_node) * 9));
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
	nodes[8].name = ft_strdup("G");
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
	add_start(&wrap, (void*)(&(nodes[8])), &(nodes[6].edges));
	add_start(&wrap, (void*)(&(nodes[6])), &(nodes[8].edges));
	add_start(&wrap, (void*)(&(nodes[7])), &(nodes[8].edges));
	wrap.graph.nodes = nodes;

	/*
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
	*/

	flow_create_all(&wrap, &(wrap.graph));
	
//	print_gatedata(&(nodes[1]), 1);
//	print_gatedata(&(nodes[2]), 1);
//	print_gatedata(&(nodes[1]), 2);
//	print_gatedata(&(nodes[2]), 2);

	// flow_simulate unit test
	wrap.graph.source_capacity = 10;
	flow_simulate(&wrap.graph, &(nodes[0]), 1);
	ft_printf("best flow : %d | line count : %d\n", wrap.graph.flow_best, wrap.graph.flow_best_cost);
	flow_simulate(&wrap.graph, &(nodes[0]), 2);
	ft_printf("best flow : %d | line count : %d\n", wrap.graph.flow_best, wrap.graph.flow_best_cost);
	ft_printf("\n");

	viz(&wrap);
	output(&wrap, &(nodes[0]), wrap.graph.flow_best, wrap.graph.source_capacity);

	//node = wrap.graph.source->hop_data;
	//while (node)
//	{
//		print_path(((t_hop*)(node->content))->hop_to);
//		node = node->next;
//	}

}
