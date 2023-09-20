/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:29:39 by fderly            #+#    #+#             */
/*   Updated: 2023/09/20 10:41:33 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_norminette(int *n, int *i)
{
	*(n) = 1;
	(*i)++;
}

void	own_echo(char *input)
{
	char	**args;
	int		i;
	int		n;

	i = 1;
	n = 0;
	args = ft_split(input, ' ');
	if (args[1])
	{
		while (args[i] && (ft_strncmp(args[i], "-n", 2) == 0)
			&& (check_arg(args[i]) != 1))
			echo_norminette(&n, &i);
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n == 0)
		printf("\n");
	free_tab(args);
}
