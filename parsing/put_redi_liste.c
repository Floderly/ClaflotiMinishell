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

/*
void	entry_delimiteur()
{

}

void	entry_basique()
{
	
}

int	put_entry(s_gbl *s_gbl, TokenList *token_list)
{
	int	i;
	// METTRE TOUT LE PARSING ET LES ERROR SPECIALS
	// ENSUITE APELLE DE FONCTION AVEC CREATON STR TEMPO ET ENVOIE DU TOKEN

	i = 0;
}*/

int	put_red_deli_str(s_gbl *s_gbl, TokenList *token_list)
{
	char	*str_tempo;
	int	i;
	int	k;

	i = 0;
	str_tempo = malloc (sizeof(char) * 9999);
	while (i < s_gbl->lgStr)
	{
		k = 0;
		if (s_gbl->inputVarEnv[s_gbl->startStr + i] == '>' && s_gbl->inputVarEnv[s_gbl->startStr + i + 1] == '>' && s_gbl->inputVarEnv[s_gbl->startStr + i - 1] != '>')
		{
			if (s_gbl->inputVarEnv[s_gbl->startStr + i + 2] == '>' || s_gbl->inputVarEnv[s_gbl->startStr + i + 2] == '<' || s_gbl->inputVarEnv[s_gbl->startStr + i + 2] == '|')
			{
				printf("Caractere '%c' interdit apres delimiteur\n", s_gbl->inputVarEnv[s_gbl->startStr + i + 2]);
				return (0);
			}
			i = i + 2;
			while (s_gbl->inputVarEnv[s_gbl->startStr + i] == ' ' && s_gbl->inputVarEnv[s_gbl->startStr + i] != 0)
				i++;
			while (s_gbl->inputVarEnv[s_gbl->startStr + i] != ' ' && s_gbl->inputVarEnv[s_gbl->startStr + i] != 0 
				&& s_gbl->inputVarEnv[s_gbl->startStr + i] != '>' && s_gbl->inputVarEnv[s_gbl->startStr + i] != '<')
			{
				str_tempo[k] = s_gbl->inputVarEnv[s_gbl->startStr + i];
				i++;
				k++;
			}
			if (s_gbl->inputVarEnv[s_gbl->startStr + i] == '>' || s_gbl->inputVarEnv[s_gbl->startStr + i] == '<')
				i--;
			str_tempo[k] = 0;
			addToken(token_list, str_tempo, 5, s_gbl);
		}
		i++;
	}
	free(str_tempo);
	return (1);
}

int	put_red_in_str(s_gbl *s_gbl, TokenList *token_list)
{
	char	*str_tempo;
	int	i;
	int	k;

	i = 0;
	str_tempo = malloc (sizeof(char) * 9999);
	while (i < s_gbl->lgStr)
	{
		k = 0;
		if (s_gbl->inputVarEnv[s_gbl->startStr + i] == '<' && s_gbl->inputVarEnv[s_gbl->startStr + i + 1] != '<' && s_gbl->inputVarEnv[s_gbl->startStr + i - 1] != '<')
		{
			if (s_gbl->inputVarEnv[s_gbl->startStr + i + 1] == '|' || (s_gbl->inputVarEnv[s_gbl->startStr + i + 1] == '>' && s_gbl->inputVarEnv[s_gbl->startStr + i + 2] == '|'))
			{
				printf("Error >< ou redi avant pipe\n");
				return (0);
			}
			if (s_gbl->inputVarEnv[s_gbl->startStr + i + 1] == '>')
				i++;
			i++;
			while (s_gbl->inputVarEnv[s_gbl->startStr + i] == ' ' && s_gbl->inputVarEnv[s_gbl->startStr + i] != 0)
				i++;
			while (s_gbl->inputVarEnv[s_gbl->startStr + i] != ' ' && s_gbl->inputVarEnv[s_gbl->startStr + i] != 0 
				&& s_gbl->inputVarEnv[s_gbl->startStr + i] != '<' && s_gbl->inputVarEnv[s_gbl->startStr + i] != '>')
			{
				str_tempo[k] = s_gbl->inputVarEnv[s_gbl->startStr + i];
				i++;
				k++;
			}
			if (s_gbl->inputVarEnv[s_gbl->startStr + i] == '<' || s_gbl->inputVarEnv[s_gbl->startStr + i] == '>')
				i--;
			str_tempo[k] = 0;
			printf("Test redi test : %s\n", str_tempo);
			addToken(token_list, str_tempo, 3, s_gbl);
		}
		i++;
	}
	free(str_tempo);
	return (1);
}

