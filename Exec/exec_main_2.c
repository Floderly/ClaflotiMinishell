/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:52:23 by chugot            #+#    #+#             */
/*   Updated: 2023/09/20 16:41:44 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirection_pipe(s_g *s_g, int fds[2])
{
	if (s_g->last_fd != STDIN_FILENO)
	{
		if (dup2(s_g->last_fd, STDIN_FILENO) == -1)
			error_msg("Error dup2 2\n", s_g);
		close(s_g->last_fd);
	}
	if (s_g->cmd_nbr > 1 && s_g->index_cmd != (s_g->cmd_nbr - 1))
	{
		close(fds[0]);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			error_msg("Error dup2 1\n", s_g);
		close(fds[1]);
	}
	if (s_g->out_fd != STDOUT_FILENO)
	{
		if (dup2(s_g->out_fd, STDOUT_FILENO) == -1)
			error_msg("Error dup2 1\n", s_g);
		close(s_g->out_fd);
	}
}

int	exec_son(s_g *s_g, int *fds, char *input, char *input_without)
{
	if (g_signal_flag == 1)
	{
		printf("\n");
		return (0);
	}
	redirection_pipe(s_g, fds);
	if (if_builtin(s_g, input) == 0)
	{
		gc_clean(&s_g->gc);
		free(s_g->input);
		free(input_without);
		exit(0);
	}
	else if (access(input_without, F_OK) == 0)
	{
		free(input_without);
		path_user(s_g, input);
	}
	else
		path(s_g, input);
	gc_clean(&s_g->gc);
	free(s_g->input);
	free(input_without);
	exit(0);
}

void	close_fds(int out_fd, int last_fd)
{
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	if (last_fd != STDIN_FILENO)
		close(last_fd);
}

void	handle_exit_status(s_g *s_g)
{
	if (WIFEXITED(s_g->status))
		s_g->exit_ret = (s_g->status / 256);
	else if (WIFSIGNALED(s_g->status))
		s_g->exit_ret = 128 + WTERMSIG(s_g->status);
	else
		s_g->exit_ret = 0;
}

int	son(s_g *s_g, char *input)
{
	char	*input_without;
	int		fds[2];

	input_without = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (input_without == NULL)
		error_msg("Error malloc input_without\n", s_g);
	input_without = clone_input_without_option(input, input_without);
	if (s_g->index_cmd != (s_g->cmd_nbr - 1))
		pipe(fds);
	g_signal_flag = 42;
	s_g->pid = fork();
	if (s_g->pid == -1)
		error_msg("error fork\n", s_g);
	else if (s_g->pid == 0)
		exec_son(s_g, fds, input, input_without);
	waitpid(s_g->pid, &s_g->status, 0);
	free(input_without);
	handle_exit_status(s_g);
	close_fds(s_g->out_fd, s_g->last_fd);
	if (s_g->index_cmd != (s_g->cmd_nbr - 1))
		close(fds[1]);
	if (s_g->index_cmd != (s_g->cmd_nbr - 1))
		return (fds[0]);
	return (0);
}
