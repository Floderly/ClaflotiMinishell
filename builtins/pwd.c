#include "../minishell.h"

int	own_pwd(s_g *s_g)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		s_g->cur_pwd = cwd;
		return (0);
	}
	else
		return (1);
}
