/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:52:23 by chugot            #+#    #+#             */
/*   Updated: 2023/08/18 17:52:25 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Ligne de commande shell pour tester bash : echo abc | rev > testSorti

/*typedef struct s_Token {
    char* prompt_str;   | echo abc | rev testSorti
    int tokenType;          1    2  1       4
    struct s_Token* next;
} s_Token;

typedef struct {
    s_Token* head;
} TokenList;*/

void     ft_nbr_of_pipe(to_lst *to_lst, s_g *s_g)
{
    s_Token  *ptr;

    ptr = to_lst->head;
    s_g->pipe_nbr = 0;
    while(ptr->next != NULL)
    {
        if (ptr->tokenType == 2)
            s_g->pipe_nbr++;
        ptr = ptr->next;
    }
}

void    init_struct_for_pipe(to_lst *to_lst, s_g *s_g)
{
    ft_nbr_of_pipe(to_lst, s_g);
    s_g->cmd_nbr = s_g->pipe_nbr + 1;
    if (s_g->pipe_nbr > 0)
    {
        s_g->pipe =  malloc(sizeof(int) * (s_g->pipe_nbr * 2)); //a free.
        if (!s_g->pipe)
            error_msg("Error malloc pipe\n");
    }
    s_g->index_cmd = 0;
}

void    create_all_pipes(s_g *s_g)
{
    int i;

    i = 0;
    while(i < s_g->pipe_nbr)
    {
        if (pipe(s_g->pipe + 2 * i) < 0)
            error_msg("Error pipe\n"); //Voir pour les frees à ce niveau.
        i++;
    }
}

char *find_cmd(to_lst *to_lst, s_g *s_g, char *cmd)
{
    int i;
    s_Token *cmd_ptr;

    i = 0;
    cmd_ptr = to_lst->head;
    while(i < s_g->index_cmd)
    {
        cmd_ptr = cmd_ptr->next;
        i++;
    }
    while (cmd_ptr->tokenType != 2 || cmd_ptr->next != NULL)
    {
        if(cmd_ptr->tokenType == 1)
        {
            cmd = cmd_ptr->prompt_str;
            return(cmd);
        }
        cmd_ptr = cmd_ptr->next;
    }
    return (0);
}

void	dup2_in_out(int zero, int one)
{
	if (dup2(zero, STDIN_FILENO) == -1) //copie zero, càd fichier de lecture sur l'entree standard 0.
		error_msg("Error dup2 3\n");
	if (dup2(one, STDOUT_FILENO) == -1)
		error_msg("Error dup2 4\n");
}

void    close_pipe(s_g *s_g)
{
    int i;

    i = 0;
    while(i <= s_g->pipe_nbr)
    {
        close(s_g->pipe[i]);
        i++;
    }
}

void	redirection_pipe(s_g *s_g)
{
		if(s_g->index_cmd == 0) //si première cmd.
        {
			//dup2_in_out(STDIN_FILENO, s_g->pipe[1]);
            if (dup2(s_g->pipe[1], STDOUT_FILENO) == -1)
		        error_msg("Error dup2 1\n");
        }
		else if(s_g->index_cmd == s_g->cmd_nbr) //si dernière cmd.
        {
			//dup2_in_out(s_g->pipe[2 * s_g->index_cmd - 2], STDOUT_FILENO); //-2 car commence à zero.
            if (dup2(s_g->pipe[2 * s_g->index_cmd - 2], STDIN_FILENO) == -1)
		        error_msg("Error dup2 2\n");
        }
		else
			dup2_in_out(s_g->pipe[2 * s_g->index_cmd - 2], s_g->pipe[2 * s_g->index_cmd + 1]);
		close_pipe(s_g);
}

void	son(s_g *s_g, char *input)
{
	char	*input_without;

    input_without = malloc(sizeof(char) * (ft_strlen(input) + 1)); //free a faire.
	input_without = clone_input_without_option(input, input_without);
	s_g->pid = fork();
	if (s_g->pid == -1)
		error_msg("error fork\n");
	else if (s_g->pid == 0)
	{
		redirection_pipe(s_g);
		if (if_builtin(s_g, input) == 0) //si c'est des fonctions builtins, execute nos propres fonctions ci-dessous.
			exit(0);
		else if (access(input_without, F_OK) == 0 ) //verif si la commande entree par l'user n'est pas directement un path valide. Attention si c'est JUSTE un path.
		{
			path_user(s_g, input);
			free(input_without);
		}
		else
			path(s_g, input); //processus fils pour execution de cmd.
        printf("test\n");
		exit(0);
	}
	wait(NULL);
}

int    exec_prompt(s_g *s_g, to_lst *to_lst) //execute l'ensemble des cmds du prompt.
{
    char *cmd;

    init_struct_for_pipe(to_lst, s_g);
    create_all_pipes(s_g);
    while (s_g->index_cmd < s_g->cmd_nbr) //traite les pipes avant cmd suivante.
    {
        cmd = find_cmd(to_lst, s_g, cmd);
        if (cmd == 0)
            return (0);
        printf("cmd : %s\n", cmd); //test
        son(s_g, cmd);
        s_g->index_cmd++;
    }
    return(1);
}