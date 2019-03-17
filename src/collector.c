#include "lem_in.h"
#include "stdlib.h"
#include "libft.h"

void			collector(t_wrap *wrap, uint8_t flag)
{
	if (flag == KO)
	{
		ft_printf("ERROR\n");
		if (flag == DONE)
		{
			//on resoud
			//et on imprime
		}
		ft_free_wrap(wrap);
		exit(1);
	}
	else
		ft_free_wrap(wrap);
}
