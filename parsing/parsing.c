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
	return (4);
}

char*	parsing(char *input)
{
	char *inputReturn;

	inputReturn = malloc(sizeof(char)* 4);
	inputReturn[0] = 'a';
	inputReturn[1] = 'b';
	inputReturn[2] = 'c';
	inputReturn[3] = 0;

	mallocSize(input);

	return (inputReturn);
}