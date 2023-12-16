/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:41:30 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/16 15:26:22 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	is_builtin(t_command *cmd)
{
	if (ft_strncmp(cmd->first_cmd->full_path, "cd", 2))
		return (cd(cmd));
	else if (ft_strncmp(cmd->first_cmd->full_path, "echo", 4))
		return (echo(cmd));
	else if (ft_strncmp(cmd->first_cmd->full_path, "env", 3))
		return (ft_env(cmd));
	else if (ft_strncmp(cmd->first_cmd->full_path, "exit", 4))
		return (ft_exit(cmd));
	else if (ft_strncmp(cmd->first_cmd->full_path, "export", 6))
		return (ft_export(cmd));
	else if (ft_strncmp(cmd->first_cmd->full_path, "pwd", 3))
		return (pwd(cmd));
	else if (ft_strncmp(cmd->first_cmd->full_path, "unset", 5))
		return (unset(cmd));
	else
	{
		printf("%s: ", cmd->first_token);
		ft_error("Command Not Found", -1);
	}
}

int	execution(t_command *s_cmd)
{
	pid_t			pid;
	t_simple_cmd	*head;
	t_simple_cmd	*cmd;

	cmd = s_cmd->first_cmd;
	head = cmd;
	while (cmd)
	{
		pid = fork();
		if (pid == -1)
			perror("Fork:");
		else if (pid == 0)
		{
			dup2(STDIN_FILENO, cmd->infile);
			dup2(STDOUT_FILENO, cmd->outfile);
			if (!cmd->full_path)
				is_builtin(s_cmd);
			else
			{
				if (execve(cmd->full_path, cmd->scmd, cmd->envp) == -1)
				{
					printf("%s: ", cmd->first_token);
					ft_error("Command Not Found", -1);
				}
			}
		}
		cmd = cmd->next;
	}
	cmd = head;
}
