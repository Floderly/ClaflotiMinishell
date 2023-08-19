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

int	mallocSize(char *input)
{
	// PAS FAIT
	return (4);
}

int	quoteCheck(char *input)
{
	int	i;
	int singleQuoteNb;
	int doubleQuoteNb;

	i = 0;
	singleQuoteNb = 0;
	doubleQuoteNb = 0;
	while (input[i])
	{
		if (input[i] == 34)
			doubleQuoteNb++;
		if (input[i] == 39)
			singleQuoteNb++;
		i++;
	}
	if (singleQuoteNb % 2 == 1 || doubleQuoteNb % 2 == 1)
	{
		printf("Single : %d et double : %d\n", singleQuoteNb, doubleQuoteNb);
		return (0);
	}
	return (1);
}

int	addVar(s_global *s_global, int i, char **env)
{
	// FAIRE SOUS FONCTION QUI RECHERCHE LE CONTENU A METTRE ?
	char *varTamp;

	i = 0;
	char *pathVarTest = "GDMSESSION";
	varTamp = malloc(sizeof(char)*99999);
	while ((ft_strnstr(env[i], pathVarTest, ft_strlen(pathVarTest)) == NULL) && env[i] != 0)
	{
		printf("Test addVarBoucle : %s", env[i]);

		i++;
	}
	printf("\n\nTest addVar : %s et valeur i : %d\n", env[i], i);
	printf("\n\nTest viKing : %s\n\n", env[57]);
	return (1);
}

int	varEnvChang(s_global *s_global, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	s_global->inputVar = malloc(sizeof(char)*99999);
	// CREER FONCTION QUI COMPTE LA TAILLE DU MALLOC POUR FAIRE BIEN
	while (s_global->input[i])
	{
		if (s_global->input[i] == 36)
		{
			j = j + addVar(s_global, i, env);
			printf("Trouver, valeur i : %d\n", i);
			i++;
			j--;
		}
		else
			s_global->inputVar[i + j] = s_global->input[i];
		i++;
	}
	return (1);
}

int	parsing(s_global *s_global, char **env)
{
	/////////
	char *inputReturn;

	inputReturn = malloc(sizeof(char) * 99999);
	inputReturn[0] = 'a';
	inputReturn[1] = 'b';
	inputReturn[2] = 'c';
	inputReturn[3] = 0;

	s_global->input2 = inputReturn;
	//////////

	if (!(quoteCheck(s_global->input)))
	{
		printf("!!! Error quote\n");
		return (0);
	}
	if (varEnvChang(s_global, env))
		printf("Var trouver et changer :)\n");
	mallocSize(s_global->input);

	free(inputReturn);

	return (1);
}