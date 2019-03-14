#include "libft.h"
#include "lem_in.h"


void					del_one(t_wrap *wrap, t_list *elem, t_list **start)
{
	t_list				*parse;

	if (elem && start && *start)
	{
		if (*start == elem)
			del_start(wrap, start);
		else
		{
			parse = *start;
			while (parse->next != elem)
				parse = parse->next;
			parse->next = elem->next;
			ft_memdel((void**)&elem);
		}
	}
}

void					del_start(t_wrap *wrap, t_list **start)
{
	t_list				*node;

	if (!start)
		collector(wrap, KO);
 	if (*start)
	{
		node = *start;
		*start = (*start)->next;
		ft_memdel((void**)&node);
	}
}

/*
** |!| del_end parses the whole list every time it is called
** |!| the 'end' ptr will not be updated by other functions,
** 		dont store it outside of a del/add loop
*/

void					del_end(t_wrap *wrap, t_list **start, t_list **end)
{
	t_list				*node;

	if (!start || !end)
		collector(wrap, KO);
	if (*start)
	{
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
}

void					del_all(t_wrap *wrap, t_list **start)
{
	t_list	*node;
	t_list	*swap;

	if (!start)
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
