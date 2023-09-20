/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/09/19 22:22:16 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_g *t_g, t_lst *t_lst)
{
	if (quote_check(t_g->input) == 0)
	{
		t_g->exit_ret = 2;
		printf("!!! Error quote\n");
		return (0);
	}
	if (var_env_chang(t_g) == 0)
	{
		printf("Variable Env inexistante\n");
		return (0);
	}
	if (check_pipe_at_start(t_g) == 0)
		return (0);
	add_list_exec(t_g, t_lst);
	if (check_empty_prompt(t_lst) == 0)
	{
		t_g->exit_ret = 127;
		printf("cmd <input >output | <repeat>\n");
		return (0);
	}
	if (check_files_exist(t_lst, t_g) == 0)
		return (0);
	return (1);
}
