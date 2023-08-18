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

int	varEnvChang(char	*input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == 36)
		{
			// A FAIRE NEXT : CHANGER PROMPT AVEC LA VARIABLE
			// SUREMENT SE PENCHER SUR MALLOC
			// PRENDRE EN COMPTE QUE SI PLUSIEURS $ CA NE MARCHE PAS LA
			printf("Trouver, valeur i : %d\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	parsing(s_global *s_global)
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
	if (varEnvChang(s_global->input))
		printf("Var trouver et changer :)\n");
	mallocSize(s_global->input);

	free(inputReturn);

	return (1);
}