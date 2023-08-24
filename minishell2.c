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

void	son(s_gbl *s_gbl, char *input)
{
	pid_t	pid;
	char	*input_without;

	pid = fork();
	input_without = clone_input_without_option(input, input_without);
	if (pid == -1)
		error_msg("error fork\n");
	else if (pid == 0)
	{
		if (if_builtin(s_gbl, input) == 0) //si c'est des fonctions builtins, execute nos propres fonctions ci-dessous.
			exit(0);
		else if (access(input_without, F_OK) == 0 ) //verif si la commande entree par l'user n'est pas directement un path valide. Attention si c'est JUSTE un path.
		{
			path_user(s_gbl, input);
			free(input_without);
		}
		else
			path(s_gbl, input); //processus fils pour execution de cmd.
		exit(0);
	}
	wait(NULL);
}

void	clone_env(s_gbl *s_gbl, char **env)
{
	int	i;
	// FAIRE LE VRAI MALLOC ? CHAUD AVEC EXPORT
	s_gbl->miniEnv = gc_malloc (&s_gbl->gc ,sizeof(char) * 9999);
	i = 0;
	while (env[i])
	{
		s_gbl->miniEnv[i] = ft_gcstrdup(env[i], s_gbl);
		i++;
	}
	s_gbl->miniEnv[i] = 0;
}

void	export_test(s_gbl *s_gbl, char *nomVar, char *arg)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s_gbl->miniEnv[i])
		i++;
	s_gbl->miniEnv[i] = gc_malloc (&s_gbl->gc ,sizeof(char) * 99999);
	while (nomVar[j])
	{
		s_gbl->miniEnv[i][j] = nomVar[j];
		j++;
	}
	s_gbl->miniEnv[i][j++] = '=';
	while (arg[k])
	{
		s_gbl->miniEnv[i][j + k] = arg[k];
		k++;
	}
	s_gbl->miniEnv[i][j + k] = 0;
	s_gbl->miniEnv[i + 1] = 0;
}
