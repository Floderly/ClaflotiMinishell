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

void	process_single_quote(char *strtempo, int *i, int *redi_r, s_gbl *s_gbl)
{
	strtempo[*i] = s_gbl->inputVarEnv[s_gbl->startStr + *i + *redi_r];
	(*i)++;
	while (s_gbl->inputVarEnv[s_gbl->startStr + *i + *redi_r] != '\'')
	{
		strtempo[*i] = s_gbl->inputVarEnv[s_gbl->startStr + *i + *redi_r];
		(*i)++;
	}
	strtempo[*i] = s_gbl->inputVarEnv[s_gbl->startStr + *i + *redi_r];
}

void	process_double_quote(char *strtempo, int *i, int *redi_r, s_gbl *s_gbl)
{
	strtempo[*i] = s_gbl->inputVarEnv[s_gbl->startStr + *i + *redi_r];
	(*i)++;
	while (s_gbl->inputVarEnv[s_gbl->startStr + *i + *redi_r] != '"')
	{
		strtempo[*i] = s_gbl->inputVarEnv[s_gbl->startStr + *i + *redi_r];
		(*i)++;
	}
	strtempo[*i] = s_gbl->inputVarEnv[s_gbl->startStr + *i + *redi_r];
}

void	process_redi_rection(char *strtempo, int *i, int *redi_r, s_gbl *s_gbl)
{
	(*redi_r)++;
	while (s_gbl->inputVarEnv[s_gbl->startStr + (*i) + (*redi_r)] == ' ' 
		&& s_gbl->inputVarEnv[s_gbl->startStr + (*i) + (*redi_r)] != 0)
		(*redi_r)++;
	while (s_gbl->inputVarEnv[s_gbl->startStr + (*i) + (*redi_r)] != ' '
		&& s_gbl->inputVarEnv[s_gbl->startStr + (*i) + (*redi_r)] != 0
		&& s_gbl->inputVarEnv[s_gbl->startStr + (*i) + (*redi_r)] != '>'
		&& s_gbl->inputVarEnv[s_gbl->startStr + (*i) + (*redi_r)] != '<')
		(*redi_r)++;
	strtempo[(*i)] = ' ';
	(*redi_r)--;
}

void	put_maillon_str(s_gbl *s_gbl, TokenList *token_list)
{
	char	*strtempo;
	int		i;
	int		redi_r;

	redi_r = 0;
	i = 0;
	strtempo = malloc (sizeof(char) * 9999);
	while (i + redi_r < s_gbl->lgStr)
	{
		if (s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r] == '\'')
			process_single_quote(strtempo, &i, &redi_r, s_gbl);
		else if (s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r] == '"')
			process_double_quote(strtempo, &i, &redi_r, s_gbl);
		else if (s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r] == '>' 
			|| s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r] == '<')
			process_redi_rection(strtempo, &i, &redi_r, s_gbl);
		else
			strtempo[i] = s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r];
		i++;
	}
	strtempo[i] = 0;
	addToken(token_list, strtempo, 1, s_gbl);
	free (strtempo);
}

/*
ANCIEN PUT_MAILLON_STR, QUI ENLEVE LES QUOTES
void	put_maillon_str(s_gbl *s_gbl, int s_gbl->startStr, int lgStr, TokenList *token_list)
{
	char	*strtempo;
	int	i;
	int	quoteR;
	int	redi_r;

	redi_r = 0;
	quoteR = 0;
	i = 0;
	strtempo = malloc (sizeof(char) * 9999);
	while (i + redi_r < lgStr) //rajouter quoteR ????
	{
		if (s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r] == '\'')
		{
			i++;
			quoteR++;
			while (s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r] != '\'')
			{
				strtempo[i - quoteR] = s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r];
				i++;
			}
			quoteR++;
		}
		else if (s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r] == '"')
		{
			printf("Je rentre double quote////////////\n");
			i++;
			quoteR++;
			while (s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r] != '"')
			{
				strtempo[i - quoteR] = s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r];
				i++;
			}
			quoteR++;
		}
		else if (s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r] == '>' || s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r] == '<')
		{
			redi_r++;
			while (s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r] == ' ' && s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r] != 0)
				redi_r++;
			while (s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r] != ' ' && s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r] != 0)
				redi_r++;
			printf("Print redi_rect : %c\n", s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r]);
			strtempo[i - quoteR] = s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r];
		}
		else
		{
			printf("Test print normal : %c\n", s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r]);
			strtempo[i - quoteR] = s_gbl->inputVarEnv[s_gbl->startStr + i + redi_r];
		}
		i++;
	}
	strtempo[i - quoteR] = 0;
	printf("Test putMaillonStr : %s\n", strtempo);
	addToken(token_list, strtempo, 1, s_gbl);
	free (strtempo);
}
*/