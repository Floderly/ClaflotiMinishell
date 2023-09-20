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

int	check_var(t_g *t_g, int i)
{
	int	j;

	t_g->path_var_tempo = gc_malloc (&t_g->gc, sizeof(char) * 9999);
	i++;
	j = 0;
	while (t_g->input[i + j] != 0 && t_g->input[i + j] != ' '
		&& t_g->input[i + j] != '"' && t_g->input[i + j] != '|')
	{
		t_g->path_var_tempo[j] = t_g->input[i + j];
		j++;
	}
	t_g->path_var_tempo[j] = 0;
	i = 0;
	while (t_g->mini_env[i])
	{
		if ((ft_strnstr(t_g->mini_env[i], t_g->path_var_tempo,
					ft_strlen(t_g->path_var_tempo)) != NULL)
			&& t_g->mini_env[i][ft_strlen(t_g->path_var_tempo)] == '=')
			break ;
		i++;
	}
	if (t_g->mini_env[i] == 0)
		return (0);
	return (1);
}
