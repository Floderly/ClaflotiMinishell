/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:14:19 by chugot            #+#    #+#             */
/*   Updated: 2023/09/13 18:56:00 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_equal(char *s)
{
	int	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	modif_exp(s_g *s_g, int i)
{
	int len;

	len = 0;
	if (is_equal(s_g->expEnv[i]) == 1)
	{
		len = ft_strlen(s_g->expEnv[i]) + 2;
		s_g->expEnv[i][len-1] = 34;
		len--;
		while (s_g->expEnv[i][len--] != '=')
			s_g->expEnv[i][len] = s_g->expEnv[i][len-1];
		s_g->expEnv[i][len+1] = 34;
		//printf("declare -x %s\n", s_g->expEnv[i]);
	}
}

void	clone_env(s_g *s_g, char **env)
{
	int	i;
	// FAIRE LE VRAI MALLOC ? CHAUD AVEC EXPORT
	s_g->miniEnv = gc_malloc (&s_g->gc, sizeof(char) * 9999);
	s_g->expEnv = gc_malloc (&s_g->gc, sizeof(char) * 9999);
	i = 0;
	while (env[i])
	{
		s_g->miniEnv[i] = ft_gcstrdup(env[i], s_g);
		s_g->expEnv[i] = ft_gcstrdup(env[i], s_g);
		modif_exp(s_g, i);
		i++;
	}
	s_g->miniEnv[i] = 0;
	s_g->expEnv[i] = 0;	
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
