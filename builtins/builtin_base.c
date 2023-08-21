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

# include "../minishell.h"

void	own_env(s_global *s_global)
{
	int	i;

	i = 0;
	while (s_global->miniEnv[i])
	{
		printf("%s\n", s_global->miniEnv[i]);
		i++;
	}
}

void    own_cd()
{
    char *buffer;

    if (getcwd(buffer, 30) == NULL)
        perror("error getcwd\n");
    if (chdir(buffer) == -1)
        perror("error chdir\n");
}

int	if_builtin(s_global *s_global, char *input)
{
	//if (ft_strncmp(input, "echo", 4) == 0)
	//	own_echo();
	if (ft_strcmp(input, "cd") == 0)
		own_cd();
	/*else if (ft_strcmp(input, "pwd") == 0)
		own_pwd();
	else if (ft_strcmp(input, "export") == 0)
		own_export();
	else if (ft_strcmp(input, "unset") == 0)
		own_unset();
	else if (ft_strcmp(input, "env") == 0)
		own_env(s_global);
	else if (ft_strcmp(input, "exit") == 0)
		own_exit();*/
	else
		return(1);
	return(0);
}