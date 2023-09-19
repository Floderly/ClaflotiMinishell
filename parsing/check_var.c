/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/09/19 23:00:50 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_var(s_g *s_g, int i)
{
	int	j;

	s_g->pathVarTempo = gc_malloc (&s_g->gc, sizeof(char) * 9999);
	i++;
	j = 0;
	while (s_g->input[i + j] != 0 && s_g->input[i + j] != ' '
		&& s_g->input[i + j] != '"' && s_g->input[i + j] != '|')
	{
		s_g->pathVarTempo[j] = s_g->input[i + j];
		j++;
	}
	s_g->pathVarTempo[j] = 0;
	i = 0;
	while (s_g->miniEnv[i])
	{
		if ((ft_strnstr(s_g->miniEnv[i], s_g->pathVarTempo,
					ft_strlen(s_g->pathVarTempo)) != NULL)
			&& s_g->miniEnv[i][ft_strlen(s_g->pathVarTempo)] == '=')
			break ;
		i++;
	}
	if (s_g->miniEnv[i] == 0)
		return (0);
	return (1);
}
