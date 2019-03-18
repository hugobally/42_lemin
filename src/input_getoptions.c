#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"

static void		exit_usage(void)
{
	ft_printf("usage: lem-in [-el] < input.map\n\n");
	ft_printf("-e : export data to .js in ./viz/data/\n");
	ft_printf("     to launch vizualization, use 'open viz/index.html'\n");
	ft_printf("\n");
	ft_printf("-l : show the total number of lines printed on the\n");
	ft_printf("     last line of resulting output\n");
	ft_printf("\n");
	exit(EXIT_FAILURE);
}

static void		add_option(const char c, t_opt *opt)
{
	int			i;

	i = ft_strchri("el", c);
	if (i == -1)
		exit_usage();
	opt->opt_int = opt->opt_int | (1 << i);
}

void			get_options(t_opt *opt, int argc, char **argv)
{
	int			i;
	int			j;

	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1])
	{
		j = 1;
		while (argv[i][j])
		{
			add_option(argv[i][j], opt);
			j++;
		}
		i++;
	}
	if (i < argc)
		exit_usage();
	while (1);
}
