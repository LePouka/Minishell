/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:56:37 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/23 21:00:11 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redirection(char *redirection, char *file, t_simple_cmd *simple_cmd
				, t_command *cmd_struct)
{
	if (!ft_strcmp(redirection, ">"))
		simple_cmd->outfile = redirect_output(file,
				simple_cmd->outfile, cmd_struct);
	else if (!ft_strcmp(redirection, "<"))
		simple_cmd->infile = redirect_input(file,
				simple_cmd->infile, cmd_struct);
	else if (!ft_strcmp(redirection, ">>"))
		simple_cmd->outfile = redirect_append(file,
				simple_cmd->outfile, cmd_struct);
}

void	check_redirection(t_simple_cmd *simple_cmd, t_command *cmd_struct)
{
	t_token	*token;

	token = simple_cmd->first_token;
	while (token)
	{
		if (!token->next)
			break ;
		if (token->type == REDIRECTION && token->next)
		{
			set_redirection(token->str, token->next->str,
				simple_cmd, cmd_struct);
			token = token->next;
		}
		token = token->next;
	}
}

int	check_last_token(t_simple_cmd *simple_cmd)
{
	t_token	*token;

	token = simple_cmd->first_token;
	if (token_last(token)->type == REDIRECTION)
	{
		g_status = 2;
		ft_dprintf(2, "minishell: ");
		ft_dprintf(2, "Syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

int	handle_redirections(t_command *cmd_struct)
{
	t_simple_cmd	*simple_cmd;

	simple_cmd = cmd_struct->first_cmd;
	while (simple_cmd)
	{
		if (!check_last_token(simple_cmd))
			return (0);
		check_redirection(simple_cmd, cmd_struct);
		simple_cmd = simple_cmd->next;
	}
	return (1);
}
