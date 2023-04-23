/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:58:59 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/23 06:19:03 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

void	alpha_export_bis(t_env *env, int fd)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_isalpha(tmp->name[0]) == 0)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(tmp->name, fd);
			printf("FOUUU\n");
			if (tmp->content)
			{
				ft_putstr_fd("=", fd);
				ft_putchar_fd('"', fd);
				if (tmp->content[0] != '=' && tmp->content[0] != '\'')
					ft_putstr_fd(&tmp->content[0], fd);
				else
					ft_putstr_fd(&tmp->content[1], fd);
				ft_putchar_fd('"', fd);
			}
			ft_putchar_fd('\n', fd);
		}	
		tmp = tmp->next;
	}
}

void	alpha_third(t_env *tmp, char *s2, char *s1, int fd)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		while (tmp)
		{
			if (tmp->name[0] == s2[i] && tmp->name[0] != s1[i])
			{
				ft_putstr_fd("declare -x ", fd);
				ft_putstr_fd(tmp->name, fd);
				if (tmp->content)
				{
					ft_putstr_fd("=", fd);
					ft_putchar_fd('"', fd);
					ft_putstr_fd(&tmp->content[1], fd);
					ft_putchar_fd('"', fd);
				}
				ft_putchar_fd('\n', fd);
			}
			tmp = tmp->next;
		}
		i++;
	}
}

void	write_fct(t_env *tmp, t_alpha *alpha)
{
	while (tmp)
	{
		if (ft_isalpha((int)tmp->name[0]) == 0)
			alpha->flag = 1;
		if (tmp->name[0] == alpha->s1[alpha->i])
		{
			ft_putstr_fd("declare -x ", alpha->fd);
			ft_putstr_fd(tmp->name, alpha->fd);
			if (tmp->content)
			{
				ft_putstr_fd("=", alpha->fd);
				ft_putchar_fd('"', alpha->fd);
				if (tmp->content[0] == '=')
					ft_putstr_fd(&tmp->content[1], alpha->fd);
				else
					ft_putstr_fd(&tmp->content[0], alpha->fd);
				ft_putchar_fd('"', alpha->fd);
			}
			ft_putchar_fd('\n', alpha->fd);
		}
		tmp = tmp->next;
	}
	alpha->i = alpha->i + 1;
}

void	alpha_export(t_env *env, int fd)
{
	t_alpha	*alpha;
	char	*s1;
	char	*s2;
	t_env	*tmp;

	s1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	s2 = "abcdefghijklmnopqrstuvwxyz";
	alpha = (t_alpha *)malloc(sizeof(t_alpha) * 1);
	(norm(), alpha->s1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", \
		alpha->s2 = "abcdefghijklmnopqrstuvwxyz", alpha->i = 0, \
		alpha->fd = fd, tmp = env, alpha->flag = 0);
	if (!env)
		return ;
	while (alpha->s1[alpha->i])
	{
		tmp = env;
		write_fct(tmp, alpha);
	}
	if (alpha->flag == 1)
		alpha_export_bis(env, fd);
	finish_alpha(env, s1, s2, fd);
}

void	print_export(t_env *env, int fd)
{
	t_env	*tmp;

	tmp = env;
	alpha_export(tmp, fd);
}
