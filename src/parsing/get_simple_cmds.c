/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_simple_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:36:26 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/26 20:30:23 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	is_absolute_path(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			j++;
		i++;
	}
	if (j == 1 || j == 0)
		return (0);
	if (access(cmd, F_OK) == 0)
		return (1);
	return (0);
}

int	cmd_contains_builtin(t_simple_cmd *simple_cmd)
{
	t_token	*token;

	token = simple_cmd->first_token;
	while (token)
	{
		if (is_builtin(token->str))
		{
			token->type = COMMAND;
			return (1);
		}
		token = token->next;
	}
	return (0);
}

int	set_command_path(t_command *cmd_struct)
{
	t_simple_cmd	*simple_cmd;
	t_token	*token;
	char	*path;

	path = NULL;

	simple_cmd = cmd_struct->first_cmd;
	while (simple_cmd)
	{
		token = simple_cmd->first_token;
		while (token)
		{
			if (is_absolute_path(token->str))
			{
				token->type = COMMAND;
				path = strdup(token->str);
				simple_cmd->full_path = path;
				if (!simple_cmd->next)
					return (1);
				simple_cmd = simple_cmd->next;
			}
			if (is_builtin(token->str))
			{
				break ;
			}
			path = get_cmd_path(token->str, cmd_struct);
			if (!simple_cmd->full_path && path)
			{
				simple_cmd->full_path = path;
				token->type = COMMAND;
				if (!simple_cmd->next)
					return (1);
			}
			token = token->next;	
		}
		if (!simple_cmd->full_path && !cmd_contains_builtin(simple_cmd) && !simple_cmd->prev)
		{
			printf("minishell: %s: command not found\n", simple_cmd->first_token->str);
			return (0);
		}
		simple_cmd = simple_cmd->next;
	}
	return (1);
}

t_simple_cmd	*init_simple_cmd(t_token *head_tkn)
{
	t_simple_cmd	*new_simple_cmd;

	new_simple_cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (!new_simple_cmd)
		return (NULL);
	new_simple_cmd->full_path = NULL;
	new_simple_cmd->full_path = NULL;
	new_simple_cmd->infile = 0;
	new_simple_cmd->outfile = 1;
	new_simple_cmd->first_token = head_tkn;
	new_simple_cmd->prev = NULL;
	new_simple_cmd->next = NULL;
	return (new_simple_cmd);
}

int	set_simple_commands(t_command *cmd_struct)
{
	t_token			*token;
	t_simple_cmd	*simple_cmd_struct;

	token = cmd_struct->first_token;
	while (token)
	{
		simple_cmd_struct = init_simple_cmd(init_token(token->str,
					token->type));
		add_simple_cmd(&cmd_struct->first_cmd, simple_cmd_struct);
		token = token->next;
		while (token && token->type != PIPE)
		{
			add_token(&simple_cmd_struct->first_token,
				init_token(token->str, token->type));
			token = token->next;
		}
		if (token && token->type == PIPE)
			token = token->next;
	}
	if (!set_command_path(cmd_struct))
		return (0);
	return (1);
}
