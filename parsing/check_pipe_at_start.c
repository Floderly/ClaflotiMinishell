/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_at_start.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/09/19 22:21:57 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe_at_start(s_g *s_g)
{
	int	i;
	int	pipe_start;
	int	pipe_end;

	pipe_start = 0;
	pipe_end = 0;
	i = 0;
	while (s_g->i2[i] == ' ' && s_g->i2[i] != 0)
		i++;
	if (s_g->i2[i] == '|')
		pipe_start = 1;
	while (s_g->i2[i] != 0)
		i++;
	if (s_g->i2[i - 1] == '|')
		pipe_end = 1;
	if (pipe_start == 1 || pipe_end == 1)
	{
		printf("Pas de pipe au debut ou a la fin\n");
		s_g->exit_ret = 2;
		return (0);
	}
	return (1);
}
