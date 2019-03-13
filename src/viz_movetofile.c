#include "libft.h"
#include "lem_in.h"

/*
** TODO norme
*/

void				move_to_file(t_wrap *wrap, t_node *source, t_node *target,
									int	flag)
{
	static int		counter;
	char			*buf;

	buf = NULL;
	if (flag == TURN_START)
	{
		if (!counter)
			ft_dprintf(wrap->out_fd, "\nvar turns_data = [\n");
		ft_dprintf(wrap->out_fd, "\t[\n");
		counter++;
	}
	if (source && target)
		ft_dprintf(wrap->out_fd,
					"\t\t{\"source\": \"%s\", \"target\": \"%s\", \"num\": %d},\n",
					source->name, target->name, flag);
	if (flag == TURN_END)
		ft_dprintf(wrap->out_fd, "\t],\n");
	if (flag == LAST_TURN_END)
		ft_dprintf(wrap->out_fd, "\t]\n]");
}
