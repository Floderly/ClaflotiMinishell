/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:52:23 by chugot            #+#    #+#             */
/*   Updated: 2023/09/15 19:33:18 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void     ft_nbr_of_pipe(to_lst *to_lst, s_g *s_g)
{
    s_Token  *ptr;

    ptr = to_lst->head;
    s_g->pipe_nbr = 0;
    while(ptr->next != NULL)
    {
        if (ptr->tokenType == 2)
            s_g->pipe_nbr += 2;
        ptr = ptr->next;
    }
}

void    init_struct_for_pipe(to_lst *to_lst, s_g *s_g)
{
    ft_nbr_of_pipe(to_lst, s_g);
    s_g->cmd_nbr = (s_g->pipe_nbr / 2) + 1;
    // printf("nbr_pipe : %d, nbr_cmd : %d\n", s_g->pipe_nbr, s_g->cmd_nbr); //test
    s_g->index_cmd = 0;
}

void	redirection_pipe(s_g *s_g, int fds[2], int last_fd, int out_fd)
{
    if(last_fd != STDIN_FILENO) // si pas premiere commande
    {
        // dprintf(STDERR_FILENO, "STDIN PIPE %d\n", s_g->index_cmd);
        if (dup2(last_fd, STDIN_FILENO) == -1)
            error_msg("Error dup2 2\n");
        close(last_fd);
    }
    if(s_g->cmd_nbr > 1 && s_g->index_cmd != (s_g->cmd_nbr - 1)) // si pas derniere commande
    {
        close(fds[0]);
            if (dup2(fds[1], STDOUT_FILENO) == -1)
                error_msg("Error dup2 1\n");
            close(fds[1]);
    }
    if(out_fd != STDOUT_FILENO)
    {
        if (dup2(out_fd, STDOUT_FILENO) == -1)
            error_msg("Error dup2 1\n");
        close(out_fd);
    }
}

int	son(s_g *s_g, char *input, int last_fd, int out_fd)
{
	char	*input_without;
    int     fds[2];

    input_without = malloc(sizeof(char) * (ft_strlen(input) + 1)); //free a faire.
    if (input_without == NULL)
        error_msg("Error malloc input_without\n");
    input_without = clone_input_without_option(input, input_without);
    if (s_g->index_cmd != (s_g->cmd_nbr - 1))
        pipe(fds); // TODO: check error
    s_g->pid = fork();
	if (s_g->pid == -1)
		error_msg("error fork\n");
	else if (s_g->pid == 0)
	{
        //if (s_g->cmd_nbr > 1)
		redirection_pipe(s_g, fds, last_fd, out_fd);
		if (if_builtin(s_g, input) == 0) //si c'est des fonctions builtins, execute nos propres fonctions ci-dessous.
		 	exit(0);
		else if (access(input_without, F_OK) == 0) //verif si la commande entree par l'user n'est pas directement un path valide. Attention si c'est JUSTE un path.
		{
			path_user(s_g, input);
			free(input_without);
		}
		else
			path(s_g, input); //processus fils pour execution de cmd.
        exit(0);
    }
    wait(NULL);
    // close read end of last cmd pipe
    if (out_fd != STDOUT_FILENO)
        close(out_fd);
    if (last_fd != STDIN_FILENO)
        close(last_fd);
    if (s_g->index_cmd != (s_g->cmd_nbr - 1))
        close(fds[1]);
    if (s_g->index_cmd != (s_g->cmd_nbr - 1))
        return (fds[0]);
    return (0);
}

s_Token    *move_on_prompt(s_Token *cmd_ptr, int *out_fd)
{
    if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 3) //IF <
        cmd_ptr = cmd_ptr->next;
    if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 5) //IF <<
        cmd_ptr = cmd_ptr->next;
    if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 4) //IF >
    {
        cmd_ptr = cmd_ptr->next;
        *out_fd = STDOUT_FILENO;
    }
    if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 6) //IF >>
    {
        cmd_ptr = cmd_ptr->next;
        *out_fd = STDOUT_FILENO;
    }
    return (cmd_ptr);
}

void    setup_fd_redir(s_Token *cmd_ptr, int *last_fd, int *out_fd)
{
    while (cmd_ptr->next != NULL && (cmd_ptr->next->tokenType == 3 || cmd_ptr->next->tokenType == 5))
    {
        if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 3) //IF <
            *last_fd = redirection_simple_entry(cmd_ptr->next->prompt_str, last_fd);
        if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 5) // IF <<
            *last_fd = redirection_condition_entry(cmd_ptr->next->prompt_str, last_fd);
        cmd_ptr = cmd_ptr->next;
    }
    while (cmd_ptr->next != NULL && cmd_ptr->next->tokenType != 2)
    {
        if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 4) //IF >
            *out_fd = redirection_simple_exit(cmd_ptr->next->prompt_str, out_fd);
        if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 6) //IF >>
            *out_fd = redirection_double_exit(cmd_ptr->next->prompt_str, out_fd);
        cmd_ptr = cmd_ptr->next;
    }
}

void    exec_prompt(s_g *s_g, to_lst *to_lst) //execute l'ensemble des cmds du prompt.
{
    s_Token *cmd_ptr;
    int last_fd;
    int out_fd;

    last_fd = STDIN_FILENO;
    out_fd = STDOUT_FILENO;
    cmd_ptr = to_lst->head;
    init_struct_for_pipe(to_lst, s_g);
    while (s_g->index_cmd < s_g->cmd_nbr) //traite les pipes et redirections avant cmd suivante.
    {
        //if (cmd_ptr->next != NULL)
        //{
        //    printf("next tokenType : %d\n", cmd_ptr->next->tokenType);
        //    printf("cmd prompt : %s\n", cmd_ptr->next->prompt_str);
        //}
        if (ft_strncmp(cmd_ptr->prompt_str, "export", 6) == 0 && s_g->cmd_nbr == 1)
	    	own_export(cmd_ptr->prompt_str, s_g);
	    else if (ft_strncmp(cmd_ptr->prompt_str, "unset", 5) == 0 && s_g->cmd_nbr == 1)
	    	own_unset(cmd_ptr->prompt_str, s_g);
	    else if (ft_strncmp(cmd_ptr->prompt_str, "exit", 4) == 0 && s_g->cmd_nbr == 1)
	    	own_exit(cmd_ptr->prompt_str, s_g);
	    else if (ft_strncmp(cmd_ptr->prompt_str, "cd", 2) == 0 && s_g->cmd_nbr == 1)
	    	own_cd(cmd_ptr->prompt_str, s_g);
        else if ((ft_strncmp(cmd_ptr->prompt_str, "export", 6) == 0 || ft_strncmp(cmd_ptr->prompt_str, "unset", 5) == 0) && s_g->cmd_nbr != 1)
            cmd_ptr = cmd_ptr->next->next;
        else
        {
            setup_fd_redir(cmd_ptr, &last_fd, &out_fd);
            last_fd = son(s_g, cmd_ptr->prompt_str, last_fd, out_fd);
            cmd_ptr = move_on_prompt(cmd_ptr, &out_fd);
            cmd_ptr = cmd_ptr->next;
            if (cmd_ptr == NULL)
                break ;
            cmd_ptr = cmd_ptr->next;
        }
        s_g->index_cmd++;
    }
}
