/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:22:24 by aderouin          #+#    #+#             */
/*   Updated: 2023/04/15 13:51:31 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *nptr)
{
	long long	nb;
	int			sign;
	int			i;

	i = 0;
	nb = 0;
	sign = 1;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		if (nb * sign > 2147483647)
			return (-1);
		else if (nb * sign < -2147483648)
			return (0);
		nb = nb * 10 + nptr[i] - '0';
		i++;
	}
	return (nb * sign);
}
