#include <fcntl.h>
#include "lem_in.h"

/*
int					create_file(t_wrap *wrap, char *path)
{
	int				fd;
	
	fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		 collector(wrap, KO);
	wrap->out_fd = fd;
	return (1);
}
*/

#include <stdio.h> //DEBUG ONLY
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


void				graph_to_file(t_wrap *wrap, t_graph *graph)
{
	int				fd;

	(void)graph;
	if ((fd = open("viz/data_test.js", O_RDWR | O_CREAT | O_TRUNC, 0644)) != -1)
	{
		printf("fd is %d\n", fd);
		getchar();
		wrap->out_fd = fd;
//		nodes_to_file(fd, wrap, graph->nodes);
//		edges_to_file(fd, wrap, graph->nodes);
	}
	else
		collector(wrap, KO);
}
