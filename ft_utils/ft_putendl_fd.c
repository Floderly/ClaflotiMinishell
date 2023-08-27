/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:02:09 by aderouin          #+#    #+#             */
/*   Updated: 2023/04/13 17:02:15 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putendl_fd(char *s, int fd)
{
	const char	n = '\n';

	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, &n, 1);
}
