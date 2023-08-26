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

// EXEMPLE : echo 12 > sorti 34 | echo 123 | rev > sorti 2

int	seek_next_pipe(s_gbl *s_gbl, int startStr)
{
	int	lgStr;

	lgStr = 0;
	while (s_gbl->inputVarEnv[startStr + lgStr] != 0 && s_gbl->inputVarEnv[startStr + lgStr] != '|')
	{
		if (s_gbl->inputVarEnv[startStr + lgStr] == '\'')
		{
			lgStr++;
			while (s_gbl->inputVarEnv[startStr + lgStr] != '\'')
				lgStr++;
		}
		if (s_gbl->inputVarEnv[startStr + lgStr] == '"')
		{
			lgStr++;
			while (s_gbl->inputVarEnv[startStr + lgStr] != '"')
				lgStr++;
		}
		lgStr++;
	}
	printf("Test longueur Str jusqu'au prochain pipe : %d\n", lgStr);

	return (lgStr);
}

int	put_red_deli_str(s_gbl *s_gbl, int startStr, int lgStr, TokenList *token_list) // A FAIRE
{
	char	*strTempo;
	int	i;
	int	k;

	i = 0;
	strTempo = malloc (sizeof(char) * 9999);
	while (i < lgStr)
	{
		k = 0;
		if (s_gbl->inputVarEnv[startStr + i] == '>' && s_gbl->inputVarEnv[startStr + i + 1] == '>' && s_gbl->inputVarEnv[startStr + i - 1] != '>')
		{
			if (s_gbl->inputVarEnv[startStr + i + 2] == '>' || s_gbl->inputVarEnv[startStr + i + 2] == '<')
			{
				printf("Caractere '%c' interdit apres delimiteur\n", s_gbl->inputVarEnv[startStr + i + 2]);
				return (0);
			}
			i = i + 2;
			while (s_gbl->inputVarEnv[startStr + i] == ' ' && s_gbl->inputVarEnv[startStr + i] != 0)
				i++;
			while (s_gbl->inputVarEnv[startStr + i] != ' ' && s_gbl->inputVarEnv[startStr + i] != 0 
				&& s_gbl->inputVarEnv[startStr + i] != '>' && s_gbl->inputVarEnv[startStr + i] != '<')
			{
				strTempo[k] = s_gbl->inputVarEnv[startStr + i];
				i++;
				k++;
			}
			if (s_gbl->inputVarEnv[startStr + i] == '>' || s_gbl->inputVarEnv[startStr + i] == '<')
				i--;
			strTempo[k] = 0;
			addToken(token_list, strTempo, 5, s_gbl);
		}
		i++;
	}
	free(strTempo);
	return (1);
}

int	put_red_in_str(s_gbl *s_gbl, int startStr, int lgStr, TokenList *token_list)
{
	char	*strTempo;
	int	i;
	int	k;

	i = 0;
	strTempo = malloc (sizeof(char) * 9999);
	while (i < lgStr)
	{
		k = 0;
		if (s_gbl->inputVarEnv[startStr + i] == '<' && s_gbl->inputVarEnv[startStr + i + 1] != '<' && s_gbl->inputVarEnv[startStr + i - 1] != '<')
		{
			if (s_gbl->inputVarEnv[startStr + i + 1] == '>')
				i++;
			i++;
			while (s_gbl->inputVarEnv[startStr + i] == ' ' && s_gbl->inputVarEnv[startStr + i] != 0)
				i++;
			while (s_gbl->inputVarEnv[startStr + i] != ' ' && s_gbl->inputVarEnv[startStr + i] != 0 
				&& s_gbl->inputVarEnv[startStr + i] != '<' && s_gbl->inputVarEnv[startStr + i] != '>')
			{
				strTempo[k] = s_gbl->inputVarEnv[startStr + i];
				i++;
				k++;
			}
			if (s_gbl->inputVarEnv[startStr + i] == '<' || s_gbl->inputVarEnv[startStr + i] == '>')
				i--;
			strTempo[k] = 0;
			printf("Test redi test : %s\n", strTempo);
			addToken(token_list, strTempo, 3, s_gbl);
		}
		i++;
	}
	free(strTempo);
	return (1);
}

