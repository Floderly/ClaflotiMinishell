/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:46:51 by chugot            #+#    #+#             */
/*   Updated: 2023/09/20 16:43:12 by fderly           ###   ########.fr       */
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
# include <limits.h>
# include <signal.h>

extern int g_signal_flag;

// structure globale
typedef struct t_g
{
	t_gcan	gc;
    char    **miniEnv;
    char    **expEnv;
    char    *input;
    char    *i2;
    char    *pathVarTempo;
    char    *inputAfterRedi;
    char    *redirectionNameFile;
    int switchSingleQuote;
    char    **gestionTest;
    //pour maillon str, pour la norminette
    int sStr;
    int lgStr;
    //pour execution.
    pid_t   pid;
    int     status;
    int     cmd_nbr;
    int     pipe_nbr;
    int     index_cmd;
    int     sigaction_flag;

    //ADEROUIN
    char    **history_tab;
    int history_count;
    char    *cur_pwd;
    char    *new_pwd;
    int exit_ret;

    int out_fd;
    int last_fd;
}s_g;


// LC ARGUMENT TOKEN
typedef struct s_Token {
    char* prompt_str;
    int tokenType;
    struct s_Token* next;
} s_Token;

typedef struct {
    s_Token* head;
} to_lst;

// MINISHELL2, ENV
void	clone_env(s_g *s_g, char **env);
void	export_test(s_g *s_g, char *nomVar, char* arg);
void	modif_exp(s_g *s_g, int i);
int	is_equal(char *s);

//FONCTION SIGNAL
void    signal_handler(int signal);
void    treat_signal(struct sigaction *sa, s_g *s_g);

// FONCTIONS EXECUTION
void    exec_prompt(s_g *s_g, to_lst *to_lst, struct sigaction *sa);
int 	son(s_g *s_g, char *input);
void	path_user(s_g *s_g, char *input);
char	*clone_input_without_option(char *input, char *input_without_option);
void	path(s_g *s_g, char *argv);
int    red_simp_entry(char *infile, s_g *s_g);
int    red_cond_entry(char *keycode, struct sigaction *sa, s_g *s_g);
int red_simp_exit(char *outfile, s_g *s_g);
int red_doub_exit(char *outfile, s_g *s_g);

//aderouin
int	if_builtin_father(char *prompt, s_g *s_g);
int	if_builtin(s_g *s_g, char *input);
void	own_env(s_g *s_g);
int	own_pwd(/*s_g *s_g*/);
int	own_export(char *input, s_g *s_g);
void	swap_export(s_g *s_g);
void    own_echo(char *input);
void	own_exit(char *input, s_g *s_g);
void    own_cd(char *str, s_g *s_g);
void	own_unset(char *input, s_g *s_g);
void	print_export(s_g *s_g);
void	add_env(char *arg, s_g *s_g);
int		own_pwd_check(s_g *s_g);

// FONCTIONS BUILTIN
int	if_builtin(s_g *s_g, char *input);
void	own_env(s_g *s_g);

// FONCTION UTILS
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlen(const char *str);
int	ft_atoi(const char *nptr);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
char	*ft_gcstrdup(const char *s, s_g *s_g);
void trim_spaces(char *str);
int	ft_strcmp(char *s1, char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);

void	free_tab(char **tab);
void	error_msg(char *msg, s_g *s_g);
//aderouin
int	count_args(char **args);
int	check_arg(char *arg);
int	ft_isnum(char *str);

//FONCTION AUTRE
int	skip_space(char *string, int i); // A REFAIRE AVEC +1 ?
char    *ft_clear_env(char *str, s_g *s_g);

// FONCTION PARSING
int	parsing(s_g *s_g, to_lst *to_lst);
int	quote_check(char *input);
int	var_env_chang(s_g *s_g);
int	redirection(s_g *s_g);
int	check_pipe_at_start(s_g *s_g);

int	add_list_exec(s_g *s_g, to_lst *to_lst);
void	put_maillon_str(s_g *s_g, to_lst *to_lst);
int	put_red_deli_str(s_g *s_g, to_lst *to_lst);
int	put_red_in_str(s_g *s_g, to_lst *to_lst);
int	put_red_out_str(s_g *s_g, to_lst *to_lst);
int	put_red_append_str(s_g *s_g, to_lst *to_lst);

int	put_entry(s_g *s_g, to_lst *to_lst);
int	put_sorti(s_g *s_g, to_lst *to_lst);
void pass_quote(s_g *sg, int *i, char quote);

int	check_var(s_g *s_g, int i);

// LISTE CHAINER D'EXECUTION
void add_token(to_lst *to_lst, char *prompt_str, int tokenType, s_g *s_g);
void initTokenTest(s_g *s_g, to_lst *to_lst);
void afficher_tokens(to_lst *to_lst);

int	check_empty_prompt(to_lst *to_lst);
int	check_files_exist(to_lst *to_lst, s_g *s_g);
void clear_to_lst(to_lst *to_lst);

//s_g->pathVarTempo = gc_malloc(&s_g->gc ,sizeof(char) * 9999);

// LES DERNIERES
int	son(s_g *s_g, char *input);
int	exec_son(s_g *s_g, int *fds, char *input, char *input_without);
void	redirection_pipe(s_g *s_g, int fds[2]);
void	exec_prompt(s_g *s_g, to_lst *to_lst, struct sigaction *sa);
void	setup_fd_redir(s_Token *cmd_ptr, struct sigaction *sa, s_g *s_g);
s_Token	*move_on_prompt(s_Token *cmd_ptr, s_g *s_g);
void	init_struct_for_pipe(to_lst *to_lst, s_g *s_g);
void	ft_nbr_of_pipe(to_lst *to_lst, s_g *s_g);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

#endif
