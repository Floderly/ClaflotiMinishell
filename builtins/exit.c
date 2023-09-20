/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:29:54 by fderly            #+#    #+#             */
/*   Updated: 2023/09/20 10:58:55 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_invalid_argument(char **args, t_g *t_g)
{
	t_g->exit_ret = 2;
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	gc_clean(&t_g->gc);
	free_tab(args);
	free(t_g->input);
	exit(t_g->exit_ret);
}

void	handle_numeric_exit(char **args, t_g *t_g)
{
	if (ft_atoi(args[1]) < 0)
		t_g->exit_ret = 255;
	else
		t_g->exit_ret = ft_atoi(args[1]);
	gc_clean(&t_g->gc);
	free(t_g->input);
	free_tab(args);
	exit(t_g->exit_ret);
}

void	own_exit(char *input, t_g *t_g)
{
	char	**args;

	args = ft_split(input, ' ');
	ft_putstr_fd("exit\n", 2);
	if (args[1] && args[2])
	{
		t_g->exit_ret = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else if (args[1] != 0 && ft_isnum(args[1]) == -1)
		handle_invalid_argument(args, t_g);
	else if (args[1] != 0)
		handle_numeric_exit(args, t_g);
	else
	{
		gc_clean(&t_g->gc);
		free(t_g->input);
		free_tab(args);
		exit(t_g->exit_ret);
	}
}
