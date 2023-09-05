/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:52:23 by chugot            #+#    #+#             */
/*   Updated: 2023/09/04 20:21:47 by clara            ###   ########.fr       */
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
    //s_g->flag_entry_redir = 0;
}

/*char *find_cmd(to_lst *to_lst, s_g *s_g, char *cmd)
{
    int i;
    s_Token *cmd_ptr;

    i = 0;
    cmd_ptr = to_lst->head;
    while(i < s_g->index_cmd)
    {
        printf("cmd parsing 1 : %s\n", cmd_ptr->prompt_str);
        cmd_ptr = cmd_ptr->next;
        i++;
    }
    printf("cmd parsing 1,5 : %s\n", cmd_ptr->prompt_str);
    if (cmd_ptr != 0)
        cmd_ptr = cmd_ptr->next;
    while (cmd_ptr->next != NULL) //cmd_ptr->tokenType != 2 || 
    {
        printf("cmd parsing 2 : %s\n", cmd_ptr->prompt_str);
        if(cmd_ptr->tokenType == 1)
        {
            cmd = cmd_ptr->prompt_str;
            return(cmd);
        }
        cmd_ptr = cmd_ptr->next;
    }
    return (0);
}*/

/*void	dup2_in_out(int zero, int one)
{
	if (dup2(zero, STDIN_FILENO) == -1) //copie zero, càd fichier de lecture sur l'entree standard 0.
		error_msg("Error dup2 3\n");
	if (dup2(one, STDOUT_FILENO) == -1)
		error_msg("Error dup2 4\n");
}*/

// void    close_pipe(s_g *s_g)
// {
//     int i;

//     i = 0;
//     while(i < s_g->pipe_nbr)
//     {
//         safe_close(s_g->pipe[i]);
//         i++;
//     }
// }

void	redirection_pipe(s_g *s_g, int fds[2], int last_fd)
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
        //dprintf(STDERR_FILENO, "STDOUT PIPE %d\n", s_g->index_cmd);
        close(fds[0]);
        if (dup2(fds[1], STDOUT_FILENO) == -1)
            error_msg("Error dup2 1\n");
        close(fds[1]);
    }
}

int	son(s_g *s_g, char *input, int last_fd)
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
		redirection_pipe(s_g, fds, last_fd);
		// if (if_builtin(s_g, input) == 0) //si c'est des fonctions builtins, execute nos propres fonctions ci-dessous.
		// 	exit(0);
		if (access(input_without, F_OK) == 0) //verif si la commande entree par l'user n'est pas directement un path valide. Attention si c'est JUSTE un path.
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
    if (last_fd != STDIN_FILENO)
        close(last_fd);
    if (s_g->index_cmd != (s_g->cmd_nbr - 1))
        close(fds[1]);
    if (s_g->index_cmd != (s_g->cmd_nbr - 1))
        return (fds[0]);
    return (0);
}

int    redirection_simple_entry(char *infile, int last_fd)
{
    int infilefd;

    infilefd = open(infile, O_RDONLY, 0777);
    if(infilefd == -1)
        error_msg("Error open entry infilefd redirection\n");
    if (last_fd != STDIN_FILENO)
        close(last_fd);
    //if(s_g->cmd_nbr == 1)
    //{
    //    if(dup2(infilefd, STDIN_FILENO) == -1)
    //        error_msg("Error dup2 infile\n");
    //    //return (infilefd);
    //}
    return(infilefd);
}

void    copy_input(char *input, int inputfd)
{
    int i;

    i = 0;
    while (input[i] != '\0')
    {
        write(inputfd, &input[i], 1);
        i++;
    }
    write(inputfd, "\n", 1);
}

int    redirection_condition_entry(char *keycode, int last_fd) //char *cmd_prompt, 
{
    char *input;
    int inputfd;

    inputfd = open("inputfd.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
    if(inputfd == -1)
        error_msg("Error open entry inputfd redirection\n");
    if (last_fd != STDIN_FILENO)
        close(last_fd);
    while (1)
	{
        input = readline("> ");
        if (ft_strcmp(input, keycode) != 0)
            copy_input(input, inputfd);
        //printf("prompt : %s\n", cmd_prompt);
        if (ft_strcmp(input, keycode) == 0)
        {
            //if (ft_strncmp(cmd_prompt, "cat", 3) == 0) //attention espaces avant et après cmd.
            //{
            //    //printf("test\n");
            //    write(inputfd, "\0", 1);
            //    free(input);
            //    return(inputfd);
            //}
            write(inputfd, "\0", 1);
            free(input);
            return(inputfd);
        }
        free(input);
    }
}

void    exec_prompt(s_g *s_g, to_lst *to_lst) //execute l'ensemble des cmds du prompt.
{
    s_Token *cmd_ptr;
    int last_fd;

    last_fd = STDIN_FILENO;
    cmd_ptr = to_lst->head;
    init_struct_for_pipe(to_lst, s_g);
    while (s_g->index_cmd < s_g->cmd_nbr) //traite les pipes avant cmd suivante.
    {
        //if (cmd_ptr->next != NULL)
        //{
        //    printf("next tokenType : %d\n", cmd_ptr->next->tokenType);
        //    printf("cmd prompt : %s\n", cmd_ptr->next->prompt_str);
        //}
        if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 3) //IF SIMPLE ENTRY
            last_fd = redirection_simple_entry(cmd_ptr->next->prompt_str, last_fd);
        if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 5) // IF <<
            last_fd = redirection_condition_entry(cmd_ptr->next->prompt_str, last_fd); //cmd_ptr->prompt_str, 
        
        last_fd = son(s_g, cmd_ptr->prompt_str, last_fd);

        if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 3) //IF SIMPLE ENTRY
            cmd_ptr = cmd_ptr->next;
        if (cmd_ptr->next != NULL && cmd_ptr->next->tokenType == 5) //IF <<
            cmd_ptr = cmd_ptr->next;
        
        s_g->index_cmd++;
        cmd_ptr = cmd_ptr->next;
        if (cmd_ptr == NULL)
            break ;
        cmd_ptr = cmd_ptr->next;
    }
}
