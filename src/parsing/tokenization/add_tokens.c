/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:32:38 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/25 01:31:38 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	add_token_redirection(t_command *cmd_struct, int i)
{
	int		j;
	int		len;
	char	*cmd;
	t_token	*new_token;

	j = i;
	len = 0;
	while (cmd_struct->string[i] && is_redirection(cmd_struct->string[i]))
	{
		i++;
		len++;
	}
	cmd = ft_substr(cmd_struct->string, j, len);
	new_token = init_token(cmd, REDIRECTION);
	add_token(&cmd_struct->first_token, new_token);
	return (i);
}

int	add_token_pipe(t_command *cmd_struct, int i)
{
	int		j;
	int		len;
	char	*cmd;
	t_token	*new_token;

	j = i;
	len = 0;
	while (cmd_struct->string[i] && cmd_struct->string[i] == '|')
	{
		i++;
		len++;
	}
	cmd = ft_substr(cmd_struct->string, j, len);
	new_token = init_token(cmd, PIPE);
	add_token(&cmd_struct->first_token, new_token);
	return (i);
}

void	check_if_builtin(t_command *cmd_struct)
{
	t_token	*token;

	token = cmd_struct->first_token;
	while (token)
	{
		if (is_builtin(token->str))
			token->type = COMMAND;
		token = token->next;
	}
}
