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

void	extractPrompt(s_global *s_global, int i)
{

}

int	sortieAppendRedirection(s_global *s_global, int i)
{
	
}

int	entreeDeliRedirection(s_global *s_global, int i)
{
	
}

int	sortieRedirection(s_global *s_global, int i)
{
	
}

int	entreeRedirection(s_global *s_global, int i)
{
	int	k;
	int	j;

	j = 0;
	i++;
	k = 1;
	printf("Test skipSpace : %d\n", k);
	k = k + skipSpace(s_global->inputVarEnv, i);
	printf("Test skipSpace : %d\n", k);
	printf("Test du i : %d\n", i);
	printf("Test du i + k cibler : %c\n", s_global->inputVarEnv[i+k]);
	// ANOTHER MALLOC NON CALCULER ET NON GC ET NON FREE
	s_global->redirectionNameFile = malloc (sizeof(char) * 9999);
	k--;
	while (s_global->inputVarEnv[i+k+j] != 0 && s_global->inputVarEnv[i+k+j] != ' ')
	{
		s_global->redirectionNameFile[j] = s_global->inputVarEnv[i+k+j];
		j++;
	}
	s_global->redirectionNameFile[j] = 0;
	printf("Test du i : %d\n", i);
	printf("Test du j : %d\n", j);
	printf("Test du k : %d\n", k);

	printf("Test redirectionNameFile : %s\n", s_global->redirectionNameFile);

	printf("Test du return : %d\n", j + k);
	return (j + k + 2);
}

void	checkForRedirection(s_global *s_global)
{
	int	i;
	int	k;

	// ANOTHER MALLOC NON CALCULER ET NON GC ET NON FREE
	s_global->inputAfterRedi = malloc (sizeof(char) * 99999);
	i = 0;
	k = 0;
	while (s_global->inputVarEnv[i + k])
	{
		if (s_global->inputVarEnv[i + k] == '>' && s_global->inputVarEnv[i + k + 1] == '>')
			k = k + sortieAppendRedirection(s_global, i);
		else if (s_global->inputVarEnv[i + k] == '<' && s_global->inputVarEnv[i + k + 1] == '<')
			k = k + entreeDeliRedirection(s_global, i);
		else if (s_global->inputVarEnv[i + k] == '>' && s_global->inputVarEnv[i  + k- 1] != '>')
			k = k + sortieRedirection(s_global, i);
		else if (s_global->inputVarEnv[i + k] == '<' && s_global->inputVarEnv[i + k - 1] != '<')
			k = k + entreeRedirection(s_global, i);
		else
		{
			s_global->inputAfterRedi[i] = s_global->inputVarEnv[i + k];
			printf("Test char : %c\n", s_global->inputAfterRedi[i]);
			printf("Test char 2: %c\n", s_global->inputVarEnv[i + k]);
			i++;
		}
	}
	s_global->inputAfterRedi[i] = 0;
	printf("Test inputAfterRedi : %s\n", s_global->inputAfterRedi);
}

int	redirection(s_global *s_global)
{
	checkForRedirection(s_global);
	return (1);
}