/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcstrdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:53:53 by fderly            #+#    #+#             */
/*   Updated: 2023/09/20 10:26:48 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_gcstrdup(const char *s, s_g *s_g)
{
	int		i;
	char	*dst;
	int		len;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	dst = gc_malloc(&s_g->gc, sizeof(char) * len + 1);
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

void	trim_spaces(char *str)
{
	int	start;
	int	end;
	int	i;

	start = 0;
	end = strlen(str) - 1;
	while (str[start] == ' ' || str[start] == '\t'
		|| str[start] == '\n' || str[start] == '\r')
	{
		start++;
	}
	while (end > start && (str[end] == ' ' || str[end] == '\t'
			|| str[end] == '\n' || str[end] == '\r'))
	{
		end--;
	}
	i = 0;
	while (start <= end)
	{
		str[i++] = str[start++];
	}
	str[i] = '\0';
}
