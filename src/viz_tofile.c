#include <fcntl.h>
#include "lem_in.h"
#include "libft.h"

int					create_file(t_wrap *wrap, char *path)
{
	int				fd;
	
	fd = open(path, O_RDWR | O_CREAT | O_TRUNC | O_SYMLINK, S_IRUSR | S_IWUSR);
	if (fd == -1)
		 return (0);
	if (wrap)
		wrap->out_fd = fd;
	return (1);
}

void				parse_table(t_wrap *wrap, t_graph *graph, t_list **nodes,
									void (*output)(int, t_list*))
{
	int				i;
	int				table_size;

	if (!nodes)
		collector(wrap, KO);
	table_size = graph->table_size;
	i = 0;
	while (i < table_size)
	{
		output(wrap->out_fd, nodes[i]);
		i++;
	}
}

void				delete_duplicate(__attribute__((unused)) int fd,
										t_list *start)
{
	t_list			*elem;
	t_node			*node;

	elem = start;
	while (elem)
	{
		node = (t_node*)(elem->content);
		elem = elem->next;
	}
}

void				graph_to_file(t_wrap *wrap, t_graph *graph)
{
//	parse_table(wrap, graph, graph->nodes, &delete_duplicate);
	ft_dprintf(wrap->out_fd, "var nodes_data = [\n");
	parse_table(wrap, graph, graph->nodes, &nodes_to_file);
	ft_dprintf(wrap->out_fd, "]\n\n");
	ft_dprintf(wrap->out_fd, "var links_data = [\n");
	parse_table(wrap, graph, graph->nodes, &edges_to_file);
	ft_dprintf(wrap->out_fd, "]\n\n");
}
