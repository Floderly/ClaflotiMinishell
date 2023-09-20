/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:29:47 by fderly            #+#    #+#             */
/*   Updated: 2023/09/20 10:41:59 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_clear_env(char *str, s_g *s_g)
{
	int		i;
	char	*ret;

	ret = gc_malloc(&s_g->gc, sizeof(char) * 9999);
	i = 0;
	while (str[i - 1] != '=' && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

void	own_env(s_g *s_g)
{
	int	i;

	i = -1;
	while (s_g->miniEnv[++i])
		printf("%s\n", s_g->miniEnv[i]);
}

void	add_env(char *arg, s_g *s_g)
{
	int	i;

	i = 0;
	if (is_equal(arg) == 1)
	{
		while (s_g->miniEnv[i])
		{
			if (ft_strcmp(ft_clear_env(s_g->miniEnv[i], s_g),
					ft_clear_env(arg, s_g)) == 0)
			{
				printf("trouver\n");
				break ;
			}
			i++;
		}
		if (s_g->miniEnv[i] == 0)
			s_g->miniEnv[i] = gc_malloc(&s_g->gc, sizeof(char) * 99999);
		s_g->miniEnv[i] = arg;
	}
}
