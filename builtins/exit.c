#include "../minishell.h"

void	own_exit(char *input, s_g *s_g)
{
	char	**args;

	args = ft_split(input, ' ');
	ft_putstr_fd("exit", 2);
	if (args[1] && args[2])
	{
		s_g->exit_ret = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else if (args[1] && ft_isnum(args[1]) == -1)
	{
		s_g->exit_ret = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (args[1])
		s_g->exit_ret = ft_atoi(args[1]);
	else
		s_g->exit_ret = 0;
}