int	put_red_out_str(s_gbl *s_gbl, int startStr, int lgStr, TokenList *token_list)
{
	char	*strTempo;
	int	i;
	int	k;

	i = 0;
	strTempo = malloc (sizeof(char) * 9999);
	printf("========SLT======\n");
	while (i < lgStr)
	{
		k = 0;
		if (s_gbl->inputVarEnv[startStr + i] == '>' && s_gbl->inputVarEnv[startStr + i + 1] != '>' && s_gbl->inputVarEnv[startStr + i - 1] != '>')
		{
			if (s_gbl->inputVarEnv[startStr + i + 1] == '<')
			{
				printf("Pas le droit de faire >< frerot\n");
				return (0);
			}
			printf("========lancement======\n");
			i++;
			while (s_gbl->inputVarEnv[startStr + i] == ' ' && s_gbl->inputVarEnv[startStr + i] != 0)
				i++;
			while (s_gbl->inputVarEnv[startStr + i] != ' ' && s_gbl->inputVarEnv[startStr + i] != 0 
				&& s_gbl->inputVarEnv[startStr + i] != '>' && s_gbl->inputVarEnv[startStr + i] != '<')
			{
				strTempo[k] = s_gbl->inputVarEnv[startStr + i];
				i++;
				k++;
			}
			if (s_gbl->inputVarEnv[startStr + i] == '>' || s_gbl->inputVarEnv[startStr + i] == '<')
				i--;
			strTempo[k] = 0;
			printf("Test redi test : %s\n", strTempo);
			addToken(token_list, strTempo, 4, s_gbl);
		}
		i++;
	}
	free(strTempo);
	return (1);
}

int	put_red_append_str(s_gbl *s_gbl, int startStr, int lgStr, TokenList *token_list) // A FAIRE
{
	char	*strTempo;
	int	i;
	int	k;

	i = 0;
	strTempo = malloc (sizeof(char) * 9999);
	while (i < lgStr)
	{
		k = 0;
		if (s_gbl->inputVarEnv[startStr + i] == '<' && s_gbl->inputVarEnv[startStr + i + 1] == '<' && s_gbl->inputVarEnv[startStr + i - 1] != '<')
		{
			if (s_gbl->inputVarEnv[startStr + i + 2] == '>' || s_gbl->inputVarEnv[startStr + i + 2] == '<')
			{
				printf("Caractere '%c' interdit apres append\n", s_gbl->inputVarEnv[startStr + i + 2]);
				return (0);
			}
			i = i + 2;
			while (s_gbl->inputVarEnv[startStr + i] == ' ' && s_gbl->inputVarEnv[startStr + i] != 0)
				i++;
			while (s_gbl->inputVarEnv[startStr + i] != ' ' && s_gbl->inputVarEnv[startStr + i] != 0 
				&& s_gbl->inputVarEnv[startStr + i] != '>' && s_gbl->inputVarEnv[startStr + i] != '<')
			{
				strTempo[k] = s_gbl->inputVarEnv[startStr + i];
				i++;
				k++;
			}
			if (s_gbl->inputVarEnv[startStr + i] == '>' || s_gbl->inputVarEnv[startStr + i] == '<')
				i--;
			strTempo[k] = 0;
			addToken(token_list, strTempo, 6, s_gbl);
		}
		i++;
	}
	free(strTempo);
	return (1);
}

int	add_list_exec(s_gbl *s_gbl, TokenList *token_list)
{
	int	startStr;
	int	lgStr;

	startStr = 0;
	lgStr = 0;
	while (s_gbl->inputVarEnv[startStr + lgStr] != 0)
	{
		startStr = startStr + lgStr;
		lgStr = seek_next_pipe(s_gbl, startStr);
		// CODE
		put_maillon_str(s_gbl, startStr, lgStr, token_list);
		put_red_deli_str(s_gbl, startStr, lgStr, token_list);
		put_red_in_str(s_gbl, startStr, lgStr, token_list);
		put_red_out_str(s_gbl, startStr, lgStr, token_list);
		put_red_append_str(s_gbl, startStr, lgStr, token_list);

		if (s_gbl->inputVarEnv[startStr + lgStr] == '|')
		{
			addToken(token_list, "|", 2, s_gbl);
			startStr++;
		}
	}
	printf("-------Fin de add_list_exec-------\n");
	return (1);
}

int	check_pipe_at_start(s_gbl *s_gbl)
{
	int	i;

	i = 0;
	while (s_gbl->inputVarEnv[i] == ' ' && s_gbl->inputVarEnv[i] != 0)
		i++;
	if (s_gbl->inputVarEnv[i] == '|')
		return (0);
	printf("Pas de pipe au debut\n");
	return (1);
}

int	parsing(s_gbl *s_gbl, TokenList *token_list)
{
	if (quote_check(s_gbl->input) == 0)
	{
		printf("!!! Error quote\n");
		return (0);
	}
	if (var_env_chang(s_gbl) == 0)
	{
		printf("Variable Env inexistante\n");
		return (0);
	}
	if (check_pipe_at_start(s_gbl) == 0)
	{
		printf("Le ptit pipe est solo bolo devant\n");
		return (0);
	}

	/*if (redirection(s_gbl) == 0)
	{
		printf("Probleme redirection\n");
		return (0);
	}*/
	add_list_exec(s_gbl, token_list);
	printf("Parsing passe, tout est GOOD !!!\n");
	return (1);
}
