/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:46:44 by chugot            #+#    #+#             */
/*   Updated: 2023/09/20 16:32:35 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	red_simp_entry(char *infile, t_g *t_g)
{
	int	infilefd;

	infilefd = open(infile, O_RDWR, 0777);
	if (infilefd == -1)
		error_msg("Error open entry infilefd redirection\n", t_g);
	if (t_g->last_fd != STDIN_FILENO)
		close(t_g->last_fd);
	return (infilefd);
}

void	copy_input(char *input, int inputfd)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		write(inputfd, &input[i], 1);
		i++;
	}
	write(inputfd, "\n", 1);
}

int	red_cond_entry(char *keycode, struct sigaction *sa, t_g *t_g)
{
	char	*input;
	int		inputfd;

	inputfd = open("inputfd.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (inputfd == -1)
		error_msg("Error open entry inputfd redirection\n", t_g);
	if (t_g->last_fd != STDIN_FILENO)
		close(t_g->last_fd);
	g_signal_flag = 43;
	treat_signal(sa, t_g);
	while (42)
	{
		input = readline("> ");
		if (ft_strcmp(input, keycode) != 0)
			copy_input(input, inputfd);
		if (ft_strcmp(input, keycode) == 0)
		{
			write(inputfd, "\0", 1);
			free(input);
			close(inputfd);
			inputfd = open("inputfd.txt", O_RDWR, 0777);
			return (inputfd);
		}
		free(input);
	}
}

int	red_simp_exit(char *outfile, t_g *t_g)
{
	int	outputfd;

	outputfd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (outputfd == -1)
		error_msg("Error open entry outputfd redirection\n", t_g);
	if (t_g->out_fd != STDOUT_FILENO)
		close(t_g->out_fd);
	return (outputfd);
}

int	red_doub_exit(char *outfile, t_g *t_g)
{
	int	outputfd;

	outputfd = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (outputfd == -1)
		error_msg("Error open entry outputfd redirection\n", t_g);
	if (t_g->out_fd != STDOUT_FILENO)
		close(t_g->out_fd);
	return (outputfd);
}
