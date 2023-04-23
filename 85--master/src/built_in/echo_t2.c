/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_t2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:29:03 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/23 03:34:04 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

int	ft_isquote(int c)
{
	if (c == '"' || c == 39)
		return (1);
	return (0);
}

int	ft_isequal(int c)
{
	if (c == '=')
		return (1);
	return (0);
}

int	ft_iswspace(char c)
{
	while (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

void	flag_equal_two(t_echo *echo)
{	
	echo->cmd = echo->tmp->value;
	while (echo->cmd[echo->j] == '"')
		echo->j++;
	while (echo->cmd[echo->j] != '$')
	{
		ft_putchar_fd(echo->cmd[echo->j], echo->redir);
		echo->j++;
	}
	if (echo->cmd[echo->j] == '$')
		echo->j++;
	while (echo->cmd[echo->j] >= 65 && echo->cmd[echo->j] <= 90)
		echo->j++;
}

void	stock_diff_null(t_echo *echo)
{
	ft_putstr_fd(echo->stock, echo->redir);
	while (echo->cmd[echo->j] >= 65 && echo->cmd[echo->j] <= 90)
		echo->j++;
	while (echo->cmd[echo->j] != '\0' && echo->cmd[echo->j] != '"')
		ft_putchar_fd(echo->cmd[echo->j++], echo->redir);
	echo->stop = 1;
	if (echo->tmp->next)
		echo->tmp = echo->tmp->next;
	echo->i = echo->i + 1;
}
