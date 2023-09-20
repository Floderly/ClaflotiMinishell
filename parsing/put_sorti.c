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

void	basic_out(int *i, t_g *t_g, t_lst *t_lst)
{
	char	*str_tempo;
	int		k;

	k = 0;
	str_tempo = malloc (sizeof(char) * 9999);
	(*i)++;
	while (t_g->i2[t_g->s_st + (*i)] == ' '
		&& t_g->i2[t_g->s_st + (*i)] != 0)
		(*i)++;
	while (t_g->i2[t_g->s_st + (*i)] != ' '
		&& t_g->i2[t_g->s_st + (*i)] != 0
		&& t_g->i2[t_g->s_st + (*i)] != '>'
		&& t_g->i2[t_g->s_st + (*i)] != '<'
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
	add_token(t_lst, str_tempo, 4, t_g);
	free(str_tempo);
}

void	sorti_append(int *i, t_g *t_g, t_lst *t_lst)
{
	char	*str_tempo;
	int		k;

	k = 0;
	str_tempo = malloc (sizeof(char) * 9999);
	(*i) = (*i) + 2;
	while (t_g->i2[t_g->s_st + (*i)] == ' '
		&& t_g->i2[t_g->s_st + (*i)] != 0)
		(*i)++;
	while (t_g->i2[t_g->s_st + (*i)] != ' '
		&& t_g->i2[t_g->s_st + (*i)] != 0
		&& t_g->i2[t_g->s_st + (*i)] != '>'
		&& t_g->i2[t_g->s_st + (*i)] != '<'
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
	add_token(t_lst, str_tempo, 6, t_g);
	free(str_tempo);
}

int	put_sorti(t_g *t_g, t_lst *t_lst)
{
	int	i;

	i = 0;
	while (i < t_g->ls_st)
	{
		if (t_g->i2[t_g->s_st + i] == '"' || t_g->i2[t_g->s_st + i] == '\'')
			pass_quote(t_g, &i, t_g->i2[t_g->s_st + i]);
		if (t_g->i2[t_g->s_st + i] == '>' && t_g->i2[t_g->s_st + i + 1] != '>')
		{
			if (t_g->i2[t_g->s_st + i + 1] == '<'
				|| t_g->i2[t_g->s_st + i + 1] == '|')
				return (0);
			basic_out(&i, t_g, t_lst);
		}
		else if (t_g->i2[t_g->s_st + i] == '>'
			&& t_g->i2[t_g->s_st + i + 1] == '>')
		{
			if (t_g->i2[t_g->s_st + i + 2] == '>'
				|| t_g->i2[t_g->s_st + i + 2] == '<')
				return (0);
			sorti_append(&i, t_g, t_lst);
		}
		i++;
	}
	return (1);
}
