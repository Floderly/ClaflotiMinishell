#include "../minishell.h"

void	own_env(s_g *s_g)
{
	int	i;

	i = -1;
	while (s_g->miniEnv[++i])
		printf("%s\n", s_g->miniEnv[i]);
}

void	add_env(char *arg, s_g *s_g)
{
	int	i;

	i = 0;
	if (is_equal(arg) == 1)
	{
		while (s_g->miniEnv[i])
			i++;
		s_g->miniEnv[i] = gc_malloc(&s_g->gc, sizeof(char) * 99999);
		s_g->miniEnv[i] = arg;
	}
}
