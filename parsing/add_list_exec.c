/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/09/19 22:25:06 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	seek_next_pipe(t_g *t_g, int s_st)
{
	int	lg_str;

	lg_str = 0;
	while (t_g->i2[s_st + lg_str] != 0
		&& t_g->i2[s_st + lg_str] != '|')
	{
		if (t_g->i2[s_st + lg_str] == '\'')
		{
			lg_str++;
			while (t_g->i2[s_st + lg_str] != '\'')
				lg_str++;
		}
		if (t_g->i2[s_st + lg_str] == '"')
		{
			lg_str++;
			while (t_g->i2[s_st + lg_str] != '"')
				lg_str++;
		}
		lg_str++;
	}
	return (lg_str);
}

int	add_list_exec(t_g *t_g, t_lst *t_lst)
{
	t_g->s_st = 0;
	t_g->ls_st = 0;
	while (t_g->i2[t_g->s_st + t_g->ls_st] != 0)
	{
		t_g->s_st = t_g->s_st + t_g->ls_st;
		t_g->ls_st = seek_next_pipe(t_g, t_g->s_st);
		put_maillon_str(t_g, t_lst);
		if (put_entry(t_g, t_lst) == 0)
		{
			printf("Probleme dans les entrees");
			return (0);
		}
		if (put_sorti(t_g, t_lst) == 0)
		{
			printf("Probleme dans les sorties");
			return (0);
		}
		if (t_g->i2[t_g->s_st + t_g->ls_st] == '|')
		{
			add_token(t_lst, "|", 2, t_g);
			t_g->s_st++;
		}
	}
	return (1);
}
