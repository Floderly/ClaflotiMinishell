/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:53:53 by fderly            #+#    #+#             */
/*   Updated: 2023/05/03 11:53:55 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dst;
	int		len;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	dst = malloc (sizeof(char) * len + 1);
	if (dst == 0)
		return (NULL);
	while (s[i] != '\0')
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
