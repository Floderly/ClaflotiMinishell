/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:29:58 by fderly            #+#    #+#             */
/*   Updated: 2023/09/20 10:30:00 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	own_unset_exp(char *arg, int x, s_g *s_g)
{
	int	i;

	i = 0;
	while (s_g->expEnv[i])
	{
		if (ft_strncmp(s_g->expEnv[i], arg, x) == 0)
		{
			while (s_g->expEnv[i])
			{
				s_g->expEnv[i] = s_g->expEnv[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
}

void	own_unset(char *input, s_g *s_g)
{
	size_t	i;
	int		x;
	char	**args;

	args = ft_split(input, ' ');
	x = ft_strlen(args[1]);
	i = 0;
	while (s_g->miniEnv[i])
	{
		if (ft_strncmp(s_g->miniEnv[i], args[1], x) == 0)
		{
			while (s_g->miniEnv[i])
			{
				s_g->miniEnv[i] = s_g->miniEnv[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
	own_unset_exp(args[1], x, s_g);
}
