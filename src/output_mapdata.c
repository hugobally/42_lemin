#include "lem_in.h"
#include "libft.h"

void		output_mapdata(t_list *input)
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
