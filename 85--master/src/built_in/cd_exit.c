/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:34:36 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/23 06:45:12 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

/*
	echo et l’option -n
◦ cd uniquement avec un chemin relatif ou absolu
◦ pwd sans aucune option
◦ export sans aucune option
◦ unset sans aucune option
◦ env sans aucune option ni argument
◦ exit sans aucune option
*/

// SI LANCEMENT DU MINISHELL ON VIRE JUSTE AVANT LANCEMENT L'ENV
// AVEC UN UNSET, LE MINISHELL DOIT SE TROUVER OU CREER UN ENV,
// UN PWD, OU UN OLD_PWD, ET UN HOME
// POUR TENIR LA ROUTE, AINSI QUE DES PATH. Fixer avant l'env

//ECHO SEC ➜ 
//  Back_to_F git:(main) ✗ echo test | cat -e
// test$
// ➜  Back_to_F git:(main) ✗ echo -n test | cat -e
// test%                              

void	ft_exit(long long nb, int flag)
{
	g_data.exit = nb;
	if (!nb)
	{	
		printf("exit\n");
		exit(1);
	}
	else
	{
		if (flag != 1)
		{
			printf("exit\n");
			if (nb > 255)
				exit(nb % 255);
			else
				exit(nb);
		}
		else
		{
			printf("exit\n");
			printf("bash: exit: %s: numeric argument \
required\n", g_data.token->next->value);
			exit(255);
		}
	}
}

void	print_bad_addr(char *path)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putchar_fd(':', STDERR_FILENO);
	ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
	g_data.exit = 126;
}

void	main_cd(char *path, char *res)
{
	if (access(ft_strjoin(res, path), X_OK) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putchar_fd(':', STDERR_FILENO);
		ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
	}
	else if (chdir(ft_strjoin(res, path)) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putchar_fd(':', STDERR_FILENO);
		ft_putstr_fd(" No such file or directory \n", STDERR_FILENO);
	}
}

void	ft_cd(char *path)
{
	char	*res;
	char	pwd[1000];
	char	*tmp;

	tmp = NULL;
	res = search_env_content_do(g_data.env, "$PWD");
	if (ft_strcmp(res, "home") != 0 && res[0])
	{
		if (back_path(path) >= 1)
			path = cut_pwd(res, back_path(path));
	}
	if (!path || ft_strcmp(path, "$HOME") == 0)
		chdir(search_env_content_do(g_data.env, "$HOME"));
	if (access(path, F_OK) == -1)
		print_bad_addr(path);
	else if (chdir(path) == -1)
	{
		main_cd(path, res);
	}
	finish_cd(pwd, tmp, res);
}

unsigned int	starter_env(char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}
