#include "lem_in.h"
#include "stdlib.h"
#include "libft.h"

void			collector(t_wrap *wrap, uint8_t flag)
{
	if (flag == KO)
	{
		ft_printf("ERROR\n");
		ft_free_wrap(wrap);
		exit(EXIT_FAILURE);
	}
	if (flag == DONE)
		output_wrapper(wrap, &(wrap->graph));
	ft_free_wrap(wrap);
	exit(EXIT_SUCCESS);
}
