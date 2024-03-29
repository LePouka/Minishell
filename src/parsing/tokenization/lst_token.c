/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:39:37 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/23 23:31:44 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//return the last cmd in the list
t_simple_cmd	*cmd_last(t_simple_cmd *lst)
{
	t_simple_cmd	*aux;

	if (lst == NULL)
		return (lst);
	aux = lst;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

//return the last env variable
t_env	*env_last(t_env *lst)
{
	t_env	*aux;

	if (lst == NULL)
		return (lst);
	aux = lst;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

//add token to the back of the list
void	add_token(t_token **lst, t_token *new_token)
{
	t_token	*tmp;

	if (new_token == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_token;
		return ;
	}
	tmp = token_last(*lst);
	tmp->next = new_token;
	new_token->prev = tmp;
}

//add cmd to the back of the list
void	add_simple_cmd(t_simple_cmd **lst, t_simple_cmd *new_cmd)
{
	t_simple_cmd	*tmp;

	if (new_cmd == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_cmd;
		return ;
	}
	tmp = cmd_last(*lst);
	tmp->next = new_cmd;
	new_cmd->prev = tmp;
}

//add env_var to the back of the list
void	add_env_var(t_env **lst, t_env *new_env)
{
	t_env	*tmp;

	if (new_env == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_env;
		return ;
	}
	tmp = env_last(*lst);
	tmp->next = new_env;
	new_env->prev = tmp;
}
