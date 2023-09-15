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

int	ft_intlen(long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len = 1;
	if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*new;
	long	nb;
	int		len_int;

	nb = n;
	len_int = ft_intlen(n);
	new = malloc((len_int + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[len_int] = '\0';
	len_int--;
	if (n == 0)
		new[0] = '0';
	if (n < 0)
	{
		new[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		new[len_int] = 48 + (nb % 10);
		nb /= 10;
		len_int--;
	}
	return (new);
}
