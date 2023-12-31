/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:29:33 by fderly            #+#    #+#             */
/*   Updated: 2023/09/20 10:29:34 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env(t_g *t_g, int opt)
{
	size_t	i;

	i = -1;
	while (t_g->mini_env[++i])
	{
		if (opt == 2 && ft_strncmp("OLDPWD=", t_g->mini_env[i], 7) == 0)
			return (i);
		else if (opt == 3 && ft_strncmp("PWD=", t_g->mini_env[i], 4) == 0)
			return (i);
	}
	return (-1);
}

void	change_pwd(t_g *t_g)
{
	int		i;
	int		j;
	char	*tmp;
	char	**dir;
	char	*old;

	i = 0;
	j = -1;
	dir = ft_split(t_g->cur_pwd, '/');
	old = ft_strjoin(t_g->cur_pwd, "/");
	while (dir[i])
		i++;
	if (ft_strcmp(t_g->new_pwd, "..") == 0)
	{
		t_g->new_pwd = "/";
		while (++j < i - 1)
		{
			tmp = ft_strjoin(dir[j], "/");
			t_g->new_pwd = ft_strjoin(t_g->new_pwd, tmp);
			free(tmp);
		}
	}
	else
		t_g->new_pwd = ft_strjoin(old, t_g->new_pwd);
}

char	*chaeck_var2(t_g *t_g, int opt)
{
	char	**args;
	int		i;

	i = get_env(t_g, opt);
	if (i == -1)
		return (0);
	args = ft_split(t_g->mini_env[i], '=');
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

void	modif_chdir(t_g *t_g, char *dir)
{
	int	i;

	i = 0;
	if (chdir(dir) == -1)
		perror("error chdir\n");
	else
	{
		t_g->new_pwd = dir;
		change_pwd(t_g);
		i = get_env(t_g, 3);
		t_g->mini_env[i] = ft_strjoin("PWD=", t_g->new_pwd);
		i = get_env(t_g, 2);
		t_g->mini_env[i] = ft_strjoin("OLDPWD=", t_g->cur_pwd);
		t_g->cur_pwd = t_g->new_pwd;
	}
}

void	own_cd(char *str, t_g *t_g)
{
	char	**args;

	args = ft_split(str, ' ');
	if (!args[1])
		ft_putstr_fd("\n", 1);
	else if (args[2])
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	else if (args[1])
		modif_chdir(t_g, args[1]);
	else
		ft_putstr_fd("minishell: cd: usage: cd [-L|-P] [dir]\n", 2);
	free_tab(args);
}
