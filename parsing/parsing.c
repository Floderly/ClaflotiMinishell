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

int	mallocSize(char *input)
{
	// PAS FAIT
	return (4);
}

int	parsing(s_global *s_global, char **env)
{

	if (quoteCheck(s_global->input) == 0)
	{
		printf("!!! Error quote\n");
		return (0);
	}
	if (varEnvChang(s_global, env) == 0)
	{
		printf("Variable Env inexistante\n");
		return (0);
	}
	mallocSize(s_global->input);

	return (1);
}