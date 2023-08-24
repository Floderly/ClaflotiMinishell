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

int	add_var(s_gbl *s_gbl, int i)
{
	int	j;
	int	k;

	j = 0;
	while (s_gbl->miniEnv[j])
	{
		if (ft_strnstr(s_gbl->miniEnv[j], s_gbl->pathVarTempo,
				ft_strlen(s_gbl->pathVarTempo)) != NULL)
			break ;
		j++;
	}
	k = 0;
	while (s_gbl->miniEnv[j][ft_strlen(s_gbl->pathVarTempo) + k + 1] != ' '
		&& s_gbl->miniEnv[j][ft_strlen(s_gbl->pathVarTempo) + k + 1] != 0)
	{
		s_gbl->inputVarEnv[i + k] = s_gbl->miniEnv[j]
		[ft_strlen(s_gbl->pathVarTempo) + k + 1];
		k++;
	}
	s_gbl->inputVarEnv[i + k] = 0;
	printf("Prompt MAJ : %s\n", s_gbl->inputVarEnv);
	return (k);
}

int	check_var(s_gbl *s_gbl, int i)
{
	int	j;

	s_gbl->pathVarTempo = gc_malloc (&s_gbl->gc ,sizeof(char) * 9999);
	if (!s_gbl->pathVarTempo)
		return (0);
	i++;
	j = 0;
	while (s_gbl->input[i + j] != 0 && s_gbl->input[i + j] != ' ')
	{
		s_gbl->pathVarTempo[j] = s_gbl->input[i + j];
		j++;
	}
	s_gbl->pathVarTempo[j] = 0;
	printf("Variable trouver : %s\n", s_gbl->pathVarTempo);
	i = 0;
	while (s_gbl->miniEnv[i])
	{
		if ((ft_strnstr(s_gbl->miniEnv[i], s_gbl->pathVarTempo,
					ft_strlen(s_gbl->pathVarTempo)) != NULL)
			&& s_gbl->miniEnv[i][ft_strlen(s_gbl->pathVarTempo)] == '=')
		{
			printf("La variable existe bien\n");
			break ;
		}
		i++;
	}
	if (s_gbl->miniEnv[i] == 0)
	{
		printf("La variable n'existe pas\n");
		free(s_gbl->pathVarTempo);
		return (0);
	}
	return (1);
}

int	var_env_chang(s_gbl *s_gbl)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	s_gbl->inputVarEnv = gc_malloc (&s_gbl->gc ,sizeof(char) * 99999);
	if (!s_gbl->inputVarEnv)
		return (0);
	while (s_gbl->input[i])
	{
		if (s_gbl->input[i] == '\'')
		{
			s_gbl->inputVarEnv[j] = s_gbl->input[i];
			i++;
			while (s_gbl->input[i] != '\'')
			{
				s_gbl->inputVarEnv[j] = s_gbl->input[i];
				j++;
				i++;
			}
			s_gbl->inputVarEnv[j] = s_gbl->input[i];
		}
		else if (s_gbl->input[i] == '$')
		{
			if (check_var(s_gbl, i) != 0)
			{
				j += add_var(s_gbl, j);
				i += ft_strlen(s_gbl->pathVarTempo) + 1;
			}
			else
			{
				free(s_gbl->inputVarEnv);
				return (0);
			}
		}
		else
		{
			s_gbl->inputVarEnv[j] = s_gbl->input[i];
			j++;
			i++;
		}
	}
	s_gbl->inputVarEnv[j] = '\0';
	printf("Prompt fin traitement var : %s\n", s_gbl->inputVarEnv);
	return (1);
}
