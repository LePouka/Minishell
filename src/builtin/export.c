/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:20:07 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/23 20:32:16 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_non_valid(char *value)
{
	int	i;

	if (!value[0] || (!ft_isalpha(value[0]) && value[0] != '_'))
		return (ft_dprintf(2, \
			"minishell: export: `%s': not a valid identifier\n", value), 1);
	i = 0;
	while (value[i] && value[i] != '=')
	{
		if (!ft_isalnum(value[i]) && value[i] != '_')
		{
			return (ft_dprintf(2, \
				"minishell: export: `%s': not a valid identifier\n", value), 1);
		}
		i++;
	}
	while (value[i])
	{
		if (!ft_isprint(value[i]))
		{
			return (ft_dprintf(2, \
				"minishell: export: `%s': not a valid identifier\n", value), 1);
		}
		i++;
	}
	return (0);
}

void	no_arg(t_env *env)
{
	t_env	*head;

	head = env;
	while (env && env->key)
	{
		if (env->value && env->value[0])
		{
			ft_dprintf(1, "export %s=\"%s\"\n", env->key, env->value);
		}
		else
		{
			ft_dprintf(1, "export %s\n", env->key);
		}
		env = env->next;
	}
	env = head;
}

void	ft_reset(t_env *env, char *key, char *value)
{
	t_env	*head;

	if (value && value[0])
	{
		head = env;
		while (env)
		{
			if (!ft_strcmp(env->key, key))
			{
				free(env->value);
				env->value = ft_substr(value, 0, ft_strlen(value));
				env = head;
				return ;
			}
			env = env->next;
		}
		env = head;
	}
}

void	export_var(t_env *env, t_token *token)
{
	char	*key;
	char	*value;
	t_env	*new_env_var;

	key = get_key(token->str);
	value = get_value(token->str);
	if (ft_getenv(key, env))
	{
		ft_reset(env, key, value);
		free(key);
		free(value);
	}
	else
	{
		new_env_var = init_env_var(key, value);
		add_env_var(&env, new_env_var);
	}
}

int	ft_export(t_command *s_cmd, t_token *token)
{
	int		status;
	t_token	*head;

	status = 0;
	head = token;
	while (token && token->str)
	{
		if (is_non_valid(token->str))
			status = 1;
		else
			export_var(s_cmd->lst_env, token);
		token = token->next;
	}
	token = head;
	if (!token || !token->str)
		no_arg(s_cmd->lst_env);
	return (status);
}
