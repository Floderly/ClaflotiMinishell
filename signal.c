/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:51:59 by chugot            #+#    #+#             */
/*   Updated: 2023/09/11 17:52:01 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    signal_handler(int signal) //SIGINT ctrl+C
{
    (void)signal;
    //s_g->sigaction_signal = 1;
    printf("Set newline\n");
    return ;
}

void    init_signal(struct sigaction *sa)
{
    //Initialisation of struct for sigaction. 
    sa->sa_handler = signal_handler;
    sa->sa_flags = SA_RESTART;
    sigemptyset(&sa->sa_mask);
    //If Ctrl+C is press.
    signal(SIGQUIT, SIG_IGN);
    if (sigaction(SIGINT, sa, NULL) == -1)
        perror("Sigaction error\n");
    //signal(SIGINT, signal_handler);
}

//ctrl \ a gerer avec bruti de bell.