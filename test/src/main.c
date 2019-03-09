#include <stdlib.h>
#include "lem_in_test.h"

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
	** VARIABLES
	*/

	t_wrap		wrap;
	t_list 		*node;
	char		*string;
	int			i = 0;

	/*
	** LIST ADD START
	*/

  	ft_printf("list add start test\n");
	string = ft_strdup("teststring0");
	
	while (i < 10)
	{
		add_start(&wrap, (void*)string, &(wrap.input_start));
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
	reset (&wrap);
	ft_printf("------------------\n");

	/*
	** LIST ADD END
	*/

	ft_printf("list add end test\n");
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

	ft_printf("------------------\n");

	/*
	** LIST DEL START
	*/

	ft_printf("list del start test\n");
	del_start(&wrap, &(wrap.input_start));
	ft_printf("expected testring1 > teststring9\n");
	node = wrap.input_start;
	while (node)
	{
		ft_printf("%s\n", (char*)node->content);
		node = node->next;
	}
	node = (t_list*)ft_memalloc(sizeof(t_list));
	del_start(&wrap, &node);
	if (node != NULL)
	{
		ft_printf("del list with 1 elem : KO\n");
		print_error();
	}
	ft_printf("del list with 1 elem : OK\n");
	ft_printf("------------------\n");

	/*
	** LIST DEL END
	*/

	ft_printf("list del end test\n");
	del_end(&wrap, &(wrap.input_start), &(wrap.input_end));
	ft_printf("expected testring1 > teststring8\n");
	node = wrap.input_start;
	while (node)
	{
		ft_printf("%s\n", (char*)node->content);
		node = node->next;
	}
	node = (t_list*)ft_memalloc(sizeof(t_list));
	del_end(&wrap, &node, &node);
	if (node != NULL)
	{
		ft_printf("del list with 1 elem : KO\n");
		print_error();
	}
	ft_printf("del list with 1 elem : OK\n");
	ft_printf("------------------\n");

	/*
	** LIST DEL ALL
	*/

	ft_printf("list del all test\n");
	del_all(&wrap, &(wrap.input_start));
	ft_printf("expected null\n");
	node = wrap.input_start;
	if (node == NULL)
		ft_printf("del all : OK\n");
	while (node)
	{
		ft_printf("%s\n", (char*)node->content);
		node = node->next;
	}
	node = (t_list*)ft_memalloc(sizeof(t_list));
	del_all(&wrap, &node);
	if (node != NULL)
	{
		ft_printf("del list with 1 elem : KO\n");
		print_error();
	}
	ft_printf("del list with 1 elem : OK\n");
	ft_printf("------------------\n");

	flow_test();

	return (0);
}
