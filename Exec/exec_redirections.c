/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:46:44 by chugot            #+#    #+#             */
/*   Updated: 2023/09/07 16:46:45 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    redirection_simple_entry(char *infile, int last_fd)
{
    int infilefd;

    infilefd = open(infile, O_RDONLY, 0777);
    if(infilefd == -1)
        error_msg("Error open entry infilefd redirection\n");
    if (last_fd != STDIN_FILENO)
        close(last_fd);
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
    //char    buf[4096];
    //int r;

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
            write(inputfd, "\0", 1);
            //r = read(inputfd, buf, 4096);
            //printf("got %d characters\n", r);
            //if (r == -1)
            //{
            //    printf("badbad\n");
            //}
            //write(1, buf, r);
            free(input);
            close(inputfd);
            inputfd = open("inputfd.txt", O_RDWR, 0777);
            return(inputfd);
        }
        free(input);
    }
}

int redirection_simple_exit(char *outfile, int out_fd)
{
    int outputfd;

    outputfd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (outputfd == -1)
        error_msg("Error open entry outputfd redirection\n");
    if (out_fd != STDOUT_FILENO)
        close(out_fd);
    return(outputfd);
}

int redirection_double_exit(char *outfile, int out_fd)
{
    int outputfd;

    outputfd = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0777);
    if (outputfd == -1)
        error_msg("Error open entry outputfd redirection\n");
    if (out_fd != STDOUT_FILENO)
        close(out_fd);
    return(outputfd);
}
