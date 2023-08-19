# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clara <clara@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/17 12:00:49 by chugot            #+#    #+#              #
#    Updated: 2023/08/17 17:48:26 by chugot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

SRCS =	minishell.c \
		ft_split.c \
		ft_strjoin.c \
		ft_strnstr.c \
		pipex_free.c \
		execve_cmd.c \
		parsing/parsing.c \
		parsing/quoteCheck.c \
		parsing/varEnvChang.c \

CC = gcc

FLAGS = -Wall -Wextra -Werror -lreadline -lhistory

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME) $(FLAGS)

all:	$(NAME)

clean:
		rm -f $(OBJS)

fclean:
		rm -f $(OBJS) $(NAME)

re:		fclean $(NAME)

.PHONY:	all clean fclean re
