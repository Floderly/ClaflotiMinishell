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
# include "gc/gc.h"

// structure globale
typedef struct t_gbl
{
	t_gcan	gc;
    char    **miniEnv;
    char    *input;
    char    *inputVarEnv;
    char    *pathVarTempo;
    char    *inputAfterRedi;
    char    *redirectionNameFile;
    int switchSingleQuote;
    char    **gestionTest;
}s_gbl;

// LC ARGUMENT TOKEN
typedef struct s_Token {
    char* prompt_str;
    int tokenType;
    struct s_Token* next;
} s_Token;

typedef struct {
    s_Token* head;
} TokenList;

// MINISHELL2
void	son(s_gbl *s_gbl, char *input);
void	clone_env(s_gbl *s_gbl, char **env);
void	export_test(s_gbl *s_gbl, char *nomVar, char* arg);

// FONCTION EXECUTION
void	path_user(s_gbl *s_gbl, char *input);
char	*clone_input_without_option(char *input, char *input_without_option);
void	path(s_gbl *s_gbl, char *argv);
int	if_builtin(s_gbl *s_gbl, char *input);
void	own_env(s_gbl *s_gbl);

// FONCTION UTILS
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_gcstrdup(const char *s, s_gbl *s_gbl);
int	ft_strcmp(char *s1, char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

void	free_tab(char **tab);
void	error_msg(char *msg);

//FONCTION AUTRE
int	skipSpace(char *string, int i); // A REFAIRE AVEC +1 ?

// FONCTION PARSING
int	parsing(s_gbl *s_gbl);
int	quote_check(char *input);
int	var_env_chang(s_gbl *s_gbl);
int	redirection(s_gbl *s_gbl);

// LISTE CHAINER D'EXECUTION
void addToken(TokenList *tokenList, char *prompt_str, int tokenType, s_gbl *s_gbl);
void initTokenList(TokenList *tokenList);
void initTokenTest(s_gbl *s_gbl, TokenList *tokenList);
void afficherTokens(TokenList *tokenList);

//s_gbl->pathVarTempo = gc_malloc(&s_gbl->gc ,sizeof(char) * 9999);


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

#endif
