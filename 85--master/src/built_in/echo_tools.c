/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:55:29 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/23 06:05:31 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

void	loop_help_echo(t_echo *echo)
{
	char	*res;

	res = echo->tmp->value;
	while (ft_strcmp(echo->tmp->value, "-n") == 0)
	{
		if (echo->tmp->next && ft_strcmp(echo->tmp->value, "-n") == 0)
			echo->tmp = echo->tmp->next;
		else
		{
			echo->flag = 3;
			return ;
		}
		echo->flag = 3;
	}
}

void	help_echo(t_echo *echo)
{
	if (echo->tmp->value == NULL)
		return ;
	if (ft_strlen(echo->tmp->value) == 3
		&& echo->tmp->value[ft_strlen(echo->tmp->value) - 1] == ' ')
	{
		if (echo->tmp->next)
		{
			printf("lui\n");
			echo->tmp = echo->tmp->next;
		}
		else
		{
			printf("laaa\n");
			echo->flag = 2;
			return ;
		}
		echo->flag = -1;
	}
	if (ft_strlen(echo->tmp->value) > 3)
		return ;
	printf("ok\n");
	loop_help_echo(echo);
}

int	cases_dollar(t_token **tmp, char *stock, char *test, int i)
{
	stock = (*tmp)->value;
	if (stock[1] == '$')
	{
		test = search_env_content_do(g_data.env, &stock[2]);
		if (test == NULL)
			return (0);
		return (1);
	}
	if (stock[i] == '"')
	{
		while (stock[i] == '"')
			i++;
		test = search_env_content_do(g_data.env, &stock[i]);
		if (test == NULL)
			return (0);
		return (1);
	}
	return (0);
}

int	echo_dollar(t_token **tmp)
{
	char	*stock;
	char	*test;
	int		i;

	(norm(), stock = NULL, test = NULL, i = 0);
	if ((*tmp)->t_type == 4)
		return (cases_dollar(tmp, stock, test, i));
	return (0);
}
