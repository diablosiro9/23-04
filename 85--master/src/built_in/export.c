/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:15:59 by imac21            #+#    #+#             */
/*   Updated: 2023/04/23 04:10:49 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

void	change_env(char *new_env, char *content)
{
	if (env_exist(new_env) == 0)
		ft_lstadd_back_env(&g_data.env,
			ft_lstnew_env(ft_strdup(new_env), ft_strdup(content)));
	else if (ft_same_content(new_env, content) != 1)
		cmd_unset_assist(new_env, content);
	if (new_env)
		free(new_env);
	if (content)
		free(content);
}

int	create_env(char *new_env, char *stock)
{
	if (ft_isalpha(new_env[0]) == 0)
		return (0);
	if (stock != NULL)
	{
		if (ft_lstadd_back_env(&g_data.env, \
			ft_lstnew_env((reverse_chr(new_env, '=')), stock)) == 0)
			ft_lstadd_back_env(&g_data.env, ft_lstnew_env(new_env, " "));
		if (treat_last_part(ft_strrchr(new_env, '=')) != NULL)
			g_data.env->num_vars++;
	}
	else
	{
		if (ft_lstadd_back_env(&g_data.env, \
			ft_lstnew_env((reverse_chr(new_env, '=')), \
				treat_last_part(ft_strrchr(new_env, '=')))) == 0)
			ft_lstadd_back_env(&g_data.env, ft_lstnew_env(new_env, " "));
		if (treat_last_part(ft_strrchr(new_env, '=')) != NULL)
			g_data.env->num_vars++;
	}
	g_data.export->num_vars = g_data.env->num_vars + 1;
	g_data.export = g_data.env;
	return (1);
}

int	loop_mexport(t_token *tmp, char *new_env, char *stock, int flag)
{
	while (tmp)
	{
		if (export_norm(tmp, new_env, &stock, flag) == 0)
			return (0);
		if (env_exist(reverse_chr(new_env, '=')) == 0)
		{
			if (create_env(new_env, stock) == 0)
				break ;
		}
		else
		{
			if (stock != NULL)
				cmd_unset_assist(reverse_chr(new_env, '='), stock);
			else
				cmd_unset_assist(reverse_chr(new_env, '='), \
					ft_strrchr(new_env, '='));
		}
		if (!tmp->next)
			return (1);
		tmp = tmp->next;
		new_env = ft_strdup(tmp->value);
	}
	return (1);
}

int	main_export(char *new_env, t_token *tmp, size_t i)
{
	int		z;
	int		flag;
	char	*stock;

	(norm(), z = 0, flag = 0, stock = NULL);
	printf("main_export\n");
	while (tmp)
	{
		if (z == 1)
			return (1);
		if (skip(&new_env, &i, &tmp, g_data.cmd) == -1)
			return (1);
		if (tmp && tmp->value[0] == 0)
		{
			while (g_data.cmd[i] && ft_iswspace(g_data.cmd[i]) != 1)
			i += 1;
			if (tmp->next)
				tmp = tmp->next;
		}
		if (loop_mexport(tmp, new_env, stock, flag) == 0)
			return (0);
		z++;
	}
	return (1);
}

int	ft_export(int redir)
{
	t_export	*export;
	char		*new_env;

	export = (t_export *)malloc(sizeof(t_export) * 1);
	new_env = NULL;
	export->i = 0;
	export->tmp = g_data.token;
	export->redir = redir;
	if (help_export(export) == 0)
		return (0);
	if (main_export(new_env, export->tmp, export->i) == 1)
		return (1);
	return (1);
}
