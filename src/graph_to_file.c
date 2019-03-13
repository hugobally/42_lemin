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

void				nodes_to_file(int fd, t_list *start)
{
	t_list			*elem;
	t_node			*node;

	elem = start;
	while (elem)
	{
		node = (t_node*)(elem->content);
		ft_dprintf(fd, "\t{\"name\": \"%s\", \"type\": %d},\n",
						node->name, node->type);
		elem = elem->next;
	}
}

void				edges_to_file(int fd, t_list *start)
{
	t_list			*elem;
	t_node			*node;
	t_list			*edge;

	elem = start;
	while (elem)
	{
		node = (t_node*)(elem->content);
		edge = node->edges;
		while (edge)
		{
			ft_dprintf(fd, "\t{\"source\": \"%s\", \"target\": \"%s\"},\n",
							node->name, ((t_node*)(edge->content))->name);
			edge = edge->next;
		}
		elem = elem->next;
	}
}

void			parse_table(t_wrap *wrap, t_graph *graph, t_list **nodes,
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

void				graph_to_file(t_wrap *wrap, t_graph *graph)
{
	if (create_file(wrap, "viz/data.js")
			|| create_file(wrap, "data.js"))
	{
		ft_dprintf(wrap->out_fd, "var nodes_data = [\n");
		parse_table(wrap, graph, graph->nodes, &nodes_to_file);
		ft_dprintf(wrap->out_fd, "]\n\n");
		ft_dprintf(wrap->out_fd, "var links_data = [\n");
		parse_table(wrap, graph, graph->nodes, &edges_to_file);
		ft_dprintf(wrap->out_fd, "]\n\n");
	}
	else
		collector(wrap, KO);
}
