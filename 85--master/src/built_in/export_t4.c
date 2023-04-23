/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_t4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:21:16 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/23 00:51:18 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

void	loop_unset_assist(t_env *env, char *name, char *content, int flag)
{
	while (env)
	{
		if (check_str(name, env->name) == 1)
		{
			if (env->content == NULL)
				flag = 1;
			env->content = NULL;
			if (content != NULL)
				env->content = ft_strdup(content);
			else
			{
				if (flag != 1)
					env->content = ft_strdup("""");
			}
			break ;
		}
		env = env->next;
	}
}

void	cmd_unset_assist(char *name, char *content)
{
	t_env	*env;
	t_env	*start;
	int		flag;

	(norm(), flag = 0, start = g_data.env, env = g_data.env);
	if (!name)
		return ;
	loop_unset_assist(env, name, content, flag);
	g_data.env = start;
}

char	*treat_last_part(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	if (str == NULL)
		return (str);
	if (ft_strlen(str) == 1)
		return (str);
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i + 1] == '"' && str[ft_strlen(str) - 1] == '"')
			{
				res = ft_substr(str, i + 1, ft_strlen(str) - 2);
				return (res);
			}
		}
		i++;
	}
	return (str);
}

void	stock_nonull(char **stock)
{
	if (stock == NULL || *stock == NULL)
	{
		return ;
	}
	if (ft_strlen(*stock) >= 2)
	{
		if (stock[0][2] && stock[0][1] == '$')
			*stock = search_env_content_do(g_data.env, &stock[0][1]);
		if (*stock != NULL)
		{
			if (stock[0][0] != '=')
				*stock = ft_strjoin("=", *stock);
		}
		else
			*stock = ft_strdup("");
	}
}

int	export_norm(t_token *tmp, char *new_env, char **stock, int flag)
{
	if (tmp->value[0] == '=')
		return (0);
	if (tmp->t_type == 4 || tmp->t_type == 5)
	{
		new_env = &tmp->value[1];
		flag = ft_strlen(tmp->value);
		while (flag != 0 && (new_env[flag - 1] != '\''
				&& new_env[flag - 1] != '"'))
			flag--;
		if (flag == (int)ft_strlen(tmp->value))
			new_env[flag] = '\0';
		new_env[flag - 1] = '\0';
	}
	*stock = treat_last_part(ft_strrchr(new_env, '='));
	if (stock != NULL)
		stock_nonull(stock);
	return (1);
}
