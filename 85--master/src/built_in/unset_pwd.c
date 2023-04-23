/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:55:48 by imac21            #+#    #+#             */
/*   Updated: 2023/04/22 18:53:27 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

void	ft_pwd(int redir)
{
	char	pwd[1000];
	char	*tmp;

	tmp = getcwd(pwd, sizeof(pwd));
	if (tmp == NULL)
	{
		ft_putstr_fd(g_data.pwd, redir);
		ft_putstr_fd("/..", redir);
		ft_putchar_fd('\n', redir);
		return ;
	}
	ft_putstr_fd(tmp, redir);
	ft_putchar_fd('\n', redir);
	return ;
}

t_env	*help_delete(t_env *new_head, t_env *head)
{
	new_head = head->next;
	free(head);
	return (new_head);
}

t_env	*delete_node(t_env *head, int position)
{
	t_env	*new_head;
	t_env	*current;
	t_env	*next_node;
	int		i;

	(norm(), current = head, new_head = NULL, next_node = NULL, i = 0);
	if (head == NULL)
		return (head);
	if (position == 0)
		return (help_delete(new_head, head));
	current = head;
	while (current != NULL && i < position - 1)
	{
		current = current->next;
		i++;
	}
	if (current == NULL || current->next == NULL)
		return (head);
	next_node = current->next->next;
	free(current->next);
	current->next = next_node;
	return (head);
}

void	ft_unset(char *name)
{
	char	*path;
	t_env	*tmp;
	int		i;

	(norm(), path = NULL, tmp = g_data.env, i = 0);
	if (!name || name == NULL)
		return ;
	path = search_env_content_do(g_data.env, name);
	if (path == NULL && name == NULL)
		return ;
	if (path != NULL)
	{
		while (strcmp(tmp->name, name) != 0 && tmp)
		{
			tmp = tmp->next;
			i++;
		}
		if (strcmp(tmp->name, name) == 0)
			delete_node(g_data.env, i);
	}
}

void	true_unset(void)
{
	t_token	*stock;

	stock = g_data.token;
	if (!stock->next)
		ft_unset(NULL);
	stock = stock->next;
	while (stock)
	{
		if (stock->t_type == 3)
			ft_unset(stock->value);
		stock = stock->next;
	}
}
