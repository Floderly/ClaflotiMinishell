/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:14:19 by chugot            #+#    #+#             */
/*   Updated: 2023/09/15 19:14:36 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_builtin_father(char *prompt, s_g *s_g)
{
    if (ft_strncmp(prompt, "export", 6) == 0 && s_g->cmd_nbr == 1)
		own_export(prompt, s_g);
	else if (ft_strncmp(prompt, "unset", 5) == 0 && s_g->cmd_nbr == 1)
		own_unset(prompt, s_g);
	else if (ft_strncmp(prompt, "exit", 4) == 0 && s_g->cmd_nbr == 1)
		own_exit(prompt, s_g);
	else if (ft_strncmp(prompt, "cd", 2) == 0 && s_g->cmd_nbr == 1)
		own_cd(prompt, s_g);
	else
		return (0);
	return (1);
}

int	if_builtin(s_g *s_g, char *input)
{
	if (ft_strncmp(input, "echo", 4) == 0)
		own_echo(input);
	else if (ft_strcmp(input, "pwd") == 0)
		own_pwd(s_g);
	else if (ft_strcmp(input, "env") == 0)
		own_env(s_g);
	else
		return (1);
	return (0);
}

int	count_args(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	check_arg(char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_isnum(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' && str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}
