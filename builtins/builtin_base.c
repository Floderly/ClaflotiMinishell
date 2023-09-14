/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:14:19 by chugot            #+#    #+#             */
/*   Updated: 2023/09/13 14:45:48 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_builtin(s_g *s_g, char *input)
{
	if (ft_strncmp(input, "echo", 4) == 0)
		own_echo(input);
	else if (ft_strncmp(input, "cd", 2) == 0)
		own_cd(input, s_g);
	else if (ft_strcmp(input, "pwd") == 0)
		own_pwd(s_g);
	else if (ft_strcmp(input, "env") == 0)
		own_env(s_g);
	else if (ft_strncmp(input, "exit", 4) == 0)
		own_exit(input, s_g);
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
		if (str[i] < '0' && '9' < str[i])
			return (-1);
	}
	return (0);
}
