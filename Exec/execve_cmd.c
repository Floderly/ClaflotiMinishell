/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:52:23 by chugot            #+#    #+#             */
/*   Updated: 2023/08/18 17:52:25 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_path(s_g *s_g, char *cmd)
{
	char	**tabpath;
	char	*halfpath;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(s_g->miniEnv[i], "PATH=", 5) == NULL)
		i++;
	tabpath = ft_split(s_g->miniEnv[i] + 5, ':');
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
	s_g->exit_ret = 127;
	error_msg("error no path found\n", s_g);
	return(0);
}

void	path(s_g *s_g, char *argv)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = check_path(s_g, cmd[0]);
	s_g->exit_ret = 0;
	if (execve(path, cmd, s_g->miniEnv) == -1)
	{
		free_tab(cmd);
		free(path);
		s_g->exit_ret = 2;
		error_msg("error execve\n", s_g);
	}
}

char	*change_cmd_0(s_g *s_g, char **cmd, char *path1) //modif la cmd[0] pour ne pas avoir le path pour deuxieme argument de execve.
{
	int	i;
	int	j; //index debut cmd.

	(void)s_g;
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
	return(cmd[0]);
}

void	path_user(s_g *s_g, char *input)
{
	char	**cmd;
	char *path1; //path sans option.

	cmd = ft_split(input, ' ');
	path1 = malloc(sizeof(char) * (ft_strlen(cmd[0]) + 1));
	cmd[0] = change_cmd_0(s_g, cmd, path1);
	if (execve(path1, cmd, s_g->miniEnv) == -1)
	{
		free(path1);
		free_tab(cmd);
		error_msg("error execve\n", s_g);
	}
}

char	*clone_input_without_option(char *input, char *input_without_option) //clone d'input pour verifier access sans option de commande.
{
	int	i;

	i = 0;
	while (input[i] != ' ' && input[i])
	{
		input_without_option[i] = input[i];
		i++;
	}
	input_without_option[i] = '\0';
	return (input_without_option);
}
