/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:14:19 by chugot            #+#    #+#             */
/*   Updated: 2023/09/04 18:24:57 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal_flag = 0;

void    main_loop(s_g *s_g, struct sigaction *sa, to_lst *to_lst)
{
    while (1)
	{
        g_signal_flag = 0;
        s_g->input = readline("Minishell> "); // Affiche l'invite de commande
        if (!s_g->input)
		{
            printf("Don't leave me !\n");
            free(s_g->input);
            gc_clean(&s_g->gc);
            exit(s_g->exit_ret); //L'utilisateur a appuyé sur Ctrl+D (fin d'entrée)
        }
        if (s_g->input[0] != '\0')
		{
            add_history(s_g->input);
			if (parsing(s_g, to_lst) == 1)
                exec_prompt(s_g, to_lst, sa);
        }
        free(s_g->input);
        clear_to_lst(to_lst);
    }
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
	s_g    s_g;
	to_lst   to_lst;
    struct sigaction    sa;
    char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
		s_g.cur_pwd = cwd;
	gc_init(&s_g.gc);
	to_lst.head = NULL;
	clone_env(&s_g, env); // CLONE ENV POUR FAIRE EXPORT ET UNSET
    treat_signal(&sa, &s_g);
    main_loop(&s_g, &sa, &to_lst);
	gc_clean(&s_g.gc);
    return (0);
}
