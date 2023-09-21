/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listeExecution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:18:51 by chugot            #+#    #+#             */
/*   Updated: 2023/09/20 11:05:15 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_lst *t_lst, char *prompt_str, int token_type, t_g *t_g)
{
	t_token	*new_node;
	t_token	*last_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	new_node->prompt_str = ft_gcstrdup(prompt_str, t_g);
	new_node->token_type = token_type;
	new_node->next = NULL;
	last_node = t_lst->head;
	if (last_node == NULL)
	{
		t_lst->head = new_node;
		t_g->t_lst = t_lst;
	}
	else
	{
		while (last_node->next != NULL)
		{
			last_node = last_node->next;
		}
		last_node->next = new_node;
	}
}

int	check_files_exist(t_lst *t_lst, t_g *t_g)
{
	t_token	*current;

	current = t_lst->head;
	while (current != NULL)
	{
		if (current->token_type == 3)
		{
			if (access(current->prompt_str, F_OK) == -1)
			{
				t_g->exit_ret = 1;
				printf("minishell: %s: No such file or directory\n",
					current->prompt_str);
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

int	check_empty_prompt(t_lst *t_lst)
{
	int		i;
	t_token	*current;
	int		is_empty;

	current = t_lst->head;
	while (current != NULL)
	{
		is_empty = 0;
		i = 0;
		while (current->prompt_str[i] != 0)
		{
			if (current->prompt_str[i] != ' ')
				is_empty = 1;
			i++;
		}
		if (is_empty == 0)
			return (0);
		current = current->next;
	}
	return (1);
}

void	afficher_tokens(t_lst *t_lst)
{
	t_token	*current;

	current = t_lst->head;
	while (current != NULL)
	{
		printf("Token: %s, Type: %d\n",
			current->prompt_str, current->token_type);
		current = current->next;
	}
}

void	clear_t_lst(t_lst *t_lst)
{
	t_token	*current;
	t_token	*temp;

	current = t_lst->head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	t_lst->head = NULL;
}
