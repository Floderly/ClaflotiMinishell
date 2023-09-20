/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varEnvChang.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/09/19 23:02:16 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_var_interro(t_g *t_g, int i)
{
	char	*var_interro;
	int		k;

	k = 0;
	var_interro = ft_itoa(t_g->exit_ret);
	while (var_interro[k])
	{
		t_g->i2[i + k] = var_interro[k];
		k++;
	}
	t_g->i2[i + k] = 0;
	return (k);
}

int	add_var(t_g *t_g, int i)
{
	int	j;
	int	k;

	j = 0;
	while (t_g->mini_env[j])
	{
		if (ft_strnstr(t_g->mini_env[j], t_g->path_var_tempo,
				ft_strlen(t_g->path_var_tempo)) != NULL)
			break ;
		j++;
	}
	k = 0;
	while (t_g->mini_env[j][ft_strlen(t_g->path_var_tempo) + k + 1] != ' '
		&& t_g->mini_env[j][ft_strlen(t_g->path_var_tempo) + k + 1] != 0)
	{
		t_g->i2[i + k] = t_g->mini_env[j]
		[ft_strlen(t_g->path_var_tempo) + k + 1];
		k++;
	}
	t_g->i2[i + k] = 0;
	return (k);
}

void	quote_var_env(t_g *t_g, int *i, int *j)
{
	t_g->i2[(*j)++] = t_g->input[(*i)++];
	while (t_g->input[(*i)] != '\'')
		t_g->i2[(*j)++] = t_g->input[(*i)++];
	t_g->i2[(*j)++] = t_g->input[(*i)++];
}

int	var_env_chang2(t_g *t_g, int *i, int *j)
{
	if (t_g->input[*(i) + 1] == '?')
	{
		*(j) += add_var_interro(t_g, *(j));
		*(i) += 2;
	}
	else if (check_var(t_g, *(i)) != 0)
	{
		*(j) += add_var(t_g, *(j));
		*(i) += ft_strlen(t_g->path_var_tempo) + 1;
	}
	else
		return (0);
	return (1);
}

int	var_env_chang(t_g *t_g)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	t_g->i2 = gc_malloc (&t_g->gc, sizeof(char) * 99999);
	while (t_g->input[i])
	{
		if (t_g->input[i] == '\'')
			quote_var_env(t_g, &i, &j);
		else if (t_g->input[i] == '$' && t_g->input[i + 1] != ' ')
		{
			if (var_env_chang2(t_g, &i, &j) == 0)
				return (0);
		}
		else
			t_g->i2[j++] = t_g->input[i++];
	}
	t_g->i2[j] = '\0';
	return (1);
}
