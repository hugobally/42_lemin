#include "libft.h"
#include "lem_in.h"

void					add_start(t_wrap *wrap, void *content, t_list **start)
{
	t_list				*node;

	if (wrap && content)
	{
		node = (t_list*)ft_memalloc(sizeof(t_list));
		if (!node || !start)
			collector(wrap, KO);
		node->content = content;
		if (*start)
			node->next = *start;
		*start = node;
	}
}

void					add_end(t_wrap *wrap, void *content,
									t_list **start, t_list **end)
{
	t_list				*node;
	t_list				*parse;

	if (wrap && content)
	{
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
}

//void					del_start(t_wrap *wrap, void *content, t_list **start)
//void					del_end(t_wrap *wrap, void *content, t_list **start)
//void					del_all(t_wrap *wrap, void *content, t_list **start)
