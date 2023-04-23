/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_t3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 01:59:46 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/23 03:34:52 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

void	flag_diff_two(t_token **tmp, char *stock, int flag)
{
	stock = &(*tmp)->value[1];
	flag = ft_strlen((*tmp)->value);
	while (flag != 0 && (stock[flag - 1] != '\''
			&& stock[flag - 1] != '"'))
		flag--;
	if (flag == (int)ft_strlen((*tmp)->value))
		stock[flag] = '\0';
	stock[flag - 1] = '\0';
}

void	help_dq(t_echo *echo)
{
	while (echo->delim > 0 && (echo->stock[echo->delim] == '\''
			|| echo->stock[echo->delim] == '"'))
		echo->delim--;
	if (echo->stock[echo->delim + 1] == '\'')
		echo->delim--;
	while (echo->stock[echo->j])
	{
		if (echo->stock[echo->j] == '$')
		{
			echo->stock = search_env_content_do(g_data.env, \
				ft_substr(echo->stock, echo->j, echo->delim));
			if (echo->stock == NULL)
				break ;
		}
		echo->j++;
	}
}

void	main_case_quote(t_echo *echo)
{
	echo->stock = echo->tmp->value;
	if (echo->tmp->t_type == 4)
		help_dq(echo);
	echo->j = 0;
	if (echo->flag != 2)
		flag_diff_two(&echo->tmp, echo->stock, echo->flag);
	if (echo->flag == 2)
		flag_equal_two(echo);
	if (echo->stock != NULL)
	{
		ft_putstr_fd(echo->stock, echo->redir);
		echo->stop = 1;
		echo->i = echo->i + 1;
	}
}
