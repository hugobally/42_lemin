#include "lem_in_test.h"

void	viz(t_wrap *wrap)
{
	graph_to_file(wrap, &(wrap->graph));
}
