/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_maillon_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/09/20 10:26:16 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_single_quote(char *strtempo, int *i, int *redi_r, t_g *t_g)
{
	(*redi_r)++;
	while (t_g->i2[t_g->s_st + *i + *redi_r] != '\'')
	{
		strtempo[*i] = t_g->i2[t_g->s_st + *i + *redi_r];
		(*i)++;
	}
	(*redi_r)++;
	(*i)--;
}

void	process_double_quote(char *strtempo, int *i, int *redi_r, t_g *t_g)
{
	(*redi_r)++;
	while (t_g->i2[t_g->s_st + *i + *redi_r] != '"')
	{
		strtempo[*i] = t_g->i2[t_g->s_st + *i + *redi_r];
		(*i)++;
	}
	(*redi_r)++;
	(*i)--;
}

void	process_redi_rection(char *strtempo, int *i, int *redi_r, t_g *t_g)
{
	(*redi_r)++;
	while (t_g->i2[t_g->s_st + (*i) + (*redi_r)] == ' '
		&& t_g->i2[t_g->s_st + (*i) + (*redi_r)] != 0)
		(*redi_r)++;
	while (t_g->i2[t_g->s_st + (*i) + (*redi_r)] != ' '
		&& t_g->i2[t_g->s_st + (*i) + (*redi_r)] != 0
		&& t_g->i2[t_g->s_st + (*i) + (*redi_r)] != '>'
		&& t_g->i2[t_g->s_st + (*i) + (*redi_r)] != '<')
		(*redi_r)++;
	strtempo[(*i)] = ' ';
	(*redi_r)--;
}

void	put_maillon_str(t_g *t_g, t_lst *t_lst)
{
	char	*strtempo;
	int		i;
	int		redi_r;

	redi_r = 0;
	i = 0;
	strtempo = malloc (sizeof(char) * 9999);
	while (i + redi_r < t_g->ls_st)
	{
		if (t_g->i2[t_g->s_st + i + redi_r] == '\'')
			process_single_quote(strtempo, &i, &redi_r, t_g);
		else if (t_g->i2[t_g->s_st + i + redi_r] == '"')
			process_double_quote(strtempo, &i, &redi_r, t_g);
		else if (t_g->i2[t_g->s_st + i + redi_r] == '>'
			|| t_g->i2[t_g->s_st + i + redi_r] == '<')
			process_redi_rection(strtempo, &i, &redi_r, t_g);
		else
			strtempo[i] = t_g->i2[t_g->s_st + i + redi_r];
		i++;
	}
	strtempo[i] = 0;
	trim_spaces(strtempo);
	add_token(t_lst, strtempo, 1, t_g);
	free (strtempo);
}
