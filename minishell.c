/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:14:19 by chugot            #+#    #+#             */
/*   Updated: 2023/08/17 15:14:20 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
	s_g    s_g;
	TokenList   token_list;

	gc_init(&s_g.gc); // INIT LE CLEANER DE MALLOC
	initTokenList(&token_list); // INIT LA LISTE CHAINER DEXECUTION
	clone_env(&s_g, env); // CLONE ENV POUR FAIRE EXPORT ET UNSET
	//export_test(&s_g, "testVarEnvdd", "oui"); // EXPORT DE TEST POUR TESTER LES VARIABLES
	//own_env(&s_g); //COMMAND POUR AFFICHER LE ENV

    while (1)
	{
	    initTokenTest(&s_g, &token_list);
        s_g.input = readline("Minishell> "); // Affiche l'invite de commande
        if (!s_g.input)
		{
            break; // L'utilisateur a appuyé sur Ctrl+D (fin d'entrée)
        }
        if (s_g.input[0] != '\0') 
		{
            add_history(s_g.input); // Ajoute l'entrée à l'historique
            // Ici, vous pouvez traiter la commande saisie par l'utilisateur

			// -------------------  DERLY  -------------------
            printf("---------- PARSING ------------\n");
            printf("Prompt avant traitement : %s\n", s_g.input);
			printf("Valeur retour du parsing : %d\n", parsing(&s_g, &token_list));
            printf("Prompt apres traitement : %s\n", s_g.i2);
            printf("Liste chainer generer (test):\n");
			afficherTokens(&token_list);
			// -------------------  FIN DERLY  -------------------
            printf("---------- EXECUTION ------------\n");
			son(&s_g, s_g.i2); //execution cmd sans fermer terminal.
        }
        free(s_g.input); // Libère la mémoire allouée par readline
        clear_token_list(&token_list);
        printf("---------- FIN ------------\n\n");
    }
	gc_clean(&s_g.gc);
	
    return 0;
}
