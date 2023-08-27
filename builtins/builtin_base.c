/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:14:19 by chugot            #+#    #+#             */
/*   Updated: 2023/08/17 15:14:20 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	own_env(s_g *s_g)
{
	int	i;

	i = 0;
	while (s_g->miniEnv[i])
	{
		printf("%s\n", s_g->miniEnv[i]);
		i++;
	}
}

int		own_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
		return (1);
}


int	count_args(char **args)
{
	size_t i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	check_arg(char *arg)
{
	int i;

	i = 1;	
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void    own_echo(char *input)
{
	char **args;
	int	i;
	int	n;
	int size;

	i = 1;
	n = 0;
	args = ft_split(input, ' ');
	size = count_args(args);
	if (size > 1)
	{
		while (args[i] && (ft_strncmp(args[i], "-n", 2) == 0) && (check_arg(args[i]) != 1))
		{
			n = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n == 0)
		printf("\n");
}


void    own_cd()
{
    char *buffer;

	buffer = 0;
    if (getcwd(buffer, 30) == NULL)
        perror("error getcwd\n");
    if (chdir(buffer) == -1)
        perror("error chdir\n");
}



int	if_builtin(s_g *s_g, char *input)
{
	(void)s_g; // FLAGS
	if (ft_strncmp(input, "echo", 4) == 0)
		own_echo(input);
	if (ft_strcmp(input, "cd") == 0)
		own_cd();
	else if (ft_strcmp(input, "pwd") == 0)
		own_pwd();

/*	else if (ft_strcmp(input, "export") == 0)
		own_export();
	else if (ft_strcmp(input, "unset") == 0)
		own_unset();
*/
	else if (ft_strcmp(input, "env") == 0)
		own_env(s_g);
/*
	else if (ft_strcmp(input, "exit") == 0)
		own_exit();
*/
	else
		return(1);
	return(0);
}
