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

int	add_var_interro(s_g *s_g, int i)
{
	char	*var_interro;
	int		k;

	k = 0;
	var_interro = ft_itoa(s_g->exit_ret);
	while (var_interro[k])
	{
		s_g->i2[i + k] = var_interro[k];
		k++;
	}
	s_g->i2[i + k] = 0;
	return (k);
}

int	add_var(s_g *s_g, int i)
{
	int	j;
	int	k;

	j = 0;
	while (s_g->miniEnv[j])
	{
		if (ft_strnstr(s_g->miniEnv[j], s_g->pathVarTempo,
				ft_strlen(s_g->pathVarTempo)) != NULL)
			break ;
		j++;
	}
	k = 0;
	while (s_g->miniEnv[j][ft_strlen(s_g->pathVarTempo) + k + 1] != ' '
		&& s_g->miniEnv[j][ft_strlen(s_g->pathVarTempo) + k + 1] != 0)
	{
		s_g->i2[i + k] = s_g->miniEnv[j]
		[ft_strlen(s_g->pathVarTempo) + k + 1];
		k++;
	}
	s_g->i2[i + k] = 0;
	return (k);
}

void	quote_var_env(s_g *s_g, int *i, int *j)
{
	s_g->i2[(*j)++] = s_g->input[(*i)++];
	while (s_g->input[(*i)] != '\'')
		s_g->i2[(*j)++] = s_g->input[(*i)++];
	s_g->i2[(*j)++] = s_g->input[(*i)++];
}

int	var_env_chang2(s_g *s_g, int *i, int *j)
{
	if (s_g->input[*(i) + 1] == '?')
	{
		*(j) += add_var_interro(s_g, *(j));
		*(i) += 2;
	}
	else if (check_var(s_g, *(i)) != 0)
	{
		*(j) += add_var(s_g, *(j));
		*(i) += ft_strlen(s_g->pathVarTempo) + 1;
	}
	else
		return (0);
	return (1);
}

int	var_env_chang(s_g *s_g)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	s_g->i2 = gc_malloc (&s_g->gc, sizeof(char) * 99999);
	while (s_g->input[i])
	{
		if (s_g->input[i] == '\'')
			quote_var_env(s_g, &i, &j);
		else if (s_g->input[i] == '$' && s_g->input[i + 1] != ' ')
		{
			if (var_env_chang2(s_g, &i, &j) == 0)
				return (0);
		}
		else
			s_g->i2[j++] = s_g->input[i++];
	}
	s_g->i2[j] = '\0';
	return (1);
}
