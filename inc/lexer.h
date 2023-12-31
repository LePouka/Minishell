/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:57:10 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/07 14:29:59 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "../libft/include/libft.h"
#include <stdio.h>
#include <fcntl.h>

# define COMMAND 1
# define ARGUMENT 2
# define REDIRECTION 3
# define PIPE 4
# define PARENTHESIS 5
# define SEMI 6
# define AND 7

typedef struct			s_token
{
	char		*str;
	int		type;
	struct s_token		*prev;
	struct s_token		*next;
}				t_token;

typedef struct			s_simple_cmd
{
	char		*full_path;
	int		in;
	int		out;
	int		infile;
	int		outfile;
	struct s_token		*first_token;
	struct s_simple_cmd	*prev;
	struct s_simple_cmd	*next;
}				t_simple_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef	struct				s_command
{
	int	flag_s;
	int	flag_d;
	char			*string;
	struct s_token			*first_token;
	struct s_simple_cmd		*first_cmd;
	struct s_env			*lst_env;
}					t_command;

t_command	*tokenize(char *command, t_env *env);

t_token	*init_token(char *value, int type);
t_token	*token_last(t_token *lst);

t_simple_cmd	*cmd_last(t_simple_cmd *lst);

t_env	*get_env_vars(char **envp);

void	add_token(t_token **lst, t_token *new_token);
void	add_simple_cmd(t_simple_cmd **lst, t_simple_cmd *new_cmd);
void	add_env_var(t_env **lst, t_env *new_env);
void	free_cmd(t_command *cmd);
void	free_split(char **str);
void	free_env_vars(t_env *env_var);

int	add_token_word(t_command *cmd_struct, int i);
int	add_token_redirection(t_command *cmd_struct, int i);
int	add_token_parenthesis(t_command *cmd_struct, int i);
int	add_token_pipe(t_command *cmd_struct, int i);
int	add_token_and(t_command *cmd_struct, int i);
int	add_token_semi(t_command *cmd_struct, int i);
int	is_space(char c);
int	is_parenthesis(char c);
int	is_redirection(char c);
int	is_word(char c);
int	is_builtin(char *str);
int	redirect_output(char *file, int old_fd, t_command *cmd_struct);
int	redirect_input(char *file, int old_fd, t_command *cmd_struct);
int	redirect_append(char *file, int old_fd, t_command *cmd_struct);
int	check_options(t_command *cmd_struct);

void	var_not_double_quoted(char *str);
void	check_if_builtin(t_command *cmd_struct);

int	check_quotes(t_command *cmd_struct);
int	check_redirections(t_command *cmd_struct);
int	check_between_pipes(t_command *cmd_struct);
int	check_syntax(t_command *cmd_struct);
int	expanding(t_command *cmd_struct);
int	handle_redirections(t_command *cmd_struct);
int	set_simple_commands(t_command *cmd_struct);
int	delete_quotes(t_command *cmd);
char	*get_cmd_path(char *cmd, t_command *cmd_struct);
void	go_through_simple_cmds(t_simple_cmd *simple_cmd);

#endif
