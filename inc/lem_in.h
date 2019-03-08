#ifndef LEM_IN_H
# define LEM_IN_H

#include <stdint.h>

# define OK 0
# define KO 1

typedef struct		s_hop
{
	int				flow;
	t_node			*hop_to;
}					t_hop;

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

typedef struct		s_node
{
	uint8_t			type;
	char			*name;
	t_vector		coord;
	t_node			**edges;
	t_list			gate_data;
	t_list			hops;
	int				ant;
}					t_node;

typedef struct		s_graph
{
	t_node			*nodes;
	t_node			*source;
	t_node			*sink;
}					t_graph;

typedef struct		s_wrap
{
	t_list			*input;
	t_graph			*graph;
	int				best_flow;
}					t_wrap;

void				add_start(t_wrap *wrap, void *content, t_list **start);
void				add_end(t_wrap *wrap, void *content, t_list **start);
void				del_start(t_wrap *wrap, void *content, t_list **start);
void				del_end(t_wrap *wrap, void *content, t_list **start);
void				del_all(t_wrap *wrap, void *content, t_list **start);
void				collector(t_wrap *wrap, uint8_t flag);

#endif
