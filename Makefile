# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fderly <fderly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/17 12:00:49 by chugot            #+#    #+#              #
#    Updated: 2023/08/27 02:51:54 by fderly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

SRCS =	minishell.c \
		minishell2.c \
		ft_utils/ft_split.c \
		ft_utils/ft_strjoin.c \
		ft_utils/ft_strnstr.c \
		ft_utils/ft_strdup.c \
		ft_utils/ft_gcstrdup.c \
		ft_utils/skipSpace.c \
		ft_utils/ft_strcmp.c \
		ft_utils/ft_strncmp.c \
		ft_utils/ft_putstr_fd.c \
		ft_utils/ft_putendl_fd.c \
		builtins/builtin_base.c \
		Exec/exec_test1.c \
		Exec/pipex_free.c \
		Exec/execve_cmd.c \
		parsing/parsing.c \
		parsing/quoteCheck.c \
		parsing/varEnvChang.c \
		parsing/put_maillon_str.c \
		parsing/check_pipe_at_start.c \
		parsing/add_list_exec.c \
		parsing/put_sorti.c \
		parsing/put_entry.c \
		listeExecution.c \

LIBGCDIR = gc
LIBGC = libgc.a
LIBGCFLAGS = -L $(LIBGCDIR) -l:$(LIBGC)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -lreadline -lhistory

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS) $(LIBGCDIR)/$(LIBGC)
			$(CC) $(OBJS) -o $(NAME) $(CFLAGS) $(LIBGCFLAGS)

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
