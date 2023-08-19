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

# include "minishell.h"

/*void	cmd_ctrl(char *input)
{
	if ()
	{

	}
}*/

void	son(char *input, char **env)
{
	pid_t	pid;
	char *input_without_option;

	pid = fork();
	input_without_option = clone_input_without_option(input, input_without_option);
	if (pid == -1)
		error_msg("error fork\n");
	else if (pid == 0)
	{
		if (access(input_without_option, F_OK) == 0 ) //verif si la commande entree par l'user n'est pas directement un path valide. Attention si c'est JUSTE un path.
		{
			path_user(input, env);
			free(input_without_option);
		}
		else
			path(input, env); //processus fils pour execution de cmd.
		exit(0);
	}
	wait(NULL);
}

int main(int argc, char **argv, char **env)
{
	s_global s_global;
	char *valeur_env;

    while (1)
	{
        s_global.input = readline("Minishell> "); // Affiche l'invite de commande
        if (!s_global.input)
		{
            break; // L'utilisateur a appuyé sur Ctrl+D (fin d'entrée)
        }
        if (s_global.input[0] != '\0') 
		{
            add_history(s_global.input); // Ajoute l'entrée à l'historique
            // Ici, vous pouvez traiter la commande saisie par l'utilisateur

			// -------------------  DERLY  -------------------
            printf("---------- PARSING ------------\n");
            printf("Prompt avant traitement : %s\n", s_global.input);
			if (parsing(&s_global, env))
			{
				printf("Retour 1, valeur : %s\n", s_global.input2);
			}
			else
			{
				printf("Retour 0, valeur : %s\n", s_global.input2);
			}
            printf("Prompt apres traitement : %s\n", s_global.input2);
			// -------------------  FIN DERLY  -------------------

			//cmd_ctrl(input); 
            printf("---------- EXECUTION ------------\n");
			son(s_global.inputVarEnv, env); //execution cmd sans fermer terminal.
        }
        free(s_global.input); // Libère la mémoire allouée par readline
        printf("---------- FIN ------------\n\n");
    }
        free(s_global.input2); // Libère la mémoire allouée par readline
    return 0;
}
