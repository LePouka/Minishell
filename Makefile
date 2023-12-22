#------------------------------------------------#
#   NAME                                         #
#------------------------------------------------#
NAME		:= Minishell

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
SRC_DIR		:= src
OBJ_DIR		:= obj
LIBFT_DIR	:= libft
SRCS		:=					\
	main.c						\
<<<<<<< HEAD
	builtin/cd.c				\
	builtin/pwd.c				\
	builtin/env.c				\
	builtin/exit.c				\
	builtin/echo.c				\
	builtin/unset.c				\
	builtin/export.c			\
	env/get_true_env.c			\
	utils/ft_error.c			\
	utils/split_cmd.c			\
	exec/pipes.c				\
	exec/ft_exec.c				\
	exec/execution.c			\
	exec/clear_pipes.c			\
	parsing/free.c				\
	parsing/lexer.c				\
	parsing/parser.c			\
	parsing/get_env.c			\
	parsing/lst_token.c			\
	parsing/expanding.c			\
	parsing/add_tokens.c		\
	parsing/syntax_pipe.c		\
	parsing/lexer_utils.c		\
	parsing/get_cmd_path.c		\
	parsing/syntax_quotes.c		\
	parsing/handle_quotes.c		\
	parsing/delete_quotes.c		\
	parsing/add_token_word.c	\
	parsing/get_simple_cmds.c	\
	parsing/syntax_analysis.c	\
	parsing/syntax_redirection.c
=======************************************************************************ */

#ifndef LEXER_H
# define LEXER_H

#include "../libft/include/libft.h"
#include <stdio.h>
#includ/echo.c					\
	builtin/unset.c					\
	builtin/export.c				\
	env/env_init.c					\
	env/clear_env.c					\
	env/get_true_env.c				\
	utils/ft_error.c				\
	utils/split_cmd.c				\
	exec/pipes.c					\
	exec/ft_exec.c					\
	exec/execution.c				\
	exec/clear_pipes.c				\
	parsing/error_handling/free.c			\
	parsing/tokenization/lexer.c			\
	parsing/tokenization/lst_token.c		\
	parsing/tokenization/add_tokens.c		\
	parsing/tokenization/syntax_pipe.c		\
	parsing/tokenization/lexer_utils.c		\
	parsing/tokenization/syntax_quotes.c		\
	parsing/tokenization/add_token_word.c		\
	parsing/tokenization/syntax_analysis.c		\
	parsing/tokenization/syntax_redirection.c	\
	parsing/expansion/expanding.c			\
	parsing/expansion/handle_quotes.c		\
	parsing/expansion/delete_quotes.c		\
	parsing/parser.c				\
	parsing/get_env.c				\
	parsing/get_cmd_path.c				\
	parsing/get_simple_cmds.c			\
	parsing/redirections1.c				\
	parsing/redirections2.c
>>>>>>> main
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT		:= $(LIBFT_DIR)/libft.a

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g
CPPFLAGS	:= -I inc

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
RM			:= rm -f
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LIBFT) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

norminette:
	norminette inc
	norminette src

re: fclean all

run: re
	-./$(NAME)

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#
.PHONY: clean fclean norminette re run
