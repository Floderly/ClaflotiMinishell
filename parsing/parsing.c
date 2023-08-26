/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/04/20 11:40:27 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(s_g *s_g, TokenList *token_list)
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
	add_list_exec(s_g, token_list);
	if (check_empty_prompt(token_list) == 0)
	{
		printf("Manque commande\n");
		return (0);
	}
	if (check_files_exist(token_list) == 0)
	{
		printf("Fichier non existant\n");
		return (0);
	}
	printf("Parsing passe, tout est GOOD !!!\n");
	return (1);
}
