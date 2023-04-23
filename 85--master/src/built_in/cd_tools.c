/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 23:06:35 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/23 02:14:07 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

void	change_env_content(char *name, char *new)
{
	t_env	*tmp;

	tmp = g_data.env;
	while (tmp)
	{
		if (strcmp(tmp->name, name) == 0)
			tmp->content = ft_strdup(new);
		tmp = tmp->next;
	}
}

int	back_path(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	if (str[0] == '.' && str[1] == '.' && str[2] == '\0')
		return (1);
	if (ft_strlen(str) > 2)
	{
		while (str[i - 1] == '.' && str[i - 2] == '.'
			&& (str[i - 3] == '/' || str[i - 3] == ' '))
		{
			if (str[i] == ' ')
				j++;
			i--;
		}
		return (j);
	}
	return (0);
}

char	*res_cut(char *tmp, char *str, int i, int stock)
{
	if (str[0] != '/')
	{
		tmp = malloc(sizeof(char) * (i + 2));
		tmp[0] = '/';
		stock = 1;
		while (stock < i + 1)
		{
			tmp[stock] = str[stock - 1];
			stock++;
		}
		tmp[stock] = '\0';
	}
	else
	{
		tmp = malloc(sizeof(char) * i + 1);
		while (stock < i)
		{
			tmp[stock] = str[stock];
			stock++;
		}
		tmp[stock] = '\0';
	}
	return (tmp);
}

char	*cut_pwd(char *str, int n_back)
{
	int		i;
	int		stock;
	char	*tmp;

	(void)n_back;
	(norm(), i = 0, stock = 0, tmp = NULL);
	while (str[i])
		i++;
	while (str[i] != '/')
		i--;
	return (res_cut(tmp, str, i, stock));
}

void	finish_cd(char *pwd, char *tmp, char *res)
{
	tmp = getcwd(pwd, sizeof(pwd));
	if (tmp == NULL)
		return ;
	change_env_content("PWD", tmp);
	res = search_env_content_do(g_data.env, "$PWD");
	g_data.pwd = res;
}
