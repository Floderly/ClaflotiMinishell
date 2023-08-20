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

int	skipSingleQuote(s_global *s_global, int i)
{
	return (2);
}

int	addVar(s_global *s_global, int i)
{
	int	j;
	int	k;

	j = 0;
	while (s_global->miniEnv[j])
	{
		if (ft_strnstr(s_global->miniEnv[j], s_global->pathVarTempo, ft_strlen(s_global->pathVarTempo)) != NULL)
			break;
		j++;
	}
	k = 0;
	while (s_global->miniEnv[j][ft_strlen(s_global->pathVarTempo) + k + 1] != ' ' && s_global->miniEnv[j][ft_strlen(s_global->pathVarTempo)+ k + 1] != 0)
	{
		s_global->inputVarEnv[i + k] = s_global->miniEnv[j][ft_strlen(s_global->pathVarTempo)+ k + 1];
		k++;
	}
	s_global->inputVarEnv[i + k] = 0;
	printf("Promt MAJ : %s\n", s_global->inputVarEnv);
	return (k - 1);
}

int	checkVar(s_global *s_global, int i)
{
	//malloc du quartier, avoir si besoin de faire propre
	s_global->pathVarTempo = malloc(sizeof(char) * 9999); // NON FREE // variable structure ?
	int j = 0;
	i++;
	while(s_global->input[i + j] != 0 && s_global->input[i + j] != ' ')
	{
		s_global->pathVarTempo[j] = s_global->input[i + j];
		j++;
	}
	s_global->pathVarTempo[j] = 0;
	printf("Variable trouver : %s\n", s_global->pathVarTempo);
	i = 0;
	while (s_global->miniEnv[i])
	{
		if ((ft_strnstr(s_global->miniEnv[i], s_global->pathVarTempo, ft_strlen(s_global->pathVarTempo)) != NULL) && s_global->miniEnv[i][ft_strlen(s_global->pathVarTempo)] == '=')
		{
			printf("La variable existe bien\n");
			break;
		}
		i++;
	}
	if (s_global->miniEnv[i] == 0)
	{
		printf("La variable n'existe pas\n");
		return (0);
	}
	return (1);
}

int	varEnvChang(s_global *s_global)
{
	int	i;
	int	j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	s_global->inputVarEnv = malloc(sizeof(char)*99999);
	// CREER FONCTION QUI COMPTE LA TAILLE DU MALLOC POUR FAIRE BIEN
	while (s_global->input[i])
	{
		// passer les quotes simple
		if (s_global->input[i] == 39)
		{
			s_global->inputVarEnv[i + j] = s_global->input[i + k];
			i++;
			while (s_global->input[i] != 39)
			{
				s_global->inputVarEnv[i + j] = s_global->input[i + k];
				i++;
			}
			s_global->inputVarEnv[i + j] = s_global->input[i + k];
		}
		//j = j + skipSingleQuote(s_global, i, env);
		else if (s_global->input[i] == 36)
		{	
			if (checkVar(s_global, i) != 0)
			{
				j = j + addVar(s_global, i);
				k = k + ft_strlen(s_global->pathVarTempo);
			}
			else
			{
				free(s_global->inputVarEnv);
				return (0);
			}
		}
		else
			s_global->inputVarEnv[i + j] = s_global->input[i + k];
		i++;
	}
	s_global->inputVarEnv[i + j + 1] = 0;
	printf("Prompt fin traitement var : %s\n", s_global->inputVarEnv);
	return (1);
}