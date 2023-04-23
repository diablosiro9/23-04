/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:45:44 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/22 21:46:57 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

t_env	*ft_envnew(char *name, char *content, int i)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->content = content;
	new->next = NULL;
	new->num_vars = i - 1;
	return (new);
}

void	ft_envadd(t_env **lst, t_env *new)
{
	t_env	*tmp;

	tmp = NULL;
	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	if (*lst)
		tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*get_env_do(char **env)
{
	int		i;
	t_env	*list;

	i = 0;
	list = NULL;
	while (env[i])
	{
		ft_envadd(&list, ft_envnew(ft_sub(env[i], 0, \
			ft_strchr(env[i], '=') - env[i]), ft_sub(env[i], \
			starter_env(env[i]), ft_strlen(env[i]) - \
				(ft_strchr(env[i], '=') - env[i])), i));
		i++;
	}
	list->num_vars = i;
	return (list);
}
