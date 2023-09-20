/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:52:23 by chugot            #+#    #+#             */
/*   Updated: 2023/09/20 16:41:10 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_nbr_of_pipe(t_lst *t_lst, t_g *t_g)
{
	t_token	*ptr;

	ptr = t_lst->head;
	t_g->pipe_nbr = 0;
	while (ptr->next != NULL)
	{
		if (ptr->token_type == 2)
			t_g->pipe_nbr += 2;
		ptr = ptr->next;
	}
}

void	init_struct_for_pipe(t_lst *t_lst, t_g *t_g)
{
	ft_nbr_of_pipe(t_lst, t_g);
	t_g->cmd_nbr = (t_g->pipe_nbr / 2) + 1;
	t_g->index_cmd = 0;
}

t_token	*move_on_prompt(t_token *cmd_ptr, t_g *t_g)
{
	if (cmd_ptr->next != NULL && cmd_ptr->next->token_type == 3)
		cmd_ptr = cmd_ptr->next;
	if (cmd_ptr->next != NULL && cmd_ptr->next->token_type == 5)
		cmd_ptr = cmd_ptr->next;
	if (cmd_ptr->next != NULL && cmd_ptr->next->token_type == 4)
	{
		cmd_ptr = cmd_ptr->next;
		t_g->out_fd = STDOUT_FILENO;
	}
	if (cmd_ptr->next != NULL && cmd_ptr->next->token_type == 6)
	{
		cmd_ptr = cmd_ptr->next;
		t_g->out_fd = STDOUT_FILENO;
	}
	return (cmd_ptr);
}

void	setup_fd_redir(t_token *cmd_ptr, struct sigaction *sa, t_g *t_g)
{
	while (cmd_ptr->next != NULL && (cmd_ptr->next->token_type == 3
			|| cmd_ptr->next->token_type == 5))
	{
		if (cmd_ptr->next != NULL && cmd_ptr->next->token_type == 3)
			t_g->last_fd = red_simp_entry(cmd_ptr->next->prompt_str, t_g);
		if (cmd_ptr->next != NULL && cmd_ptr->next->token_type == 5)
			t_g->last_fd = red_cond_entry(cmd_ptr->next->prompt_str, sa, t_g);
		cmd_ptr = cmd_ptr->next;
	}
	while (cmd_ptr->next != NULL && cmd_ptr->next->token_type != 2)
	{
		if (cmd_ptr->next != NULL && cmd_ptr->next->token_type == 4)
			t_g->out_fd = red_simp_exit(cmd_ptr->next->prompt_str, t_g);
		if (cmd_ptr->next != NULL && cmd_ptr->next->token_type == 6)
			t_g->out_fd = red_doub_exit(cmd_ptr->next->prompt_str, t_g);
		cmd_ptr = cmd_ptr->next;
	}
}

void	exec_prompt(t_g *t_g, t_lst *t_lst, struct sigaction *sa)
{
	t_token	*cmd_ptr;

	t_g->last_fd = STDIN_FILENO;
	t_g->out_fd = STDOUT_FILENO;
	cmd_ptr = t_lst->head;
	init_struct_for_pipe(t_lst, t_g);
	while (t_g->index_cmd < t_g->cmd_nbr)
	{
		if ((ft_strncmp(cmd_ptr->prompt_str, "export", 6) == 0
				|| ft_strncmp(cmd_ptr->prompt_str, "unset", 5) == 0)
			&& t_g->cmd_nbr != 1)
			cmd_ptr = cmd_ptr->next->next;
		if (if_builtin_father(cmd_ptr->prompt_str, t_g) == 0)
		{
			setup_fd_redir(cmd_ptr, sa, t_g);
			t_g->last_fd = son(t_g, cmd_ptr->prompt_str);
			cmd_ptr = move_on_prompt(cmd_ptr, t_g);
			cmd_ptr = cmd_ptr->next;
			if (cmd_ptr == NULL)
				break ;
			cmd_ptr = cmd_ptr->next;
		}
		t_g->index_cmd++;
	}
}
