/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/09/19 22:35:00 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pass_quote(s_g *sg, int *i, char quote)
{
	(*i)++;
	while (sg->i2[sg->sStr + (*i)] != quote)
	{
		if (sg->i2[sg->sStr + (*i)] == '\0')
		{
			break ;
		}
		(*i)++;
	}
	(*i)++;
}

void	basic_entry(int *i, s_g *s_g, to_lst *to_lst)
{
	char	*str_tempo;
	int		k;

	k = 0;
	str_tempo = malloc(sizeof(char) * 9999);
	if (s_g->i2[s_g->sStr + (*i) + 1] == '>')
		(*i)++;
	(*i)++;
	while (s_g->i2[s_g->sStr + (*i)] == ' '
		&& s_g->i2[s_g->sStr + (*i)] != 0)
		(*i)++;
	while (s_g->i2[s_g->sStr + (*i)] != ' ' && s_g->i2[s_g->sStr + (*i)] != 0
		&& s_g->i2[s_g->sStr + (*i)] != '<' && s_g->i2[s_g->sStr + (*i)] != '>'
		&& s_g->i2[s_g->sStr + (*i)] != '|')
	{
		str_tempo[k++] = s_g->i2[s_g->sStr + (*i)];
		(*i)++;
	}
	if (s_g->i2[s_g->sStr + (*i)] == '<'
		|| s_g->i2[s_g->sStr + (*i)] == '>')
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
	while (s_g->i2[s_g->sStr + (*i)] == ' '
		&& s_g->i2[s_g->sStr + (*i)] != 0)
		(*i)++;
	while (s_g->i2[s_g->sStr + (*i)] != ' ' && s_g->i2[s_g->sStr + (*i)] != 0
		&& s_g->i2[s_g->sStr + (*i)] != '>' && s_g->i2[s_g->sStr + (*i)] != '<'
		&& s_g->i2[s_g->sStr + (*i)] != '|')
	{
		str_tempo[k] = s_g->i2[s_g->sStr + (*i)];
		(*i)++;
		k++;
	}
	if (s_g->i2[s_g->sStr + (*i)] == '>'
		|| s_g->i2[s_g->sStr + (*i)] == '<')
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
		if (sg->i2[sg->sStr + i] == '"' || sg->i2[sg->sStr + i] == '\'')
			pass_quote(sg, &i, sg->i2[sg->sStr + i]);
		if (sg->i2[sg->sStr + i] == '<' && sg->i2[sg->sStr + i + 1] == '<')
		{
			if (sg->i2[sg->sStr + i + 2] == '>'
				|| sg->i2[sg->sStr + i + 2] == '<'
				|| sg->i2[sg->sStr + i + 2] == '|')
				return (0);
			entry_delimiteur(&i, sg, to_lst);
		}
		else if (sg->i2[sg->sStr + i] == '<')
		{
			if (sg->i2[sg->sStr + i + 1] == '|'
				|| sg->i2[sg->sStr + i + 2] == '|')
				return (0);
			basic_entry(&i, sg, to_lst);
		}
		i++;
	}
	return (1);
}
