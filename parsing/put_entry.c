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

void	pass_quote(t_g *sg, int *i, char quote)
{
	(*i)++;
	while (sg->i2[sg->s_st + (*i)] != quote)
	{
		if (sg->i2[sg->s_st + (*i)] == '\0')
		{
			break ;
		}
		(*i)++;
	}
	(*i)++;
}

void	basic_entry(int *i, t_g *t_g, t_lst *t_lst)
{
	char	*str_tempo;
	int		k;

	k = 0;
	str_tempo = malloc(sizeof(char) * 9999);
	if (t_g->i2[t_g->s_st + (*i) + 1] == '>')
		(*i)++;
	(*i)++;
	while (t_g->i2[t_g->s_st + (*i)] == ' '
		&& t_g->i2[t_g->s_st + (*i)] != 0)
		(*i)++;
	while (t_g->i2[t_g->s_st + (*i)] != ' ' && t_g->i2[t_g->s_st + (*i)] != 0
		&& t_g->i2[t_g->s_st + (*i)] != '<' && t_g->i2[t_g->s_st + (*i)] != '>'
		&& t_g->i2[t_g->s_st + (*i)] != '|')
	{
		str_tempo[k++] = t_g->i2[t_g->s_st + (*i)];
		(*i)++;
	}
	if (t_g->i2[t_g->s_st + (*i)] == '<'
		|| t_g->i2[t_g->s_st + (*i)] == '>')
		(*i)--;
	str_tempo[k] = 0;
	add_token(t_lst, str_tempo, 3, t_g);
	free(str_tempo);
}

void	entry_delimiteur(int *i, t_g *t_g, t_lst *t_lst)
{
	char	*str_tempo;
	int		k;

	k = 0;
	str_tempo = malloc (sizeof(char) * 9999);
	(*i) = (*i) + 2;
	while (t_g->i2[t_g->s_st + (*i)] == ' '
		&& t_g->i2[t_g->s_st + (*i)] != 0)
		(*i)++;
	while (t_g->i2[t_g->s_st + (*i)] != ' ' && t_g->i2[t_g->s_st + (*i)] != 0
		&& t_g->i2[t_g->s_st + (*i)] != '>' && t_g->i2[t_g->s_st + (*i)] != '<'
		&& t_g->i2[t_g->s_st + (*i)] != '|')
	{
		str_tempo[k] = t_g->i2[t_g->s_st + (*i)];
		(*i)++;
		k++;
	}
	if (t_g->i2[t_g->s_st + (*i)] == '>'
		|| t_g->i2[t_g->s_st + (*i)] == '<')
		(*i)--;
	str_tempo[k] = 0;
	add_token(t_lst, str_tempo, 5, t_g);
	free(str_tempo);
}

int	put_entry(t_g *sg, t_lst *t_lst)
{
	int	i;

	i = 0;
	while (i < sg->ls_st)
	{
		if (sg->i2[sg->s_st + i] == '"' || sg->i2[sg->s_st + i] == '\'')
			pass_quote(sg, &i, sg->i2[sg->s_st + i]);
		if (sg->i2[sg->s_st + i] == '<' && sg->i2[sg->s_st + i + 1] == '<')
		{
			if (sg->i2[sg->s_st + i + 2] == '>'
				|| sg->i2[sg->s_st + i + 2] == '<'
				|| sg->i2[sg->s_st + i + 2] == '|')
				return (0);
			entry_delimiteur(&i, sg, t_lst);
		}
		else if (sg->i2[sg->s_st + i] == '<')
		{
			if (sg->i2[sg->s_st + i + 1] == '|'
				|| sg->i2[sg->s_st + i + 2] == '|')
				return (0);
			basic_entry(&i, sg, t_lst);
		}
		i++;
	}
	return (1);
}
