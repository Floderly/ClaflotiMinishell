#include "../minishell.h"

int	get_env(s_g *s_g, int opt)
{
	size_t	i;

	i = -1;
	while (s_g->miniEnv[++i])
	{
		if (opt == 2 && ft_strncmp("OLDPWD=", s_g->miniEnv[i], 7) == 0)
			return (i);
		else if (opt == 3 && ft_strncmp("PWD=", s_g->miniEnv[i], 4) == 0)
			return (i);
	}
	return (-1);
}

void	change_pwd(s_g *s_g)
{
	int		i;
	int		j;
	char	*tmp;
	char	**dir;
	char	*old;

	i = 0;
	j = -1;
	dir = ft_split(s_g->cur_pwd, '/');
	old = ft_strjoin(s_g->cur_pwd, "/");
	while (dir[i])
		i++;
	if (ft_strcmp(s_g->new_pwd, "..") == 0)
	{
		s_g->new_pwd = "/";
		while (++j < i - 1)
		{
			tmp = ft_strjoin(dir[j], "/");
			s_g->new_pwd = ft_strjoin(s_g->new_pwd, tmp);
		}
	}
	else
		s_g->new_pwd = ft_strjoin(old, s_g->new_pwd);
}

char	*chaeck_var2(s_g *s_g, int opt)
{
	char	**args;
	int		i;

	i = get_env(s_g, opt);
	if (i == -1)
		return (0);
	args = ft_split(s_g->miniEnv[i], '=');
	i = -1;
	while (args[1][++i])
	{
		if (args[1][i] != 34 || args[1][i] != 39)
		{
			printf("%c\n", args[1][i]);
			return (args[1]);
		}
	}
	return (0);
}

void	modif_chdir(s_g *s_g, char *dir)
{
	int	i;

	i = 0;
	if (chdir(dir) == -1)
		perror("error chdir\n");
	else
	{
		s_g->new_pwd = dir;
		change_pwd(s_g);
		i = get_env(s_g, 3);
		s_g->miniEnv[i] = ft_strjoin("PWD=", s_g->new_pwd);
		i = get_env(s_g, 2);
		s_g->miniEnv[i] = ft_strjoin("OLDPWD=", s_g->cur_pwd);
		s_g->cur_pwd = s_g->new_pwd;
	}
}

void	own_cd(char *str, s_g *s_g)
{
	char	**args;

	args = ft_split(str, ' ');
	if (!args[1])
		ft_putstr_fd("\n", 1);
	else if (args[2])
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	else if (args[1])
		modif_chdir(s_g, args[1]);
	else
		ft_putstr_fd("minishell: cd: usage: cd [-L|-P] [dir]\n", 2);
}
