/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:43:09 by rtissera          #+#    #+#             */
/*   Updated: 2023/11/22 19:06:18 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Ne pas oublier de tout free
 */
int	ft_exit(char *strn, t_env *env)
{
	int	i;

	clear_env(env);
	if (strn && strn[0])
	{
		i = 0;
		while (strn[i])
		{
			if (!ft_isdigit(strn[i]))
				exit(2);
			i++;
		}
		errno = ft_atoi(strn);
		exit(errno);
	}
	else
		exit(0);
}
