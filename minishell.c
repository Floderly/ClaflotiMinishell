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

char	*check_path(char *cmd, char **env)
{
	char	**tabpath;
	char	*halfpath;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == NULL)
		i++;
	tabpath = ft_split(env[i] + 5, ':');
	i = 0;
	while (tabpath[i])
	{
		halfpath = ft_strjoin(tabpath[i], "/");
		path = ft_strjoin(halfpath, cmd);
		free(halfpath);
		if (access(path, F_OK) == 0)
		{
			free_tab(tabpath);
			return (path);
		}
		free(path);
		i++;
	}
	free_tab(tabpath);
	error_msg("error no path found\n");
}

void	path(char *argv, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = check_path(cmd[0], env);
	if (execve(path, cmd, env) == -1)
	{
		free_tab(cmd);
		free(path);
		error_msg("error execve\n");
	}
	free_tab(cmd);
	free(path);
}

void	son(char *input, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_msg("error fork\n");
	else if (pid == 0)
	{
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
