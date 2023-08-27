/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/08/27 02:24:07 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	entry_basique(int *i, s_g *s_g, to_lst *to_lst)
{
	char	*str_tempo;
	int		k;

	k = 0;
	str_tempo = malloc (sizeof(char) * 9999);
	if (s_g->i2[s_g->startStr + (*i) + 1] == '>')
		(*i)++;
	(*i)++;
	while (s_g->i2[s_g->startStr + (*i)] == ' ' 
		&& s_g->i2[s_g->startStr + (*i)] != 0)
		i++;
	while (s_g->i2[s_g->startStr + (*i)] != ' ' 
		&& s_g->i2[s_g->startStr + (*i)] != 0 
		&& s_g->i2[s_g->startStr + (*i)] != '<' 
		&& s_g->i2[s_g->startStr + (*i)] != '>')
	{
		str_tempo[k++] = s_g->i2[s_g->startStr + (*i)];
		(*i)++;
	}
	if (s_g->i2[s_g->startStr + (*i)] == '<' 
		|| s_g->i2[s_g->startStr + (*i)] == '>')
		(*i)--;
	str_tempo[k] = 0;
	add_token(to_lst, str_tempo, 3, s_g);
	free(str_tempo);
}

void	entry_delimiteur(int *i, s_g *s_g, to_lst *to_lst)
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
	add_token(to_lst, str_tempo, 5, s_g);
	free(str_tempo);
}

int	put_entry(s_g *sg, to_lst *to_lst)
{
	int	i;

	i = 0;
	while (i < sg->lgStr)
	{
		if (sg->i2[sg->startStr + i] == '<' 
			&& sg->i2[sg->startStr + i + 1] == '<')
		{
			if (sg->i2[sg->startStr + i + 2] == '>' 
				|| sg->i2[sg->startStr + i + 2] == '<'
				|| sg->i2[sg->startStr + i + 2] == '|')
				return (0);
			entry_delimiteur(&i, sg, to_lst);
		}
		else if (sg->i2[sg->startStr + i] == '<')
		{
			if (sg->i2[sg->startStr + i + 1] == '|' 
				|| (sg->i2[sg->startStr + i + 1] == '>'
					&& sg->i2[sg->startStr + i + 2] == '|'))
				return (0);
			entry_basique(&i, sg, to_lst);
		}
		i++;
	}
	return (1);
}
