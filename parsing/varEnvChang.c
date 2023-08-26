/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/04/20 11:40:27 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	printf("Prompt MAJ : %s\n", s_g->i2);
	return (k);
}

int	check_var(s_g *s_g, int i)
{
	int	j;

	s_g->pathVarTempo = malloc (sizeof(char) * 9999);
	if (!s_g->pathVarTempo)
		return (0);
	i++;
	j = 0;
	while (s_g->input[i + j] != 0 && s_g->input[i + j] != ' ')
	{
		s_g->pathVarTempo[j] = s_g->input[i + j];
		j++;
	}
	s_g->pathVarTempo[j] = 0;
	printf("Variable trouver : %s\n", s_g->pathVarTempo);
	i = 0;
	while (s_g->miniEnv[i])
	{
		if ((ft_strnstr(s_g->miniEnv[i], s_g->pathVarTempo,
					ft_strlen(s_g->pathVarTempo)) != NULL)
			&& s_g->miniEnv[i][ft_strlen(s_g->pathVarTempo)] == '=')
		{
			printf("La variable existe bien\n");
			break ;
		}
		i++;
	}
	if (s_g->miniEnv[i] == 0)
	{
		printf("La variable n'existe pas\n");
		free(s_g->pathVarTempo);
		return (0);
	}
	return (1);
}

int	var_env_chang(s_g *s_g)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	s_g->i2 = gc_malloc (&s_g->gc, sizeof(char) * 99999);
	if (!s_g->i2)
		return (0);
	while (s_g->input[i])
	{
		if (s_g->input[i] == '\'')
		{
			s_g->i2[j] = s_g->input[i]; // Copie l'apostrophe simple
			j++;
			i++;
			while (s_g->input[i] != '\'')
			{
				s_g->i2[j] = s_g->input[i]; // Copie le caractère entre les apostrophes
				j++;
				i++;
			}
			s_g->i2[j] = s_g->input[i]; // Copie la deuxième apostrophe simple
			j++;
			i++;
		}
		else if (s_g->input[i] == '$' && s_g->input[i + 1] != ' ')
		{
			if (check_var(s_g, i) != 0)
			{
				j += add_var(s_g, j);
				i += ft_strlen(s_g->pathVarTempo) + 1;
			}
			else
			{
				free(s_g->i2);
				return (0);
			}
		}
		else
		{
			s_g->i2[j] = s_g->input[i];
			j++;
			i++;
		}
	}
	s_g->i2[j] = '\0';
	printf("Prompt fin traitement var : %s\n", s_g->i2);
	return (1);
}
