/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:00:53 by imac21            #+#    #+#             */
/*   Updated: 2023/04/22 21:46:13 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

char	*ft_sub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	loop_env(t_env *tmp, char *copy)
{
	while (tmp != NULL)
	{
		copy = tmp->content;
		if (copy != NULL)
		{
			if (copy[0] == '=' && copy[1] == '\0')
			{
				if (tmp->next)
					tmp = tmp->next;
			}
			else
				printf("%s%s\n", tmp->name, tmp->content);
		}
		tmp = tmp->next;
	}
}

// trouver le moyen de passer plusieurs para, tant quon trouve pas pipe
void	ft_env(char	*s)
{
	t_env	*tmp;
	char	*copy;
	int		flag;
	t_token	*tmp_token;

	(norm(), tmp = g_data.env, copy = s, flag = -1, tmp_token = g_data.token);
	if (tmp == NULL)
		return ;
	if (s == NULL)
		loop_env(tmp, copy);
	else
		printf("env: %s: No such file or directory\n", s);
}

/*
void	init_data_env(char **env)
{
	int		i;
	char	**tableau;

	i = 0;
	tableau = ft_split(env[i++], '=');
	g_data.env = ft_lstnew_env(ft_strdup(tableau[0]), ft_strdup(tableau[1]));
	free_tab(tableau);
	while (env[i])
	
		tableau = ft_split(env[i], '=');
		ft_lstadd_back_env(&g_data.env, ft_lstnew_env(ft_strdup(tableau[0]),
				ft_strdup(tableau[1])));
		free_tab(tableau);
		i++;
	}
}*/