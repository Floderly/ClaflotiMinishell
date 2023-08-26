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

int	parsing(s_gbl *s_gbl, TokenList *token_list)
{
	if (quote_check(s_gbl->input) == 0)
	{
		printf("!!! Error quote\n");
		return (0);
	}
	if (var_env_chang(s_gbl) == 0)
	{
		printf("Variable Env inexistante\n");
		return (0);
	}
	if (check_pipe_at_start(s_gbl) == 0)
		return (0);

	/*if (redirection(s_gbl) == 0)
	{
		printf("Probleme redirection\n");
		return (0);
	}*/
	add_list_exec(s_gbl, token_list);
	printf("Parsing passe, tout est GOOD !!!\n");
	return (1);
}
