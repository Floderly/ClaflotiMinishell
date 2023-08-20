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

#include "minishell.h"

char	*check_path(s_global *s_global, char *cmd)
{
	char	**tabpath;
	char	*halfpath;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(s_global->miniEnv[i], "PATH=", 5) == NULL)
		i++;
	tabpath = ft_split(s_global->miniEnv[i] + 5, ':');
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
	error_msg("error no path found\n");
}

void	path(s_global *s_global, char *argv)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = check_path(s_global, cmd[0]);
	if (execve(path, cmd, s_global->miniEnv) == -1)
	{
		free_tab(cmd);
		free(path);
		error_msg("error execve\n");
	}
	free_tab(cmd);
	free(path);
}

char	*change_cmd_0(s_global *s_global, char **cmd, char *path1) //modif la cmd[0] pour ne pas avoir le path pour deuxieme argument de execve.
{
	int	i;
	int	j; //index debut cmd.

	i = 0;
	while (cmd[0][i])
	{
		path1[i] = cmd[0][i];
		i++;
	}
	while (path1[i] != '/')
		i--;
	j = i + 1;
	i = 0;
	free(cmd[0]);
	cmd[0] = malloc(sizeof(char) * (ft_strlen(path1) - j) + 1);
	while (path1[j])
	{
		cmd[0][i] = path1[j];
		i++;
		j++;
	}
	cmd[0][i] = '\0';
	return(cmd[0]);
}

void	path_user(s_global *s_global, char *input)
{
	char	**cmd;
	char *path1; //path sans option.

	cmd = ft_split(input, ' ');
	path1 = malloc(sizeof(char) * ft_strlen(cmd[0]));
	cmd[0] = change_cmd_0(s_global, cmd, path1);
	if (execve(path1, cmd, s_global->miniEnv) == -1)
	{
		free_tab(cmd);
		free(path1);
		error_msg("error execve\n");
	}
	free(path1);
	free_tab(cmd);
}

char	*clone_input_without_option(char *input, char *input_without_option) //clone d'input pour verifier access sans option de commande.
{
	int	i;

	i = 0;
	input_without_option = malloc(sizeof(char) * ft_strlen(input));
	while (input[i] != ' ' && input[i])
	{
		input_without_option[i] = input[i];
		i++;
	}
	input_without_option[i] = '\0';
	return (input_without_option);
}