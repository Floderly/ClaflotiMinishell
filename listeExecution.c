/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listeExecution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fderly <fderly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:18:51 by chugot            #+#    #+#             */
/*   Updated: 2023/09/15 18:42:26 by fderly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(to_lst *to_lst, char *prompt_str, int tokenType, s_g *s_g)
{
	s_Token	*new_node;
	s_Token	*last_node;

	new_node = (s_Token *)malloc(sizeof(s_Token));
	if (new_node == NULL)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	new_node->prompt_str = ft_gcstrdup(prompt_str, s_g);
	new_node->tokenType = tokenType;
	new_node->next = NULL;
	last_node = to_lst->head;
	if (last_node == NULL)
	{
		to_lst->head = new_node;
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

int	check_files_exist(to_lst *to_lst, s_g *s_g)
{
	s_Token	*current;

	//(void)s_g; //test exit
	current = to_lst->head;
	while (current != NULL) 
	{
		if (current->tokenType == 3) 
		{
			if (access(current->prompt_str, F_OK) == -1)
			{
				s_g->exit_ret = 1;
				printf("minishell: %s: No such file or directory\n", current->prompt_str);
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

int	check_empty_prompt(to_lst *to_lst)
{
	int		i;
	s_Token	*current;
	int		is_empty;

	current = to_lst->head;
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

void	afficher_tokens(to_lst *to_lst)
{
	s_Token	*current;

	current = to_lst->head;
	while (current != NULL)
	{
		printf("Token: %s, Type: %d\n", current->prompt_str, current->tokenType);
		current = current->next;
	}
}

void	clear_to_lst(to_lst *to_lst)
{
	s_Token	*current;
	s_Token	*temp;

	current = to_lst->head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	to_lst->head = NULL;
}
