/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:14:19 by chugot            #+#    #+#             */
/*   Updated: 2023/08/28 17:53:26 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clone_env(s_g *s_g, char **env)
{
	int	i;
	// FAIRE LE VRAI MALLOC ? CHAUD AVEC EXPORT
	s_g->miniEnv = gc_malloc (&s_g->gc ,sizeof(char) * 9999);
	i = 0;
	while (env[i])
	{
		s_g->miniEnv[i] = ft_gcstrdup(env[i], s_g);
		i++;
	}
	s_g->miniEnv[i] = 0;
}

void	export_test(s_g *s_g, char *nomVar, char *arg)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s_g->miniEnv[i])
		i++;
	s_g->miniEnv[i] = gc_malloc (&s_g->gc ,sizeof(char) * 99999);
	while (nomVar[j])
	{
		s_g->miniEnv[i][j] = nomVar[j];
		j++;
	}
	s_g->miniEnv[i][j++] = '=';
	while (arg[k])
	{
		s_g->miniEnv[i][j + k] = arg[k];
		k++;
	}
	s_g->miniEnv[i][j + k] = 0;
	s_g->miniEnv[i + 1] = 0;
}
