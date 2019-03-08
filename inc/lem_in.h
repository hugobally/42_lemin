#ifndef LEM_IN_H
# define LEM_IN_H

#include <stdint.h>

/*
** Macros
*/

# define OK 0
# define KO 1

/*
** Generic list structure
*/

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*
** Sub-Components for node structure
**	- gate_data : information about gate nodes
**	- hop : next node in path for a given flow id
**  - vector : node coordinates
*/

typedef struct		s_gate_data
{
	int				flow;
	int				path_length;
	int				crowding;
	int				to_send;
}					t_gate_data;

typedef struct		s_vector
{
	int				x;
	int				y;
}					t_vector;

typedef struct		s_hop
{
	int				flow;
	struct s_node	*hop_to;
}					t_hop;

/*
** Main Node Component
*/

typedef struct		s_node
{
	uint8_t			type;
	char			*name;
	t_vector		coord;
	struct s_node	**edges;
	t_list			*gate_data;
	t_list			*hops;
	int				ant;
}					t_node;

/*
** Graph representation of input map
*/

typedef struct		s_graph
{
	t_node			*nodes;
	t_node			*source;
	t_node			*sink;
	int				flow_max;
	int				flow_best;
}					t_graph;

/*
** Container for program data
*/

typedef struct		s_wrap
{
	t_list			*input_start;
	t_list			*input_end;
	t_graph			*graph;
}					t_wrap;

/*
**	List Creation/Deletion
*/

void				add_start(t_wrap *wrap, void *content, t_list **start);
void				add_end(t_wrap *wrap, void *content,
								t_list **start, t_list **end);
void				del_start(t_wrap *wrap, t_list **start);
void				del_end(t_wrap *wrap, t_list **start, t_list **end);
void				del_all(t_wrap *wrap, t_list **start);


/*
**	Create all possible flows and store them
*/

void		flow_create_all(t_wrap *wrap, t_graph *graph);
t_list		*flow_find_new(t_wrap *wrap, t_node *source, t_node *sink);

/*
**	Collector for clean exit
*/

void				collector(t_wrap *wrap, uint8_t flag);

#endif
