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
    char *input;
	char *valeur_env;

    while (1)
	{
        input = readline("Minishell> "); // Affiche l'invite de commande
        if (!input)
		{
            break; // L'utilisateur a appuyé sur Ctrl+D (fin d'entrée)
        }
        if (input[0] != '\0') 
		{
            add_history(input); // Ajoute l'entrée à l'historique
            // Ici, vous pouvez traiter la commande saisie par l'utilisateur
            printf("Vous avez saisi : %s\n", input);
			//cmd_ctrl(input);
			//valeur_env = getenv("PATH");
			//printf("la valeur de PATH est %s\n", valeur_env);
			son(input, env); //execution cmd sans fermer terminal.
        }
        free(input); // Libère la mémoire allouée par readline
    }
    return 0;
}
