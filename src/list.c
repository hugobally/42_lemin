#include "libft.h"
#include "lem_in.h"

void					add_start(t_wrap *wrap, void *content, t_list **start)
{
	t_list				*node;

	node = (t_list*)ft_memalloc(sizeof(t_list));
	if (!node || !start)
		collector(wrap, KO);
	node->content = content;
	if (*start)
		node->next = *start;
	*start = node;
}

void					add_end(t_wrap *wrap, void *content,
									t_list **start, t_list **end)
{
	t_list				*node;
	t_list				*parse;

	node = (t_list*)ft_memalloc(sizeof(t_list));
	if (!node || !start || !end)
		collector(wrap, KO);
	node->content = content;
	if (!*start)
		*start = node;
	else
	{
		if (!*end)
		{
			parse = *start;
			while (parse->next)
				parse = parse->next;
			*end = parse;
		}
		(*end)->next = node;
	}
	*end = node;
}

void					del_start(t_wrap *wrap, t_list **start)
{
	t_list				*node;

	if (!start || !*start)
		collector(wrap, KO);
	node = *start;
	*start = (*start)->next;
	ft_memdel((void**)&node);
}

/*
** |!| del_end parses the whole list every time it is called
*/

void					del_end(t_wrap *wrap, t_list **start, t_list **end)
{
	t_list				*node;

	if (!start || !*start || !end)
		collector(wrap, KO);
	if (!(*start)->next)
	{
		*start = NULL;
		*end = NULL;
	}
	else
	{
		node = *start;
		while (node->next->next)
			node = node->next;
		*end = node;
		ft_memdel((void**)&(node->next));
	}
}

void					del_all(t_wrap *wrap, t_list **start)
{
	t_list	*node;
	t_list	*swap;

	if (!start || !*start)
		collector(wrap, KO);
	node = *start;
	while (node)
	{
		swap = node->next;
		ft_memdel((void**)&node);
		node = swap;
	}
	*start = NULL;
}
