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

void addToken(TokenList *token_list, char *prompt_str, int tokenType, s_g *s_g)
{
	s_Token *newNode = (s_Token *)malloc(sizeof(s_Token));
	if (newNode == NULL)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}

	newNode->prompt_str = ft_gcstrdup(prompt_str, s_g);
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

void initTokenTest(s_g *s_g, TokenList *token_list)
{
	(void)s_g;
	// EXEMPLE NUMERO 1
	//Ligne de commande shell pour tester bash : echo abc | rev > testSorti
	//addToken(token_list, "LE TEST", 1, s_g);
	//addToken(token_list, "|", 2, s_g);
	//addToken(token_list, "rev", 1, s_g);
	//addToken(token_list, "testSorti", 4, s_g);
	
	/*
	EXEMPLE NUMERO 2
	Ligne de commnade shell pour tester bash : rev < testEntree | cat -e | rev > testSorti
	Doit mettre un $ devant la phrase dans le fichier testEntree, inverse le sens, puis cat -e et re inverse
	addToken(token_list, "rev", 1, s_g);
	addToken(token_list, "testEntree", 3, s_g);
	addToken(token_list, "|", 3, s_g);
	addToken(token_list, "cat -e", 1, s_g);
	addToken(token_list, "|", 3, s_g);
	addToken(token_list, "rev", 1, s_g);
	addToken(token_list, "testSorti", 4, s_g);
	*/

	/*
	EXEMPLE NUMERO 3
	Ligne de commande shell pour tester bash : ls -l > testFile | rev < testFile | cat -e > testSortiN3
	Met ls -l dans sorti testFile
	addToken(token_list, "ls -l", 1, s_g);
	addToken(token_list, "testFile", 4, s_g);
	addToken(token_list, "|", 3, s_g);
	addToken(token_list, "rev", 1, s_g);
	addToken(token_list, "testFile", 3, s_g);
	addToken(token_list, "|", 3, s_g);
	addToken(token_list, "cat -e", 1, s_g);
	addToken(token_list, "testSortiN3", 4, s_g);
	*/

	// Print tokens with types
	s_Token *current = token_list->head;
	while (current != NULL)
	{
		printf("Token: %s, Type: %d\n", current->prompt_str, current->tokenType);
		current = current->next;
	}
}

int check_files_exist(TokenList *token_list) 
{
    s_Token *current = token_list->head;
    
    while (current != NULL) 
	{
        if (current->tokenType == 3) 
		{
            if (access(current->prompt_str, F_OK) == -1)
			{
				printf("%s non existant\n", current->prompt_str);
                return 0;
			}
        }
        current = current->next;
    }
    return 1;
}

int	check_empty_prompt(TokenList *token_list)
{
	int	i;
	s_Token *current = token_list->head;
	int	is_empty;

	while (current != NULL)
	{
		if (current->tokenType == 1)
		{
			is_empty = 0;
			i = 0;
			while (current->prompt_str[i] != 0)
			{
				if (current->prompt_str[i] != ' ')
					is_empty = 1;
				i++;
			}
		}
		if (is_empty == 0)
			return (0);
		current = current->next;
	}
	return (1);
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

void clear_token_list(TokenList *token_list)
{
    s_Token *current = token_list->head;
    
    while (current != NULL) {
        s_Token *temp = current;
        current = current->next;
		//(void)temp;
        free(temp);
    }
    
    token_list->head = NULL;
}