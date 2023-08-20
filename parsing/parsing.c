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

int	parsing(s_global *s_global)
{

	if (quoteCheck(s_global->input) == 0)
	{
		printf("!!! Error quote\n");
		return (0);
	}
	if (varEnvChang(s_global) == 0)
	{
		printf("Variable Env inexistante\n");
		return (0);
	}
	//if (checkRedirection(s_global))

	return (1);
}