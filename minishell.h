/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:46:51 by chugot            #+#    #+#             */
/*   Updated: 2023/08/17 14:46:52 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

// structure globale
typedef struct t_global
{
    char *input;
    char *input2;
    char *inputVar;
}s_global;


void	path_user(char *input, char **env);
char	*clone_input_without_option(char *input, char *input_without_option);
void	path(char *argv, char **env);


char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlen(const char *str);

void	free_tab(char **tab);
void	error_msg(char *msg);

//PARSING
int	parsing(s_global *s_global, char **env);




# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

#endif
