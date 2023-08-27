/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/08/27 02:24:07 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	seek_next_pipe(s_g *s_g, int startStr)
{
	int	lg_str;

	lg_str = 0;
	while (s_g->i2[startStr + lg_str] != 0 
		&& s_g->i2[startStr + lg_str] != '|')
	{
		if (s_g->i2[startStr + lg_str] == '\'')
		{
			lg_str++;
			while (s_g->i2[startStr + lg_str] != '\'')
				lg_str++;
		}
		if (s_g->i2[startStr + lg_str] == '"')
		{
			lg_str++;
			while (s_g->i2[startStr + lg_str] != '"')
				lg_str++;
		}
		lg_str++;
	}
	return (lg_str);
}

int	add_list_exec(s_g *s_g, to_lst *to_lst)
{
	s_g->startStr = 0;
	s_g->lgStr = 0;
	while (s_g->i2[s_g->startStr + s_g->lgStr] != 0)
	{
		s_g->startStr = s_g->startStr + s_g->lgStr;
		s_g->lgStr = seek_next_pipe(s_g, s_g->startStr);
		put_maillon_str(s_g, to_lst);
		if (put_entry(s_g, to_lst) == 0)
		{
			printf("Probleme dans les entrees");
			return (0);
		}
		if (put_sorti(s_g, to_lst) == 0)
		{
			printf("Probleme dans les sorties");
			return (0);
		}
		if (s_g->i2[s_g->startStr + s_g->lgStr] == '|')
		{
			add_token(to_lst, "|", 2, s_g);
			s_g->startStr++;
		}
	}
	return (1);
}