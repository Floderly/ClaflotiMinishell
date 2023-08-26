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

void	sorti_basique(int *i, s_g *s_g, TokenList *token_list)
{
	char	*str_tempo;
	int		k;

	k = 0;
	str_tempo = malloc (sizeof(char) * 9999);
	(*i)++;
	while (s_g->i2[s_g->startStr + (*i)] == ' ' 
		&& s_g->i2[s_g->startStr + (*i)] != 0)
		(*i)++;
	while (s_g->i2[s_g->startStr + (*i)] != ' ' 
		&& s_g->i2[s_g->startStr + (*i)] != 0 
		&& s_g->i2[s_g->startStr + (*i)] != '>' 
		&& s_g->i2[s_g->startStr + (*i)] != '<')
	{
		str_tempo[k] = s_g->i2[s_g->startStr + (*i)];
		(*i)++;
		k++;
	}
	if (s_g->i2[s_g->startStr + (*i)] == '>' 
		|| s_g->i2[s_g->startStr + (*i)] == '<')
		(*i)--;
	str_tempo[k] = 0;
	addToken(token_list, str_tempo, 4, s_g);
	free(str_tempo);
}

void	sorti_append(int *i, s_g *s_g, TokenList *token_list)
{
	char	*str_tempo;
	int		k;

	k = 0;
	str_tempo = malloc (sizeof(char) * 9999);
	(*i) = (*i) + 2;
	while (s_g->i2[s_g->startStr + (*i)] == ' ' 
		&& s_g->i2[s_g->startStr + (*i)] != 0)
		(*i)++;
	while (s_g->i2[s_g->startStr + (*i)] != ' ' 
		&& s_g->i2[s_g->startStr + (*i)] != 0 
		&& s_g->i2[s_g->startStr + (*i)] != '>' 
		&& s_g->i2[s_g->startStr + (*i)] != '<')
	{
		str_tempo[k] = s_g->i2[s_g->startStr + (*i)];
		(*i)++;
		k++;
	}
	if (s_g->i2[s_g->startStr + (*i)] == '>' 
		|| s_g->i2[s_g->startStr + (*i)] == '<')
		(*i)--;
	str_tempo[k] = 0;
	addToken(token_list, str_tempo, 6, s_g);
	free(str_tempo);
}

int	put_sorti(s_g *s_g, TokenList *token_list)
{
	int	i;

	i = 0;
	while (i < s_g->lgStr)
	{
		if (s_g->i2[s_g->startStr + i] == '>' 
			&& s_g->i2[s_g->startStr + i + 1] != '>')
		{
			if (s_g->i2[s_g->startStr + i + 1] == '<' 
				|| s_g->i2[s_g->startStr + i + 1] == '|')
				return (0);
			sorti_basique(&i, s_g, token_list);
		}
		else if (s_g->i2[s_g->startStr + i] == '>' 
			&& s_g->i2[s_g->startStr + i + 1] == '>')
		{
			if (s_g->i2[s_g->startStr + i + 2] == '>' 
				|| s_g->i2[s_g->startStr + i + 2] == '<' 
				|| s_g->i2[s_g->startStr + i + 2] == '|')
				return (0);
			sorti_append(&i, s_g, token_list);
		}
		i++;
	}
	return (1);
}
