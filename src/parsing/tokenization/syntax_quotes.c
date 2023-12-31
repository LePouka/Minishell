/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:01:05 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/28 20:40:06 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/include/libft.h"
#include "lexer.h"

/*int	check_double(t_command *cmd_struct, char *word, int i)
{
	int	quotes_open;

	while (word[i])
	{
		if (word[i] == '"')
		{
			quotes_open = 1;
			i++;
		}
		while (word[i] && word[i] != '"')
			i++;
		if (word[i] == '"')
		{
			quotes_open = 0;
			i++;
		}
	}
	i++;
	if (quotes_open == 0)
	{
		while (word[i - 1] != '"')
			i--;
		return (i);
	}
	else
	{
		printf("Double quotes not closed\n");
		free_cmd(cmd_struct);
		exit(EXIT_FAILURE);
	}
}

int	check_single(t_command *cmd_struct, char *word, int i)
{
	int	quotes_open;

	while (word[i])
	{
		if (word[i] == '\'')
		{
			quotes_open = 1;
			i++;
		}
		while (word[i] && word[i] != '\'')
			i++;
		if (word[i] == '\'')
		{
			quotes_open = 0;
			i++;
		}
	}
	i++;
	if (quotes_open == 0)
	{
		while (word[i - 1] != '\'')
			i--;
		return (i);
	}
	else
	{
		printf("Single quotes not closed\n");
		free_cmd(cmd_struct);
		exit(EXIT_FAILURE);
	}
}*/

int	change_flag(int flag)
{
	if (flag == 0)
		return (1);
	if (flag == 1)
		return (0);
	return (0);
}

int	check_single(t_command *cmd_struct, char *word, int i)
{
	int	flag;
	
	flag = 0;
	while (word[i])
	{
		if (word[i] == '\'')
			flag = change_flag(flag);
		i++;
	}
	if (flag == 0)
	{
		while (word[i - 1] != '\'')
			i--;
		return (i);
	}
	else
	{
		printf("Single quotes not closed\n");
		free_cmd(cmd_struct);
		exit(EXIT_FAILURE);
	}
}

int	check_double(t_command *cmd_struct, char *word, int i)
{
	int	flag;
	
	flag = 0;
	while (word[i])
	{
		if (word[i] == '"')
			flag = change_flag(flag);
		i++;
	}
	if (flag == 0)
	{
		while (word[i - 1] != '"')
			i--;
		return (i);
	}
	else
	{
		printf("Double quotes not closed\n");
		free_cmd(cmd_struct);
		exit(EXIT_FAILURE);
	}
}


void	check_if_all_quotes_closed(t_command *cmd_struct, char *word)
{
	int	i;
	//int	len;
	i = 0;
	//len = ft_strlen(word);
	while (word[i])
	{
		while (word[i] && word[i] != '"' && word[i] != '\'')
			i++;
		if (word[i] == '"')
			i = check_double(cmd_struct, word, i);
		if (word[i] == '\'')
			i = check_single(cmd_struct, word, i);
	}
}

int	check_quotes(t_command *cmd_struct)
{
	t_token	*token;

	token = cmd_struct->first_token;
	while (token)
	{
		if (token->type == ARGUMENT)
		{
			check_if_all_quotes_closed(cmd_struct, token->str);
		}
		token = token->next;
	}
	return (1);
}
