/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sorti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/09/19 22:43:29 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	basic_out(int *i, s_g *s_g, to_lst *to_lst)
{
	char	*str_tempo;
	int		k;

	k = 0;
	str_tempo = malloc (sizeof(char) * 9999);
	(*i)++;
	while (s_g->i2[s_g->sStr + (*i)] == ' '
		&& s_g->i2[s_g->sStr + (*i)] != 0)
		(*i)++;
	while (s_g->i2[s_g->sStr + (*i)] != ' '
		&& s_g->i2[s_g->sStr + (*i)] != 0
		&& s_g->i2[s_g->sStr + (*i)] != '>'
		&& s_g->i2[s_g->sStr + (*i)] != '<'
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
	add_token(to_lst, str_tempo, 4, s_g);
	free(str_tempo);
}

void	sorti_append(int *i, s_g *s_g, to_lst *to_lst)
{
	char	*str_tempo;
	int		k;

	k = 0;
	str_tempo = malloc (sizeof(char) * 9999);
	(*i) = (*i) + 2;
	while (s_g->i2[s_g->sStr + (*i)] == ' '
		&& s_g->i2[s_g->sStr + (*i)] != 0)
		(*i)++;
	while (s_g->i2[s_g->sStr + (*i)] != ' '
		&& s_g->i2[s_g->sStr + (*i)] != 0
		&& s_g->i2[s_g->sStr + (*i)] != '>'
		&& s_g->i2[s_g->sStr + (*i)] != '<'
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
	add_token(to_lst, str_tempo, 6, s_g);
	free(str_tempo);
}

int	put_sorti(s_g *s_g, to_lst *to_lst)
{
	int	i;

	i = 0;
	while (i < s_g->lgStr)
	{
		if (s_g->i2[s_g->sStr + i] == '"' || s_g->i2[s_g->sStr + i] == '\'')
			pass_quote(s_g, &i, s_g->i2[s_g->sStr + i]);
		if (s_g->i2[s_g->sStr + i] == '>' && s_g->i2[s_g->sStr + i + 1] != '>')
		{
			if (s_g->i2[s_g->sStr + i + 1] == '<'
				|| s_g->i2[s_g->sStr + i + 1] == '|')
				return (0);
			basic_out(&i, s_g, to_lst);
		}
		else if (s_g->i2[s_g->sStr + i] == '>'
			&& s_g->i2[s_g->sStr + i + 1] == '>')
		{
			if (s_g->i2[s_g->sStr + i + 2] == '>'
				|| s_g->i2[s_g->sStr + i + 2] == '<')
				return (0);
			sorti_append(&i, s_g, to_lst);
		}
		i++;
	}
	return (1);
}
