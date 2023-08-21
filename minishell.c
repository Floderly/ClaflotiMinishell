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

void	son(s_global *s_global, char *input)
{
	pid_t	pid;
	char *input_without_option;

	pid = fork();
	input_without_option = clone_input_without_option(input, input_without_option);
	if (pid == -1)
		error_msg("error fork\n");
	else if (pid == 0)
	{
		if (if_builtin(s_global, input) == 0) //si c'est des fonctions builtins, execute nos propres fonctions ci-dessous.
			exit(0);
		else if (access(input_without_option, F_OK) == 0 ) //verif si la commande entree par l'user n'est pas directement un path valide. Attention si c'est JUSTE un path.
		{
			path_user(s_global, input);
			free(input_without_option);
		}
		else
			path(s_global, input); //processus fils pour execution de cmd.
		exit(0);
	}
	wait(NULL);
}

void	cloneEnv(s_global *s_global, char **env)
{
	int	i;
	// FAIRE LE VRAI MALLOC ? CHAUD AVEC EXPORT
	s_global->miniEnv = malloc(sizeof(char) * 9999);
	i = 0;
	while (env[i])
	{
		s_global->miniEnv[i] = ft_strdup(env[i]);
		i++;
	}
	s_global->miniEnv[i] = 0;
}

void	exportTest(s_global *s_global, char *nomVar, char* arg)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s_global->miniEnv[i])
		i++;
	s_global->miniEnv[i] = malloc (sizeof(char) * 99999);
	while (nomVar[j])
	{
		s_global->miniEnv[i][j] = nomVar[j];
		j++;
	}
	s_global->miniEnv[i][j++] = '=';
	while (arg[k])
	{
		s_global->miniEnv[i][j+k] = arg[k];
		k++;
	}
	s_global->miniEnv[i][j+k] = 0;
	s_global->miniEnv[i + 1] = 0;
}

int main(int argc, char **argv, char **env)
{
	s_global s_global;

	// CLONE ENV POUR FAIRE EXPORT ET UNSET
	cloneEnv(&s_global, env);
	//exportTest(&s_global, "testVarEnvdd", "oui"); // EXPORT POUR TESTER LES VARIABLES
	//own_env(&s_global); //COMMAND POUR AFFICHER LE ENV


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
			if (parsing(&s_global))
			{
				printf("Retour parsing : 1\n");
			}
			else
			{
				printf("Retour parsing : 0\n");
			}
            printf("Prompt apres traitement : %s\n", s_global.inputVarEnv);
			// -------------------  FIN DERLY  -------------------

			//cmd_ctrl(input); 
            printf("---------- EXECUTION ------------\n");
			son(&s_global, s_global.inputVarEnv); //execution cmd sans fermer terminal.
        }
        free(s_global.input); // Libère la mémoire allouée par readline
        printf("---------- FIN ------------\n\n");
    }
	
    return 0;
}
