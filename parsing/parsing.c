/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/08/27 02:24:07 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(s_g *s_g, to_lst *to_lst)
{
	if (quote_check(s_g->input) == 0)
	{
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
		printf("Manque commande\n");
		return (0);
	}
	if (check_files_exist(to_lst) == 0)
	{
		printf("Fichier non existant\n");
		return (0);
	}
	// printf("Parsing passe, tout est GOOD !!!\n");
	return (1);
}
