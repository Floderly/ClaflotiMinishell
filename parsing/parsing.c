/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/09/15 18:44:03 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(s_g *s_g, to_lst *to_lst)
{
	if (quote_check(s_g->input) == 0)
	{
		s_g->exit_ret = 2;
		printf("!!! Error quote\n");
		return (0);
	}
	if (var_env_chang(s_g) == 0)
	{
		printf("Variable Env inexistante\n");
		return (0);
	}
	if (check_pipe_at_start(s_g) == 0)
		return (0);
	add_list_exec(s_g, to_lst);
	if (check_empty_prompt(to_lst) == 0)
	{
		s_g->exit_ret = 127;
		printf("cmd <input >output | <repeat>\n");
		return (0);
	}
	if (check_files_exist(to_lst, s_g) == 0)
		return (0);
	//afficher_tokens(to_lst);
	return (1);
}
