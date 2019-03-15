#include "lem_in.h"
#include "stdlib.h"
#include "libft.h"

void				collector(__attribute__((unused)) t_wrap *wrap, __attribute__((unused)) uint8_t flag)
{
	if (flag == KO)
		ft_putstr("ERROR\n");
	if (flag == DONE)
	{
		//on resoud
		//et on imprime
	}
	ft_free_wrap(wrap);
	if (flag == OK)
		return ;
	exit(1);
}
