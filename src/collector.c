#include "lem_in.h"
#include "stdlib.h"
#include "libft.h"

void				collector(__attribute__((unused)) t_wrap *wrap, __attribute__((unused)) uint8_t flag)
{
	if (flag == KO)
		ft_printf("ERROR\n");
	if (flag == DONE)
	{
		//on resoud

	}
	//on free
	exit(1);
}
