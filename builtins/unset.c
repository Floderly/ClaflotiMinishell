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

void	own_unset_exp(char *arg, int x, t_g *t_g)
{
	int	i;

	i = 0;
	while (t_g->exp_env[i])
	{
		if (ft_strncmp(t_g->exp_env[i], arg, x) == 0)
		{
			while (t_g->exp_env[i])
			{
				t_g->exp_env[i] = t_g->exp_env[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
}

void	own_unset(char *input, t_g *t_g)
{
	size_t	i;
	int		x;
	char	**args;

	args = ft_split(input, ' ');
	x = ft_strlen(args[1]);
	i = 0;
	while (t_g->mini_env[i])
	{
		if (ft_strncmp(t_g->mini_env[i], args[1], x) == 0)
		{
			while (t_g->mini_env[i])
			{
				t_g->mini_env[i] = t_g->mini_env[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
	own_unset_exp(args[1], x, t_g);
}
