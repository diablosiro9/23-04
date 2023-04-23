/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:20:25 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/22 03:55:37 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

int	det_hd(void)
{
	t_token	*tmp;

	tmp = g_data.token;
	while (tmp)
	{
		if (tmp->t_type == 9 && (!tmp->next || tmp->next->t_type != 10))
		{
			print_hd_error(tmp);
			return (-1);
		}
		if (tmp->t_type == 9 && tmp->next->t_type == 10)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_list	*simple_hd(void)
{
	t_token	*temp;
	int		i;
	t_list	*stock;

	i = 1;
	temp = g_data.token;
	stock = NULL;
	while (temp)
	{
		stock = ft_lstnew(temp->value);
		if (temp->t_type == 10)
			stock = here_doc(temp->value, i);
		temp = temp->next;
	}
	if (stock)
		return (stock);
	return (NULL);
}

char	**fill_hd_arg(char *path, char *name)
{
	char	**res;
	t_token	*tmp;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	tmp = g_data.token;
	res = NULL;
	(void)path;
	while (tmp && (tmp->t_type == 8 || tmp->t_type == 7))
	{
		if (tmp->t_type == 7)
			flag = 1;
		i++;
		tmp = tmp->next;
	}
	res = malloc(sizeof(char *) * ((i * 2) + 1));
	if (!res || res == NULL)
		return (NULL);
	res[0] = ft_strdup(name);
	res[1] = ft_strdup("-");
	res[2] = NULL;
	return (res);
}

t_list	*here_doc(char *delim, int flag)
{
	char	*stock;
	t_list	*cmd;
	t_list	*tmp;

	(norm(), cmd = NULL, stock = NULL, tmp = NULL);
	while (42)
	{
		stock = readline(">");
		tmp = ft_lstnew(stock);
		stock = tmp->content;
		if (strcmp(stock, delim) == 0)
			return (cmd);
		ft_lstadd(&cmd, tmp);
		if (flag == -1)
		{
			if (strcmp(stock, delim) == 0)
				return (cmd);
		}
		if (flag == 0)
		{
			if (ft_strchr(stock, '"'))
				return (cmd);
		}
	}
	return (tmp);
}
