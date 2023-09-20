/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:30:34 by fderly            #+#    #+#             */
/*   Updated: 2023/09/20 10:33:30 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_g *t_g)
{
	int	i;

	i = -1;
	while (t_g->exp_env[++i])
		printf("declare -x %s\n", t_g->exp_env[i]);
}

void	swap_export(t_g *t_g)
{
	int		i;
	char	*tmp;

	i = 0;
	while (t_g->exp_env[i + 1])
	{
		if (ft_strcmp(t_g->exp_env[i], t_g->exp_env[i + 1]) > 0)
		{
			tmp = t_g->exp_env[i];
			t_g->exp_env[i] = t_g->exp_env[i + 1];
			t_g->exp_env[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

void	add_export(char *input, t_g *t_g)
{
	int	i;
	int	j;

	i = 0;
	while (t_g->exp_env[i])
	{
		if (ft_strcmp(ft_clear_env(t_g->exp_env[i], t_g),
				ft_clear_env(input, t_g)) == 0)
			break ;
		i++;
		t_g->exp_env[i] = gc_malloc(&t_g->gc, sizeof(char) * 99999);
	}
	if (t_g->exp_env[i] == 0)
	{
		t_g->exp_env[i] = gc_malloc(&t_g->gc, sizeof(char) * 999);
	}
	j = -1;
	while (input[++j])
		t_g->exp_env[i][j] = input[j];
	t_g->exp_env[i][j] = 0;
	modif_exp(t_g, i);
	i++;
	t_g->exp_env[i] = 0;
	swap_export(t_g);
}

int	own_export(char *input, t_g *t_g)
{
	char	**args;

	args = ft_split(input, ' ');
	if (!args[1])
	{
		swap_export(t_g);
		print_export(t_g);
		return (0);
	}
	else if (('0' <= args[1][0] && args[1][0] <= '9') || args[1][0] == '=')
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	add_export(args[1], t_g);
	add_env(args[1], t_g);
	return (0);
}
