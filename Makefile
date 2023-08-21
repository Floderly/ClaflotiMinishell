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
		ft_utils/ft_split.c \
		ft_utils/ft_strjoin.c \
		ft_utils/ft_strnstr.c \
		ft_utils/ft_strdup.c \
		ft_utils/skipSpace.c \
		ft_utils/ft_strcmp.c \
		ft_utils/ft_strncmp.c \
		builtins/own_echo.c \
		builtins/builtin_base.c \
		pipex_free.c \
		execve_cmd.c \
		parsing/parsing.c \
		parsing/quoteCheck.c \
		parsing/varEnvChang.c \
		parsing/redirection.c \

LIBGCDIR = gc
LIBGC = libgc.a
LIBGCFLAGS = -L $(LIBGCDIR) -l:$(LIBGC)

CC = gcc

FLAGS = -Wall -Wextra -Werror -lreadline -lhistory

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS) $(LIBGCDIR)/$(LIBGC)
			$(CC) $(OBJS) -o $(NAME) $(FLAGS) $(LIBGCFLAGS)

$(LIBGCDIR)/$(LIBGC):
	make -C $(LIBGCDIR)

all:	$(NAME)

clean:
		rm -f $(OBJS)

fclean:
		rm -f $(OBJS) $(NAME)
		make -C ${LIBGCDIR} fclean

re:		fclean $(NAME)

.PHONY:	all clean fclean re
