/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:18:51 by chugot            #+#    #+#             */
/*   Updated: 2023/09/20 14:07:51 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	error_msg(char *msg, t_g *t_g)
{
	gc_clean(&t_g->gc);
	free(t_g->input);
	perror(msg);
	exit(t_g->exit_ret);
}

char	*clone_input_without_option(char *input, char *input_without_option)
{
	int	i;

	i = 0;
	while (input[i] != ' ' && input[i])
	{
		input_without_option[i] = input[i];
		i++;
	}
	input_without_option[i] = '\0';
	return (input_without_option);
}
