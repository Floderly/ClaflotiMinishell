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

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
	s_g    s_g;
	to_lst   to_lst;

	gc_init(&s_g.gc);
	to_lst.head = NULL;
	clone_env(&s_g, env); // CLONE ENV POUR FAIRE EXPORT ET UNSET
	//export_test(&s_g, "testVarEnvdd", "oui"); // EXPORT DE TEST POUR TESTER LES VARIABLES

    while (1)
	{
        s_g.input = readline("Minishell> "); // Affiche l'invite de commande
        if (!s_g.input)
		{
            break; // L'utilisateur a appuyé sur Ctrl+D (fin d'entrée)
        }
        if (s_g.input[0] != '\0')
		{
            add_history(s_g.input);

			if (parsing(&s_g, &to_lst) == 1)
                exec_prompt(&s_g, &to_lst);
            // printf("Liste chainer generer :\n");
			// afficher_tokens(&to_lst);
            // printf("---------- EXECUTION ------------\n");
        }
        free(s_g.input);
        clear_to_lst(&to_lst);
        // printf("---------- FIN ------------\n\n");
    }
	gc_clean(&s_g.gc);
	
    return 0;
}