int	put_red_out_str(s_gbl *s_gbl, TokenList *token_list)
{
	char	*str_tempo;
	int	i;
	int	k;

	i = 0;
	str_tempo = malloc (sizeof(char) * 9999);
	printf("========SLT======\n");
	while (i < s_gbl->lgStr)
	{
		k = 0;
		if (s_gbl->inputVarEnv[s_gbl->startStr + i] == '>' && s_gbl->inputVarEnv[s_gbl->startStr + i + 1] != '>' && s_gbl->inputVarEnv[s_gbl->startStr + i - 1] != '>')
		{
			if (s_gbl->inputVarEnv[s_gbl->startStr + i + 1] == '<' || s_gbl->inputVarEnv[s_gbl->startStr + i + 1] == '|')
			{
				printf("Error >< ou > avant pipe\n");
				return (0);
			}
			printf("========lancement======\n");
			i++;
			while (s_gbl->inputVarEnv[s_gbl->startStr + i] == ' ' && s_gbl->inputVarEnv[s_gbl->startStr + i] != 0)
				i++;
			while (s_gbl->inputVarEnv[s_gbl->startStr + i] != ' ' && s_gbl->inputVarEnv[s_gbl->startStr + i] != 0 
				&& s_gbl->inputVarEnv[s_gbl->startStr + i] != '>' && s_gbl->inputVarEnv[s_gbl->startStr + i] != '<')
			{
				str_tempo[k] = s_gbl->inputVarEnv[s_gbl->startStr + i];
				i++;
				k++;
			}
			if (s_gbl->inputVarEnv[s_gbl->startStr + i] == '>' || s_gbl->inputVarEnv[s_gbl->startStr + i] == '<')
				i--;
			str_tempo[k] = 0;
			printf("Test redi test : %s\n", str_tempo);
			addToken(token_list, str_tempo, 4, s_gbl);
		}
		i++;
	}
	free(str_tempo);
	return (1);
}

int	put_red_append_str(s_gbl *s_gbl, TokenList *token_list)
{
	char	*str_tempo;
	int	i;
	int	k;

	i = 0;
	str_tempo = malloc (sizeof(char) * 9999);
	while (i < s_gbl->lgStr)
	{
		k = 0;
		if (s_gbl->inputVarEnv[s_gbl->startStr + i] == '<' && s_gbl->inputVarEnv[s_gbl->startStr + i + 1] == '<' && s_gbl->inputVarEnv[s_gbl->startStr + i - 1] != '<')
		{
			if (s_gbl->inputVarEnv[s_gbl->startStr + i + 2] == '>' || s_gbl->inputVarEnv[s_gbl->startStr + i + 2] == '<' || s_gbl->inputVarEnv[s_gbl->startStr + i + 2] == '|')
			{
				printf("Caractere '%c' interdit apres append\n", s_gbl->inputVarEnv[s_gbl->startStr + i + 2]);
				return (0);
			}
			i = i + 2;
			while (s_gbl->inputVarEnv[s_gbl->startStr + i] == ' ' && s_gbl->inputVarEnv[s_gbl->startStr + i] != 0)
				i++;
			while (s_gbl->inputVarEnv[s_gbl->startStr + i] != ' ' && s_gbl->inputVarEnv[s_gbl->startStr + i] != 0 
				&& s_gbl->inputVarEnv[s_gbl->startStr + i] != '>' && s_gbl->inputVarEnv[s_gbl->startStr + i] != '<')
			{
				str_tempo[k] = s_gbl->inputVarEnv[s_gbl->startStr + i];
				i++;
				k++;
			}
			if (s_gbl->inputVarEnv[s_gbl->startStr + i] == '>' || s_gbl->inputVarEnv[s_gbl->startStr + i] == '<')
				i--;
			str_tempo[k] = 0;
			addToken(token_list, str_tempo, 6, s_gbl);
		}
		i++;
	}
	free(str_tempo);
	return (1);
}
