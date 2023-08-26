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

int	seek_next_pipe(s_gbl *s_gbl, int startStr)
{
	int	lg_str;

	lg_str = 0;
	while (s_gbl->inputVarEnv[startStr + lg_str] != 0 
		&& s_gbl->inputVarEnv[startStr + lg_str] != '|')
	{
		if (s_gbl->inputVarEnv[startStr + lg_str] == '\'')
		{
			lg_str++;
			while (s_gbl->inputVarEnv[startStr + lg_str] != '\'')
				lg_str++;
		}
		if (s_gbl->inputVarEnv[startStr + lg_str] == '"')
		{
			lg_str++;
			while (s_gbl->inputVarEnv[startStr + lg_str] != '"')
				lg_str++;
		}
		lg_str++;
	}
	return (lg_str);
}

int	add_list_exec(s_gbl *s_gbl, TokenList *token_list)
{
	s_gbl->startStr = 0;
	s_gbl->lgStr = 0;
	while (s_gbl->inputVarEnv[s_gbl->startStr + s_gbl->lgStr] != 0)
	{
		s_gbl->startStr = s_gbl->startStr + s_gbl->lgStr;
		s_gbl->lgStr = seek_next_pipe(s_gbl, s_gbl->startStr);
		put_maillon_str(s_gbl, token_list);
		put_red_deli_str(s_gbl, token_list);
		put_red_in_str(s_gbl, token_list);
		put_red_out_str(s_gbl, token_list);
		put_red_append_str(s_gbl, token_list);
		if (s_gbl->inputVarEnv[s_gbl->startStr + s_gbl->lgStr] == '|')
		{
			addToken(token_list, "|", 2, s_gbl);
			s_gbl->startStr++;
		}
	}
	return (1);
}
