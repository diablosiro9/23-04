/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:56:21 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/23 03:31:01 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

int	case_quote(t_echo *echo)
{
	(norm(), echo->stock = NULL, echo->flag = 0, echo->stop = 0, \
		echo->j = 0, echo->delim = ft_strlen(echo->tmp->value) - 1);
	if (echo->tmp->t_type == 4 || echo->tmp->t_type == 5)
		main_case_quote(echo);
	if (echo->tmp->next)
		echo->tmp = echo->tmp->next;
	else
		return (1);
	return (0);
}

void	main_case_squote(t_echo *echo)
{
	echo->stock = echo->tmp->value;
	if (echo->tmp->t_type == 5)
	{
		while (echo->delim > 0 && echo->stock[echo->delim] == '\'')
			echo->delim--;
		if (echo->stock[echo->delim + 1] == '\'')
			echo->delim--;
		echo->stock = ft_strsub(echo->stock, 1, echo->delim + 1);
	}
	echo->j = 0;
	if (echo->stock != NULL)
	{
		ft_putstr_fd(echo->stock, echo->redir);
		echo->stop = 1;
		echo->i = echo->i + 1;
	}
}

int	case_squote(t_echo *echo)
{
	(norm(), echo->stock = NULL, echo->stop = 0, echo->j = 0, \
		echo->delim = ft_strlen(echo->tmp->value) - 1);
	if (echo->tmp->t_type == 5)
		main_case_squote(echo);
	if (echo->tmp->next)
		echo->tmp = echo->tmp->next;
	else
		return (1);
	return (0);
}

int	case_option(t_echo *echo, int f_round)
{
	int		idx;

	idx = 0;
	echo->stock = echo->tmp->value;
	if (ft_strlen(echo->stock) >= 2)
	{
		if (f_round == 0)
		{
			if (echo->stock[idx] == '-')
				idx++;
			while (echo->stock[idx])
			{
				if (echo->stock[idx] != 'n')
				{
					ft_putstr_fd(echo->tmp->value, echo->redir);
				}
				else if (echo->stock[idx] == '\0')
					echo->flag = 3;
				idx++;
			}
		}
		else
			ft_putstr_fd(echo->tmp->value, echo->redir);
	}
	return (1);
}

int	case_string(char *cmd, t_token **tmp, size_t *i, int redir)
{
	int	idx;

	idx = 0;
	while ((*tmp)->value[idx] && ft_iswspace((*tmp)->value[idx]) != 1)
		ft_putchar_fd((*tmp)->value[idx++], redir);
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	else
		return (1);
	while (cmd[*i] && ft_isquote(cmd[*i]) != 1 && ft_iswspace(cmd[*i]) != 1
		&& ft_isprint(cmd[*i]) > 1 && cmd[*i] != '=')
		*i += 1;
	if (cmd[*i] == '=')
		*i += 1;
	return (0);
}
