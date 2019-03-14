#include "../inc/lem_in.h"
#include "libft.h"
#include <unistd.h>

void		printinput(t_list *input)
{
	t_list	*elem;

	elem = input;
	while (elem)
	{
		ft_printf("%s\n", ((char*)(elem->content)));
		elem = elem->next;
	}
	ft_printf("\n");
}

int			main(void)
{
	t_wrap 	wrap;
	t_graph graph;

	ft_bzero(&wrap, sizeof(t_wrap));
	ft_bzero(&graph, sizeof(t_graph));

// INPUT
	ft_read_map(&wrap, &graph);
	//ft_print_hash_tab(&(graph), 1);
	flow_create_all(&wrap, &(wrap.graph));

// VIZ PREP

	printinput(wrap.input_start);
	if (wrap.viz_option || 1)//rmv 1
	{
		if (!create_file(&wrap, "viz/moves_data.js"))
			collector(&wrap, KO);
		output(&wrap, wrap.graph.source,
						wrap.graph.flow_best,
						wrap.graph.source_capacity);
		close(wrap.out_fd);
		if (!create_file(&wrap, "viz/graph_data.js"))
			collector(&wrap, KO);
		graph_to_file(&wrap, &(wrap.graph));
//		viz_launch();
		close(wrap.out_fd);
	}
	else
		output(&wrap, wrap.graph.source,
						wrap.graph.flow_best,
						wrap.graph.source_capacity);
}
