/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:18:51 by chugot            #+#    #+#             */
/*   Updated: 2023/08/02 16:18:54 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void addToken(TokenList *token_list, char *prompt_str, int tokenType, s_gbl *s_gbl)
{
	s_Token *newNode = (s_Token *)gc_malloc(&s_gbl->gc, sizeof(s_Token));
	if (newNode == NULL)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}

	newNode->prompt_str = ft_gcstrdup(prompt_str, s_gbl);
	newNode->tokenType = tokenType;
	newNode->next = NULL;

	s_Token *lastNode = token_list->head;
	if (lastNode == NULL)
	{
		token_list->head = newNode;
	}
	else
	{
		while (lastNode->next != NULL)
		{
			lastNode = lastNode->next;
		}
		lastNode->next = newNode;
	}
}

void initTokenList(TokenList *token_list)
{
	token_list->head = NULL;
}

void initTokenTest(s_gbl *s_gbl, TokenList *token_list)
{
	addToken(token_list, "echo", 1, s_gbl);
	addToken(token_list, "abc", 2, s_gbl);
	addToken(token_list, "|", 3, s_gbl);
	addToken(token_list, "rev", 1, s_gbl);
	addToken(token_list, "test1", 5, s_gbl);

	// Print tokens with types
	s_Token *current = token_list->head;
	while (current != NULL)
	{
		printf("Token: %s, Type: %d\n", current->prompt_str, current->tokenType);
		current = current->next;
	}
}

void afficherTokens(TokenList *token_list)
{
	s_Token *current = token_list->head;
	while (current != NULL)
	{
		printf("Token: %s, Type: %d\n", current->prompt_str, current->tokenType);
		current = current->next;
	}
}
