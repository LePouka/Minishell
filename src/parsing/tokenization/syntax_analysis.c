/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:25:26 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 12:48:07 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

int	check_types(t_command *cmd_struct)
{
	t_token	*token;
	char	c;

	token = cmd_struct->first_token;
	while (token)
	{
		if (token->type == SEMI || (token->type == PIPE
				&& ft_strlen(token->str) > 1)
			|| (token->type == REDIRECTION
				&& ft_strlen(token->str) > 2)
			|| token->type == AND)
		{
			c = token->str[0];
			g_status = 2;
			ft_dprintf(2, "Syntax error near unexpected token `%c'\n", c);
			return (0);
		}
		token = token->next;
	}
	return (1);
}

int	check_pipe_location(t_command *cmd_struct)
{
	t_token	*token;

	token = cmd_struct->first_token;
	if (token->type == PIPE || token_last(token)->type == PIPE)
	{
		g_status = 2;
		ft_dprintf(2, "Syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

int	check_syntax(t_command *cmd_struct)
{
	if (cmd_struct->first_token)
	{
		if (check_types(cmd_struct) && check_quotes(cmd_struct)
			&& check_pipe_location(cmd_struct)
			&& check_between_pipes(cmd_struct)
			&& check_redirections(cmd_struct))
			return (1);
	}
	return (0);
}

int	check_option_token(t_token *token)
{
	if (token->str[0] == '-' && (token->prev == NULL
			|| token->prev->type == PIPE))
	{
		g_status = 2;
		ft_dprintf(2, "minishell: %s: command not found\n", token->str);
		return (0);
	}
	return (1);
}

int	check_options(t_command *cmd_struct)
{
	t_token	*token;

	token = cmd_struct->first_token;
	while (token)
	{
		if (!check_option_token(token))
			return (0);
		token = token->next;
	}
	return (1);
}
