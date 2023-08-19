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

int	quoteCheck(char *input)
{
	int	i;
	int singleQuoteNb;
	int doubleQuoteNb;

	i = 0;
	singleQuoteNb = 0;
	doubleQuoteNb = 0;
	while (input[i])
	{
		if (input[i] == 34)
			doubleQuoteNb++;
		if (input[i] == 39)
			singleQuoteNb++;
		i++;
	}
	if (singleQuoteNb % 2 == 1 || doubleQuoteNb % 2 == 1)
	{
		printf("Single : %d et double : %d\n", singleQuoteNb, doubleQuoteNb);
		return (0);
	}
	printf("Pas de single/double quote impair\n");
	return (1);
}