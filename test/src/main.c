#include "lem_in_test.h"
#include <stdlib.h>

void	print_error(void)
{
	ft_printf("-----ERROR-----");
	exit(1);
}

void	reset(t_wrap *wrap)
{
	ft_bzero((void*)wrap, sizeof(t_wrap));
}

int		main(void)
{

	/*
	** SETUP
	*/

	t_wrap		wrap;
	char		*string;

	/*
	** LIST ADD START TEST
	*/

	int			i = 0;

	string = ft_strdup("teststring0");
	while (i < 10)
	{
		add_start(&wrap, (void*)string, &(wrap.input_start));
		string = ft_strdup(string);
		string[ft_strlen(string) - 1] += 1;
		i++;
	}
	t_list *node;
	node = wrap.input_start;
	ft_printf("expected teststring9 > teststring0\n");
	while (node)
	{
		ft_printf("%s\n", (char*)node->content);
		node = node->next;
	}
	ft_printf("list add start : done\n");

	reset (&wrap);

	/*
	** LIST ADD END TEST
	*/

	i = 0;

	string = ft_strdup("teststring0");
	while (i < 10)
	{
		add_end(&wrap, (void*)string, &(wrap.input_start), &(wrap.input_end));
		string = ft_strdup(string);
		string[ft_strlen(string) - 1] += 1;
		i++;
	}
	node = wrap.input_start;
	ft_printf("expected teststring9 > teststring0\n");
	while (node)
	{
		ft_printf("%s\n", (char*)node->content);
		node = node->next;
	}
	ft_printf("list add end : done\n");

	reset (&wrap);

	return (0);
}
