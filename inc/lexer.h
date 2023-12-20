/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:57:10 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/20 15:30:24 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "../libft/include/libft.h"
#include <stdio.h>
# define WORD 1
# define REDIRECTION 2
# define PARENTHESIS 3
# define PIPE 4
# define AND 5
# define SEMI 6

//# define COMMAND 0
//# define OPTION 1
//# define ARGUMENT 2
//# define HEREDOC 3
//# define OUTFILE 4
//# define APPEND 5
//# define INFILE 6
//# define PIPE 7
typedef struct			s_token
{
	char		*str;
	int		type;
	//bool		expanded;
	struct s_token		*prev;
	struct s_token		*next;
}				t_token;

typedef struct			s_simple_cmd
{
	char		*full_path;
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
	char			*string;
	//char			**envp;
	//char			**argv;
	struct s_token			*first_token;
	struct s_simple_cmd		*first_cmd;
	struct s_env			*lst_env;
}					t_command;

t_command	*tokenize(char *command);
t_command	*set_simple_commands(t_command *cmd_struct);

t_token	*init_token(char *value, int type);
t_token	*token_last(t_token *lst);

t_simple_cmd	*cmd_last(t_simple_cmd *lst);

t_command	*get_env_vars(t_command *cmd_struct, char **envp);

void	add_token(t_token **lst, t_token *new_token);
void	add_simple_cmd(t_simple_cmd **lst, t_simple_cmd *new_cmd);
void	add_env_var(t_env **lst, t_env *new_env);
void	free_cmd(t_command *cmd);
void	check_syntax(t_command *cmd_struct);
void	free_split(char **str);

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

int	check_types(t_command *cmd_struct);
int	check_quotes(t_command *cmd_struct);
int	check_redirections(t_command *cmd_struct);
int	check_between_pipes(t_command *cmd_struct);

char	*get_cmd_path(char *cmd, t_command *cmd_struct);

#endif