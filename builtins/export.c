#include "../minishell.h"

void	print_export(s_g *s_g)
{
	int	i;

	i = -1;
	while (s_g->expEnv[++i])
		printf("declare -x %s\n", s_g->expEnv[i]);
}

void	swap_export(s_g *s_g)
{
	int		i;
	char	*tmp;

	i = 0;
	while (s_g->expEnv[i + 1])
	{
		if (ft_strcmp(s_g->expEnv[i], s_g->expEnv[i + 1]) > 0)
		{
			tmp = s_g->expEnv[i];
			s_g->expEnv[i] = s_g->expEnv[i + 1];
			s_g->expEnv[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

void	add_export(char *input, s_g *s_g)
{
	int	i;
	int	j;

	i = 0;
	while (s_g->expEnv[i])
		i++;
	s_g->expEnv[i] = gc_malloc(&s_g->gc, sizeof(char) * 99999);
	j = -1;
	while (input[++j])
		s_g->expEnv[i][j] = input[j];
	modif_exp(s_g, i);
	i++;
	s_g->expEnv[i] = 0;
	swap_export(s_g);
}

int	own_export(char *input, s_g *s_g)
{
	char	**args;

	args = ft_split(input, ' ');
	if (!args[1])
	{
		swap_export(s_g);
		print_export(s_g);
		return (0);
	}
	else if (('0' <= args[1][0] && args[1][0] <= '9') || args[1][0] == '=')
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	add_export(args[1], s_g);
	add_env(args[1], s_g);
	return (0);
}
