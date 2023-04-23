/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   det_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:03:06 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/22 22:56:51 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

long long	ft_atol(const char *str)
{
	int			i;
	long long	sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

int	help_sec_blt(void)
{
	if (strcmp(g_data.token->value, "cd") == 0
		|| strcmp(g_data.token->value, "/usr/bin/cd") == 0)
	{
		if (g_data.token->next)
			ft_cd(g_data.token->next->value);
		else
			ft_cd("$HOME");
		return (1);
	}
	if (strcmp(g_data.token->value, "unset") == 0)
	{
		true_unset();
		return (1);
	}
	if (strcmp(g_data.token->value, "env") == 0
		|| strcmp(g_data.token->value, "/usr/bin/env") == 0)
	{
		ft_env(NULL);
		return (1);
	}
	return (0);
}

int	help_det_blt(void)
{
	if (strcmp(g_data.token->value, "export") == 0)
	{
		ft_export(1);
		return (1);
	}
	if (strcmp(g_data.token->value, "echo") == 0
		|| strcmp(g_data.token->value, "/bin/echo") == 0)
	{
		if (g_data.token->next)
			ft_echo(1);
		else
			ft_echo(0);
		return (1);
	}
	if (help_sec_blt() == 1)
		return (1);
	return (0);
}

int	det_builtin(void)
{
	long long	res;
	int			flag;

	res = 0;
	flag = 0;
	if (strcmp(g_data.token->value, "pwd") == 0
		|| strcmp(g_data.token->value, "/bin/pwd") == 0)
	{
		ft_pwd(1);
		return (1);
	}
	if (ft_strcmp(g_data.token->value, "exit") == 0)
	{
		g_data.exit = 1;
		if (g_data.token->next)
		{
			res = ft_atol(g_data.token->next->value);
			if (ft_strlen(g_data.token->next->value) > 19)
				flag = 1;
			ft_exit(res, flag);
		}
		else
			ft_exit(0, flag);
	}
	return (help_det_blt());
}
