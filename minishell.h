/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:46:51 by chugot            #+#    #+#             */
/*   Updated: 2023/09/20 17:40:19 by fderly           ###   ########.fr       */
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

extern int	g_signal_flag;

typedef struct t_g
{
	t_gcan	gc;
	char	**mini_env;
	char	**exp_env;
	char	*input;
	char	*i2;
	char	*path_var_tempo;
	int		s_st;
	int		ls_st;
	pid_t	pid;
	int		status;
	int		cmd_nbr;
	int		pipe_nbr;
	int		index_cmd;
	int		sigaction_flag;
	char	**history_tab;
	int		history_count;
	char	*cur_pwd;
	char	*new_pwd;
	int		exit_ret;
	int		out_fd;
	int		last_fd;
}	t_g;

typedef struct t_token {
	char			*prompt_str;
	int				token_type;
	struct t_token	*next;
}	t_token;

typedef struct t_lst {
	t_token	*head;
}	t_lst;

// MINISHELL2, ENV
void	clone_env(t_g *t_g, char **env);
void	export_test(t_g *t_g, char *nomVar, char *arg);
void	modif_exp(t_g *t_g, int i);
int		is_equal(char *s);

//FONCTION SIGNAL
void	signal_handler(int signal);
void	treat_signal(struct sigaction *sa, t_g *t_g);

// FONCTIONS EXECUTION
void	exec_prompt(t_g *t_g, t_lst *t_lst, struct sigaction *sa);
int		son(t_g *t_g, char *input);
void	path_user(t_g *t_g, char *input);
char	*clone_input_without_option(char *input, char *input_without_option);
void	path(t_g *t_g, char *argv);
int		red_simp_entry(char *infile, t_g *t_g);
int		red_cond_entry(char *keycode, struct sigaction *sa, t_g *t_g);
int		red_simp_exit(char *outfile, t_g *t_g);
int		red_doub_exit(char *outfile, t_g *t_g);

//built in
int		if_builtin_father(char *prompt, t_g *t_g);
int		if_builtin(t_g *t_g, char *input);
void	own_env(t_g *t_g);
int		own_pwd(t_g *t_g);
int		own_export(char *input, t_g *t_g);
void	swap_export(t_g *t_g);
void	own_echo(char *input);
void	own_exit(char *input, t_g *t_g);
void	own_cd(char *str, t_g *t_g);
void	own_unset(char *input, t_g *t_g);
void	print_export(t_g *t_g);
void	add_env(char *arg, t_g *t_g);
int		own_pwd_check(t_g *t_g);

// FONCTIONS BUILTIN
int		if_builtin(t_g *t_g, char *input);
void	own_env(t_g *t_g);

// FONCTION UTILS
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
char	*ft_gcstrdup(const char *s, t_g *t_g);
void	trim_spaces(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);

void	free_tab(char **tab);
void	error_msg(char *msg, t_g *t_g);
int		count_args(char **args);
int		check_arg(char *arg);
int		ft_isnum(char *str);

//FONCTION AUTRE
int		skip_space(char *string, int i); // A REFAIRE AVEC +1 ?
char	*ft_clear_env(char *str, t_g *t_g);

// FONCTION PARSING
int		parsing(t_g *t_g, t_lst *t_lst);
int		quote_check(char *input);
int		var_env_chang(t_g *t_g);
int		redirection(t_g *t_g);
int		check_pipe_at_start(t_g *t_g);

int		add_list_exec(t_g *t_g, t_lst *t_lst);
void	put_maillon_str(t_g *t_g, t_lst *t_lst);
int		put_red_deli_str(t_g *t_g, t_lst *t_lst);
int		put_red_in_str(t_g *t_g, t_lst *t_lst);
int		put_red_out_str(t_g *t_g, t_lst *t_lst);
int		put_red_append_str(t_g *t_g, t_lst *t_lst);

int		put_entry(t_g *t_g, t_lst *t_lst);
int		put_sorti(t_g *t_g, t_lst *t_lst);
void	pass_quote(t_g *sg, int *i, char quote);

int		check_var(t_g *t_g, int i);

// LISTE CHAINER D'EXECUTION
void	add_token(t_lst *t_lst, char *prompt_str, int tokenType, t_g *t_g);
void	initTokenTest(t_g *t_g, t_lst *t_lst);
void	afficher_tokens(t_lst *t_lst);

int		check_empty_prompt(t_lst *t_lst);
int		check_files_exist(t_lst *t_lst, t_g *t_g);
void	clear_t_lst(t_lst *t_lst);

//t_g->pathVarTempo = gc_malloc(&t_g->gc ,sizeof(char) * 9999);

// LES DERNIERES
int		son(t_g *t_g, char *input);
int		exec_son(t_g *t_g, int *fds, char *input, char *input_without);
void	redirection_pipe(t_g *t_g, int fds[2]);
void	exec_prompt(t_g *t_g, t_lst *t_lst, struct sigaction *sa);
void	setup_fd_redir(t_token *cmd_ptr, struct sigaction *sa, t_g *t_g);
t_token	*move_on_prompt(t_token *cmd_ptr, t_g *t_g);
void	init_struct_for_pipe(t_lst *t_lst, t_g *t_g);
void	ft_nbr_of_pipe(t_lst *t_lst, t_g *t_g);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

#endif
