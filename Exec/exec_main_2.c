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

void	redirection_pipe(t_g *t_g, int fds[2])
{
	if (t_g->last_fd != STDIN_FILENO)
	{
		if (dup2(t_g->last_fd, STDIN_FILENO) == -1)
			error_msg("Error dup2 2\n", t_g);
		close(t_g->last_fd);
	}
	if (t_g->cmd_nbr > 1 && t_g->index_cmd != (t_g->cmd_nbr - 1))
	{
		close(fds[0]);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			error_msg("Error dup2 1\n", t_g);
		close(fds[1]);
	}
	if (t_g->out_fd != STDOUT_FILENO)
	{
		if (dup2(t_g->out_fd, STDOUT_FILENO) == -1)
			error_msg("Error dup2 1\n", t_g);
		close(t_g->out_fd);
	}
}

int	exec_son(t_g *t_g, int *fds, char *input, char *input_without)
{
	if (g_signal_flag == 1)
	{
		printf("\n");
		return (0);
	}
	redirection_pipe(t_g, fds);
	if (if_builtin(t_g, input) == 0)
	{
		gc_clean(&t_g->gc);
		free(t_g->input);
		free(input_without);
		exit(0);
	}
	else if (access(input_without, F_OK) == 0)
	{
		free(input_without);
		path_user(t_g, input);
	}
	else
		path(t_g, input);
	gc_clean(&t_g->gc);
	free(t_g->input);
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

void	handle_exit_status(t_g *t_g)
{
	if (WIFEXITED(t_g->status))
		t_g->exit_ret = (t_g->status / 256);
	else if (WIFSIGNALED(t_g->status))
		t_g->exit_ret = 128 + WTERMSIG(t_g->status);
	else
		t_g->exit_ret = 0;
}

int	son(t_g *t_g, char *input)
{
	char	*input_without;
	int		fds[2];

	input_without = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (input_without == NULL)
		error_msg("Error malloc input_without\n", t_g);
	input_without = clone_input_without_option(input, input_without);
	if (t_g->index_cmd != (t_g->cmd_nbr - 1))
		pipe(fds);
	g_signal_flag = 42;
	t_g->pid = fork();
	if (t_g->pid == -1)
		error_msg("error fork\n", t_g);
	else if (t_g->pid == 0)
		exec_son(t_g, fds, input, input_without);
	waitpid(t_g->pid, &t_g->status, 0);
	free(input_without);
	handle_exit_status(t_g);
	close_fds(t_g->out_fd, t_g->last_fd);
	if (t_g->index_cmd != (t_g->cmd_nbr - 1))
		close(fds[1]);
	if (t_g->index_cmd != (t_g->cmd_nbr - 1))
		return (fds[0]);
	return (0);
}
