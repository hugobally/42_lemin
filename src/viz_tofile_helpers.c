#include "libft.h"
#include "lem_in.h"

void				move_to_file(t_wrap *wrap,
									t_node *source,
									t_node *target,
									int flag)
{
	static int		counter;
	char			*buf;

	buf = NULL;
	if (source && target)
		ft_dprintf(wrap->out_fd,
					"\t\t{\"source\": \"%s\", "
					"\"target\": \"%s\", "
					"\"num\": %d},\n",
					source->name, target->name, flag);
	if (flag == TURN_START)
	{
		if (!counter)
			ft_dprintf(wrap->out_fd, "\nvar turns_data = [\n");
		ft_dprintf(wrap->out_fd, "\t[\n");
		counter++;
	}
	if (flag == TURN_END)
		ft_dprintf(wrap->out_fd, "\t],\n");
	if (flag == LAST_TURN_END)
		ft_dprintf(wrap->out_fd, "\t]\n]");
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
