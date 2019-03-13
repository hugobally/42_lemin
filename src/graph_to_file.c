#include <fcntl.h>
#include "lem_in.h"

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

/*
void				write_wrapper(t_wrap *wrap, char *buffer, int printf_ret)
{
	int				write_ret;

	if (printf_ret == -1)
		collector(wrap, KO);
	write_ret = write(wrap->output_fd, line, ft_strlen(line));
	if (line)
		ft_memdel((void**)&line);
	if (write_ret == -1)
		collector(wrap, KO);
}
*/

void				nodes_to_file(int fd, t_wrap *wrap,
									t_graph *graph, t_nodes **nodes)
{
	int				size;// use graph->size

	size = 9;
	if (nodes)
	{
		ft_dprintf(wrap->out_fd, "var nodes_data = [\n");
	}
	
}

void				graph_to_file(t_wrap *wrap, t_graph *graph)
{
	if (create_file(&wrap_test, "viz/data_test.js")
			|| create_file(&wrap_test, "data_test.js"))
	{
		nodes_to_file(wrap->out_fd, wrap, graph->nodes);
		edges_to_file(wrap->out_fd, wrap, graph->nodes);
	}
	else
		collector(wrap, KO);
}
