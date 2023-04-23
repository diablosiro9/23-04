/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 03:19:24 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/23 07:29:18 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

int	others_if(t_echo *echo, int f_round)
{
	if (echo->tmp->t_type == 5)
	{
		if (case_squote(echo) == 1)
			return (1);
	}
	else if (echo->tmp->t_type == 7)
	{
		if (case_option(echo, f_round) == 1)
			return (1);
	}
	else if (echo->tmp->t_type == 3
		&& echo->tmp->t_type != 4 && echo->tmp->t_type != 5)
	{
		if (case_string(echo->cmd, &echo->tmp, &echo->i, echo->redir) == 1)
			return (1);
	}
	else if ((echo->tmp->t_type == 8 || echo->tmp->t_type == 6)
		&& echo->tmp->t_type != 4 && echo->tmp->t_type != 5)
	{
		if (case_string(echo->cmd, &echo->tmp, &echo->i, echo->redir) == 1)
			return (1);
	}
	return (0);
}

int	loop_main_echo(t_echo *echo, int f_round)
{
	while (echo->tmp)
	{
		if (f_round != 0)
			ft_putchar_fd(' ', echo->redir);
		if (ft_strcmp(echo->tmp->value, "$?") == 0)
		{
			ft_putstr_fd(ft_itoa(g_data.exit), echo->redir);
			if (echo->tmp->next)
				echo->tmp = echo->tmp->next;
			else
				return (1);
		}
		if (echo->tmp->t_type == 4)
		{
			if (case_quote(echo) == 1)
				return (1);
		}
		else
		{
			if (others_if(echo, f_round) == 1)
				return (1);
		}
		f_round++;
	}
	return (0);
}

int	main_echo(t_echo *echo)
{
	int	f_round;

	f_round = 0;
	if (echo->flag == -1)
		echo->tmp = echo->tmp->next;
	return (loop_main_echo(echo, f_round));
}

void	init_echo(t_echo *echo, int redir)
{
	(norm(), echo->redir = redir, echo->i = 0, \
		echo->tmp = g_data.token, echo->cmd = g_data.cmd, \
			echo->flag = 1);
}

int	ft_echo(int redir)
{
	t_echo		*echo;

	echo = (t_echo *)malloc(sizeof(t_echo) * 1);
	if (!echo)
		return (0);
	init_echo(echo, redir);
	if (echo->redir == -1)
		echo->redir = 1;
	while (echo->i < ft_strlen("echo"))
		echo->i += 1;
	if (echo->tmp->next)
		echo->tmp = echo->tmp->next;
	else
	{
		echo->flag = 1;
		ft_putchar_fd('\n', echo->redir);
		return (1);
	}
	help_echo(echo);
	if (echo->flag == 2)
		return (1);
	main_echo(echo);
	if (echo->flag != 3)
		ft_putchar_fd('\n', echo->redir);
	return (1);
}
