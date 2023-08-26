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
	s_gbl    s_gbl;
	TokenList   token_list;

	gc_init(&s_gbl.gc); // INIT LE CLEANER DE MALLOC
	initTokenList(&token_list); // INIT LA LISTE CHAINER DEXECUTION
	clone_env(&s_gbl, env); // CLONE ENV POUR FAIRE EXPORT ET UNSET
	//export_test(&s_gbl, "testVarEnvdd", "oui"); // EXPORT DE TEST POUR TESTER LES VARIABLES
	//own_env(&s_gbl); //COMMAND POUR AFFICHER LE ENV

	printf("Liste chainer de test:\n");
	initTokenTest(&s_gbl, &token_list);

    while (1)
	{
        s_gbl.input = readline("Minishell> "); // Affiche l'invite de commande
        if (!s_gbl.input)
		{
            break; // L'utilisateur a appuyé sur Ctrl+D (fin d'entrée)
        }
        if (s_gbl.input[0] != '\0') 
		{
            add_history(s_gbl.input); // Ajoute l'entrée à l'historique
            // Ici, vous pouvez traiter la commande saisie par l'utilisateur

			// -------------------  DERLY  -------------------
            printf("---------- PARSING ------------\n");
            printf("Prompt avant traitement : %s\n", s_gbl.input);
			printf("Valeur retour du parsing : %d\n", parsing(&s_gbl, &token_list));
            printf("Prompt apres traitement : %s\n", s_gbl.inputVarEnv);
            printf("Liste chainer generer (test):\n");
			afficherTokens(&token_list);
			// -------------------  FIN DERLY  -------------------
            printf("---------- EXECUTION ------------\n");
			son(&s_gbl, s_gbl.inputVarEnv); //execution cmd sans fermer terminal.
        }
        free(s_gbl.input); // Libère la mémoire allouée par readline
        printf("---------- FIN ------------\n\n");
    }
	gc_clean(&s_gbl.gc);
	
    return 0;
}
