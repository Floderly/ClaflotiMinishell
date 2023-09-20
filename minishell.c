/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:14:19 by chugot            #+#    #+#             */
/*   Updated: 2023/09/20 17:39:50 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_flag = 0;

void	main_loop(t_g *t_g, struct sigaction *sa, t_lst *t_lst)
{
	while (1)
	{
		g_signal_flag = 0;
		t_g->input = readline("Minishell> ");
		if (!t_g->input)
		{
			printf("Don't leave me !\n");
			free(t_g->input);
			gc_clean(&t_g->gc);
			exit(t_g->exit_ret);
		}
		if (t_g->input[0] != '\0')
		{
			add_history(t_g->input);
			if (parsing(t_g, t_lst) == 1)
				exec_prompt(t_g, t_lst, sa);
		}
		free(t_g->input);
		clear_t_lst(t_lst);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_g					t_g;
	t_lst				t_lst;
	struct sigaction	sa;
	char				cwd[PATH_MAX];

	(void)argc;
	(void)argv;
	t_g.exit_ret = 0;
	if (getcwd(cwd, PATH_MAX))
		t_g.cur_pwd = cwd;
	gc_init(&t_g.gc);
	t_lst.head = NULL;
	clone_env(&t_g, env);
	treat_signal(&sa, &t_g);
	main_loop(&t_g, &sa, &t_lst);
	gc_clean(&t_g.gc);
	return (0);
}
