/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:32:08 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/23 07:29:28 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

void	print_for_alpha(t_env *tmp, int fd)
{
	char	*res;

	res = NULL;
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(tmp->name, fd);
	if (tmp->content)
	{
		res = tmp->content;
		ft_putstr_fd("=", fd);
		ft_putchar_fd('"', fd);
		if (res[1] == '\'')
			ft_putstr_fd(ft_substr(res, 2, \
				ft_strlen(res) - 3), fd);
		else
			ft_putstr_fd(&tmp->content[1], fd);
		ft_putchar_fd('"', fd);
	}
	ft_putchar_fd('\n', fd);
}

void	finish_alpha(t_env *env, char *s1, char *s2, int fd)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (s2[i])
	{
		tmp = env;
		while (tmp)
		{
			if (tmp->name[0] == s2[i] && tmp->name[0] != s1[i])
				print_for_alpha(tmp, fd);
			tmp = tmp->next;
		}
		i++;
	}
}
