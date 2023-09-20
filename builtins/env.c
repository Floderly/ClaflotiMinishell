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

char	*ft_clear_env(char *str, t_g *t_g)
{
	int		i;
	char	*ret;

	ret = gc_malloc(&t_g->gc, sizeof(char) * 9999);
	i = 0;
	while (str[i - 1] != '=' && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

void	own_env(t_g *t_g)
{
	int	i;

	i = -1;
	while (t_g->mini_env[++i])
		printf("%s\n", t_g->mini_env[i]);
}

void	add_env(char *arg, t_g *t_g)
{
	int	i;

	i = 0;
	if (is_equal(arg) == 1)
	{
		while (t_g->mini_env[i])
		{
			if (ft_strcmp(ft_clear_env(t_g->mini_env[i], t_g),
					ft_clear_env(arg, t_g)) == 0)
			{
				printf("trouver\n");
				break ;
			}
			i++;
		}
		if (t_g->mini_env[i] == 0)
			t_g->mini_env[i] = gc_malloc(&t_g->gc, sizeof(char) * 99999);
		t_g->mini_env[i] = arg;
	}
}
