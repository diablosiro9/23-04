/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_t3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:35:44 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/23 04:05:29 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

int	skip(char **new_env, size_t *i, t_token **tmp, char *cmd)
{
	while (ft_iswspace(cmd[*i]))
		*i += 1;
	if (*i == ft_strlen(g_data.cmd))
		return (-1);
	if (cmd[*i] && ft_isquote(cmd[*i]) == 1)
		*i += 2;
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	*new_env = ft_strdup((*tmp)->value);
	*i += ft_strlen(*new_env);
	return (0);
}

int	env_exist(char *name)
{
	t_env	*tmp;

	tmp = g_data.export;
	if (ft_isalpha(name[0]) != 1)
		return (0);
	while (tmp)
	{
		if (check_str(name, tmp->name) == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*reverse_chr(char *s, char c)
{
	int		i;
	char	*res;

	(norm(), i = 0, res = NULL);
	while (s[i] && s[i] != c)
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	help_export(t_export *export)
{
	if (export->redir == -1)
		export->redir = 1;
	while (export->i < ft_strlen("export"))
		export->i += 1;
	if (!export->tmp->next)
	{
		print_export(g_data.export, 1);
		return (0);
	}
	return (1);
}

void	unset_assist(char *name)
{
	t_env	*env;
	t_env	*start;

	start = g_data.env;
	env = g_data.env;
	if (!name)
		return ;
	while (env)
	{
		if (check_str(name, env->name) == 1)
		{
			free(env->content);
			env->content = NULL;
			break ;
		}
		env = env->next;
	}
	g_data.env = start;
}
