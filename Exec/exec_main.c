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

void	ft_nbr_of_pipe(to_lst *to_lst, s_g *s_g)
{
	s_Token	*ptr;

	ptr = to_lst->head;
	s_g->pipe_nbr = 0;
	while (ptr->next != NULL)
	{
		if (ptr->tokenType == 2)
			s_g->pipe_nbr += 2;
		ptr = ptr->next;
	}
}

void	init_struct_for_pipe(to_lst *to_lst, s_g *s_g)
{
	ft_nbr_of_pipe(to_lst, s_g);
	s_g->cmd_nbr = (s_g->pipe_nbr / 2) + 1;
	s_g->index_cmd = 0;
}

s_Token	*move_on_prompt(s_Token *cmd_ptr, s_g *s_g)
{
	if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 3)
		cmd_ptr = cmd_ptr->next;
	if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 5)
		cmd_ptr = cmd_ptr->next;
	if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 4)
	{
		cmd_ptr = cmd_ptr->next;
		s_g->out_fd = STDOUT_FILENO;
	}
	if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 6)
	{
		cmd_ptr = cmd_ptr->next;
		s_g->out_fd = STDOUT_FILENO;
	}
	return (cmd_ptr);
}

void	setup_fd_redir(s_Token *cmd_ptr, struct sigaction *sa, s_g *s_g)
{
	while (cmd_ptr->next != NULL && (cmd_ptr->next->tokenType == 3
			|| cmd_ptr->next->tokenType == 5))
	{
		if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 3)
			s_g->last_fd = red_simp_entry(cmd_ptr->next->prompt_str, s_g);
		if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 5)
			s_g->last_fd = red_cond_entry(cmd_ptr->next->prompt_str, sa, s_g);
		cmd_ptr = cmd_ptr->next;
	}
	while (cmd_ptr->next != NULL && cmd_ptr->next->tokenType != 2)
	{
		if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 4)
			s_g->out_fd = red_simp_exit(cmd_ptr->next->prompt_str, s_g);
		if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 6)
			s_g->out_fd = red_doub_exit(cmd_ptr->next->prompt_str, s_g);
		cmd_ptr = cmd_ptr->next;
	}
}

void	exec_prompt(s_g *s_g, to_lst *to_lst, struct sigaction *sa)
{
	s_Token	*cmd_ptr;

	s_g->last_fd = STDIN_FILENO;
	s_g->out_fd = STDOUT_FILENO;
	cmd_ptr = to_lst->head;
	init_struct_for_pipe(to_lst, s_g);
	while (s_g->index_cmd < s_g->cmd_nbr)
	{
		if ((ft_strncmp(cmd_ptr->prompt_str, "export", 6) == 0
				|| ft_strncmp(cmd_ptr->prompt_str, "unset", 5) == 0)
			&& s_g->cmd_nbr != 1)
			cmd_ptr = cmd_ptr->next->next;
		if (if_builtin_father(cmd_ptr->prompt_str, s_g) == 0)
		{
			setup_fd_redir(cmd_ptr, sa, s_g);
			s_g->last_fd = son(s_g, cmd_ptr->prompt_str);
			cmd_ptr = move_on_prompt(cmd_ptr, s_g);
			cmd_ptr = cmd_ptr->next;
			if (cmd_ptr == NULL)
				break ;
			cmd_ptr = cmd_ptr->next;
		}
		s_g->index_cmd++;
	}
}
