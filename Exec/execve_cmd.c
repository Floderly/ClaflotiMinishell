/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:52:23 by chugot            #+#    #+#             */
/*   Updated: 2023/09/20 14:07:39 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_path_norminette(t_g *t_g)
{
	int	i;

	i = 0;
	while (ft_strnstr(t_g->mini_env[i], "PATH=", 5) == NULL)
		i++;
	return (i);
}

char	*check_path(t_g *t_g, char *cmd)
{
	char	**tabpath;
	char	*halfpath;
	char	*path;
	int		i;

	i = check_path_norminette(t_g);
	tabpath = ft_split(t_g->mini_env[i] + 5, ':');
	i = 0;
	while (tabpath[i])
	{
		halfpath = ft_strjoin(tabpath[i], "/");
		path = ft_strjoin(halfpath, cmd);
		free(halfpath);
		if (access(path, F_OK) == 0)
		{
			free_tab(tabpath);
			return (path);
		}
		free(path);
		i++;
	}
	free_tab(tabpath);
	t_g->exit_ret = 127;
	error_msg("error no path found\n", t_g);
	return (0);
}

void	path(t_g *t_g, char *argv)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = check_path(t_g, cmd[0]);
	t_g->exit_ret = 0;
	if (execve(path, cmd, t_g->mini_env) == -1)
	{
		free_tab(cmd);
		free(path);
		t_g->exit_ret = 2;
		error_msg("error execve\n", t_g);
	}
}

char	*change_cmd_0(t_g *t_g, char **cmd, char *path1)
{
	int	i;
	int	j;

	(void)t_g;
	i = 0;
	while (cmd[0][i])
	{
		path1[i] = cmd[0][i];
		i++;
	}
	path1[i] = '\0';
	while (path1[i] != '/')
		i--;
	j = i + 1;
	i = 0;
	free(cmd[0]);
	cmd[0] = malloc(sizeof(char) * ((ft_strlen(path1) - j) + 1));
	while (path1[j])
	{
		cmd[0][i] = path1[j];
		i++;
		j++;
	}
	cmd[0][i] = '\0';
	return (cmd[0]);
}

void	path_user(t_g *t_g, char *input)
{
	char	**cmd;
	char	*path1;

	cmd = ft_split(input, ' ');
	path1 = malloc(sizeof(char) * (ft_strlen(cmd[0]) + 1));
	cmd[0] = change_cmd_0(t_g, cmd, path1);
	if (execve(path1, cmd, t_g->mini_env) == -1)
	{
		free(path1);
		free_tab(cmd);
		error_msg("error execve\n", t_g);
	}
}
