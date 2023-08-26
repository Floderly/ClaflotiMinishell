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

void processSingleQuote(char *strTempo, int *i, int *rediR, int startStr, s_gbl *s_gbl)
{
	
}
void	put_maillon_str(s_gbl *s_gbl, int startStr, int lgStr, TokenList *token_list)
{
	char	*strTempo;
	int	i;
	int	rediR;

	rediR = 0;
	i = 0;
	strTempo = malloc (sizeof(char) * 9999);
	while (i + rediR < lgStr)
	{
		if (s_gbl->inputVarEnv[startStr + i + rediR] == '\'')
		{
			strTempo[i] = s_gbl->inputVarEnv[startStr + i + rediR];
			i++;
			while (s_gbl->inputVarEnv[startStr + i + rediR] != '\'')
			{
				strTempo[i] = s_gbl->inputVarEnv[startStr + i + rediR];
				i++;
			}
			strTempo[i] = s_gbl->inputVarEnv[startStr + i + rediR];
		}
		else if (s_gbl->inputVarEnv[startStr + i + rediR] == '"')
		{
			strTempo[i] = s_gbl->inputVarEnv[startStr + i + rediR];
			i++;
			while (s_gbl->inputVarEnv[startStr + i + rediR] != '"')
			{
				strTempo[i] = s_gbl->inputVarEnv[startStr + i + rediR];
				i++;
			}
			strTempo[i] = s_gbl->inputVarEnv[startStr + i + rediR];
		}
		else if (s_gbl->inputVarEnv[startStr + i + rediR] == '>' || s_gbl->inputVarEnv[startStr + i + rediR] == '<')
		{
			rediR++;
			while (s_gbl->inputVarEnv[startStr + i + rediR] == ' ' && s_gbl->inputVarEnv[startStr + i + rediR] != 0)
				rediR++;
			while (s_gbl->inputVarEnv[startStr + i + rediR] != ' ' && s_gbl->inputVarEnv[startStr + i + rediR] != 0)
				rediR++;
			strTempo[i] = s_gbl->inputVarEnv[startStr + i + rediR];
		}
		else
			strTempo[i] = s_gbl->inputVarEnv[startStr + i + rediR];
		i++;
	}
	strTempo[i] = 0;
	addToken(token_list, strTempo, 1, s_gbl);
	free (strTempo);
}

/*
ANCIEN PUT_MAILLON_STR, QUI ENLEVE LES QUOTES
void	put_maillon_str(s_gbl *s_gbl, int startStr, int lgStr, TokenList *token_list)
{
	char	*strTempo;
	int	i;
	int	quoteR;
	int	rediR;

	rediR = 0;
	quoteR = 0;
	i = 0;
	strTempo = malloc (sizeof(char) * 9999);
	while (i + rediR < lgStr) //rajouter quoteR ????
	{
		if (s_gbl->inputVarEnv[startStr + i + rediR] == '\'')
		{
			i++;
			quoteR++;
			while (s_gbl->inputVarEnv[startStr + i + rediR] != '\'')
			{
				strTempo[i - quoteR] = s_gbl->inputVarEnv[startStr + i + rediR];
				i++;
			}
			quoteR++;
		}
		else if (s_gbl->inputVarEnv[startStr + i + rediR] == '"')
		{
			printf("Je rentre double quote////////////\n");
			i++;
			quoteR++;
			while (s_gbl->inputVarEnv[startStr + i + rediR] != '"')
			{
				strTempo[i - quoteR] = s_gbl->inputVarEnv[startStr + i + rediR];
				i++;
			}
			quoteR++;
		}
		else if (s_gbl->inputVarEnv[startStr + i + rediR] == '>' || s_gbl->inputVarEnv[startStr + i + rediR] == '<')
		{
			rediR++;
			while (s_gbl->inputVarEnv[startStr + i + rediR] == ' ' && s_gbl->inputVarEnv[startStr + i + rediR] != 0)
				rediR++;
			while (s_gbl->inputVarEnv[startStr + i + rediR] != ' ' && s_gbl->inputVarEnv[startStr + i + rediR] != 0)
				rediR++;
			printf("Print redirect : %c\n", s_gbl->inputVarEnv[startStr + i + rediR]);
			strTempo[i - quoteR] = s_gbl->inputVarEnv[startStr + i + rediR];
		}
		else
		{
			printf("Test print normal : %c\n", s_gbl->inputVarEnv[startStr + i + rediR]);
			strTempo[i - quoteR] = s_gbl->inputVarEnv[startStr + i + rediR];
		}
		i++;
	}
	strTempo[i - quoteR] = 0;
	printf("Test putMaillonStr : %s\n", strTempo);
	addToken(token_list, strTempo, 1, s_gbl);
	free (strTempo);
}
*/