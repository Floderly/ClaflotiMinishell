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

// A REUTILISER LOR DU PARSING QUAND JAURAIS AVANCER

int	entree_redirection(s_gbl *s_gbl, int i)
{
	int	k;
	int	j;

	j = 0;
	i++;
	k = 1;
	printf("Test skipSpace : %d\n", k);
	k = k + skip_space(s_gbl->inputVarEnv, i);
	printf("Test skipSpace : %d\n", k);
	printf("Test du i : %d\n", i);
	printf("Test du i + k cibler : %c\n", s_gbl->inputVarEnv[i + k]);
	// ANOTHER MALLOC NON CALCULER ET NON GC ET NON FREE
	s_gbl->redirectionNameFile = malloc (sizeof(char) * 9999);
	k--;
	while (s_gbl->inputVarEnv[i + k + j] != 0 
		&& s_gbl->inputVarEnv[i + k + j] != ' ')
	{
		s_gbl->redirectionNameFile[j] = s_gbl->inputVarEnv[i + k + j];
		j++;
	}
	s_gbl->redirectionNameFile[j] = 0;
	printf("Test du i : %d\n", i);
	printf("Test du j : %d\n", j);
	printf("Test du k : %d\n", k);
	printf("Test redirectionNameFile : %s\n", s_gbl->redirectionNameFile);
	printf("Test du return : %d\n", j + k);
	return (j + k + 2);
}

void	check_for_redirection(s_gbl *s_gbl)
{
	int	i;
	int	k;

	// ANOTHER MALLOC NON CALCULER ET NON GC ET NON FREE
	s_gbl->inputAfterRedi = gc_malloc (&s_gbl->gc ,sizeof(char) * 99999);
	i = 0;
	k = 0;
	while (s_gbl->inputVarEnv[i + k])
	{
		if (s_gbl->inputVarEnv[i + k] == '>' 
			&& s_gbl->inputVarEnv[i + k + 1] == '>')
			k = k + entree_redirection(s_gbl, i); // A FAIRE
		else if (s_gbl->inputVarEnv[i + k] == '<' 
			&& s_gbl->inputVarEnv[i + k + 1] == '<')
			k = k + entree_redirection(s_gbl, i); // A FAIRE
		else if (s_gbl->inputVarEnv[i + k] == '>' 
			&& s_gbl->inputVarEnv[i + k - 1] != '>')
			k = k + entree_redirection(s_gbl, i); // A FAIRE
		else if (s_gbl->inputVarEnv[i + k] == '<' 
			&& s_gbl->inputVarEnv[i + k - 1] != '<')
			k = k + entree_redirection(s_gbl, i);
		else
		{
			s_gbl->inputAfterRedi[i] = s_gbl->inputVarEnv[i + k];
			printf("Test char : %c\n", s_gbl->inputAfterRedi[i]);
			printf("Test char 2: %c\n", s_gbl->inputVarEnv[i + k]);
			i++;
		}
	}
	s_gbl->inputAfterRedi[i] = 0;
	printf("Test inputAfterRedi : %s\n", s_gbl->inputAfterRedi);
}

int	redirection(s_gbl *s_gbl)
{
	check_for_redirection(s_gbl);
	return (1);
}
