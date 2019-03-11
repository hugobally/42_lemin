#include "../inc/lem_in.h"
#include "libft.h"

int			main(void)
{
	t_wrap wrap;

	ft_bzero(&wrap, sizeof(t_wrap));
	ft_read_map(&wrap);	
	return (0);
}
