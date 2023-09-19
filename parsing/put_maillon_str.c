/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_maillon_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/09/19 22:40:13 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_single_quote(char *strtempo, int *i, int *redi_r, s_g *s_g)
{
	(*redi_r)++;
	while (s_g->i2[s_g->sStr + *i + *redi_r] != '\'')
	{
		strtempo[*i] = s_g->i2[s_g->sStr + *i + *redi_r];
		(*i)++;
	}
	(*redi_r)++;
	(*i)--;
}

void	process_double_quote(char *strtempo, int *i, int *redi_r, s_g *s_g)
{
	(*redi_r)++;
	while (s_g->i2[s_g->sStr + *i + *redi_r] != '"')
	{
		strtempo[*i] = s_g->i2[s_g->sStr + *i + *redi_r];
		(*i)++;
	}
	(*redi_r)++;
	(*i)--;
}

void	process_redi_rection(char *strtempo, int *i, int *redi_r, s_g *s_g)
{
	(*redi_r)++;
	while (s_g->i2[s_g->sStr + (*i) + (*redi_r)] == ' '
		&& s_g->i2[s_g->sStr + (*i) + (*redi_r)] != 0)
		(*redi_r)++;
	while (s_g->i2[s_g->sStr + (*i) + (*redi_r)] != ' '
		&& s_g->i2[s_g->sStr + (*i) + (*redi_r)] != 0
		&& s_g->i2[s_g->sStr + (*i) + (*redi_r)] != '>'
		&& s_g->i2[s_g->sStr + (*i) + (*redi_r)] != '<')
		(*redi_r)++;
	strtempo[(*i)] = ' ';
	(*redi_r)--;
}

void	put_maillon_str(s_g *s_g, to_lst *to_lst)
{
	char	*strtempo;
	int		i;
	int		redi_r;

	redi_r = 0;
	i = 0;
	strtempo = malloc (sizeof(char) * 9999);
	while (i + redi_r < s_g->lgStr)
	{
		if (s_g->i2[s_g->sStr + i + redi_r] == '\'')
			process_single_quote(strtempo, &i, &redi_r, s_g);
		else if (s_g->i2[s_g->sStr + i + redi_r] == '"')
			process_double_quote(strtempo, &i, &redi_r, s_g);
		else if (s_g->i2[s_g->sStr + i + redi_r] == '>'
			|| s_g->i2[s_g->sStr + i + redi_r] == '<')
			process_redi_rection(strtempo, &i, &redi_r, s_g);
		else
			strtempo[i] = s_g->i2[s_g->sStr + i + redi_r];
		i++;
	}
	strtempo[i] = 0;
	trimSpaces(strtempo);
	add_token(to_lst, strtempo, 1, s_g);
	free (strtempo);
}
