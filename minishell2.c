/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:14:19 by chugot            #+#    #+#             */
/*   Updated: 2023/09/20 11:09:09 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	modif_exp(t_g *t_g, int i)
{
	int	len;

	len = 0;
	if (is_equal(t_g->exp_env[i]) == 1)
	{
		len = ft_strlen(t_g->exp_env[i]) + 2;
		t_g->exp_env[i][len - 1] = 34;
		len--;
		while (t_g->exp_env[i][len--] != '=')
			t_g->exp_env[i][len] = t_g->exp_env[i][len - 1];
		t_g->exp_env[i][len + 1] = 34;
	}
}

void	clone_env(t_g *t_g, char **env)
{
	int	i;

	t_g->mini_env = gc_malloc (&t_g->gc, sizeof(char) * 9999);
	t_g->exp_env = gc_malloc (&t_g->gc, sizeof(char) * 9999);
	i = 0;
	while (env[i])
	{
		t_g->mini_env[i] = ft_gcstrdup(env[i], t_g);
		t_g->exp_env[i] = ft_gcstrdup(env[i], t_g);
		modif_exp(t_g, i);
		i++;
	}
	t_g->mini_env[i] = 0;
	t_g->exp_env[i] = 0;
}

void	export_test(t_g *t_g, char *nomVar, char *arg)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (t_g->mini_env[i])
		i++;
	t_g->mini_env[i] = gc_malloc (&t_g->gc, sizeof(char) * 9999);
	while (nomVar[j])
	{
		t_g->mini_env[i][j] = nomVar[j];
		j++;
	}
	t_g->mini_env[i][j++] = '=';
	while (arg[k])
	{
		t_g->mini_env[i][j + k] = arg[k];
		k++;
	}
	t_g->mini_env[i][j + k] = 0;
	t_g->mini_env[i + 1] = 0;
}
