/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_hd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 03:53:28 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/22 03:59:39 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

int	det_nb_hd(void)
{
	t_token	*tmp;
	int		flag;

	flag = 0;
	tmp = g_data.token;
	while (tmp)
	{
		if (tmp->t_type == 9 && tmp->next->t_type == 10)
			flag++;
		tmp = tmp->next;
	}
	if (flag > 1)
		return (2);
	return (flag);
}

int	print_hd_error(t_token *tmp)
{
	if (!tmp->next)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	if (tmp->next->t_type == 0)
		printf("bash: syntax error near unexpected token `|'\n");
	if (tmp->next->t_type == 1)
		printf("bash: syntax error near unexpected token `<'\n");
	if (tmp->next->t_type == 2)
		printf("bash: syntax error near unexpecterrrd token `>'\n");
	if (tmp->next->t_type == 9)
		printf("bash: syntax error near unexpected token `<<'\n");
	return (-1);
}
