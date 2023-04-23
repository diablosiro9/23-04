/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 07:20:19 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/22 17:57:59 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

int	det_squote(char *str)
{
	int	i;
	int	stock;
	int	res;
	int	flag;

	(norm(), i = 0, stock = 0, res = 0, flag = 0);
	while (str[i])
	{
		if (str[i] == '"' && flag == 1)
			flag = 0;
		if (str[i] == '"')
			flag = 1;
		if (str[i] == '\'' && flag != 1)
			return (1);
		i++;
	}
	return (0);
}

int	det_dquote(char *str)
{
	int	i;
	int	stock;
	int	res;
	int	flag;

	(norm(), i = 0, stock = 0, res = 0, flag = 0);
	while (str[i])
	{
		if (str[i] == '\'' && flag == 1)
			flag = 0;
		if (str[i] == '\'')
			flag = 1;
		if (str[i] == '"' && flag != 1)
			return (1);
		i++;
	}
	return (0);
}

void	case_dquote(t_token *tmp, char *stock, char *res, int start, int i, int j, int pos)
{
	char	*rest;
	
	rest = NULL;
	stock = tmp->value;
	(void)start;
	printf("stock dans dquote = %s\n", stock);
	printf("i = %d\n", i);
	while (stock[i] && stock[i] != '"')
		i++;
	if (stock[i + 1])
		i = i + 1;
	j = i;
	printf("1\n");
	while (stock[j] && stock[j] != '"')
		j++;
	printf("2\n");
	if (j == (int)ft_strlen(stock))
		res = ft_strjoin(ft_strsub(stock, 0, i - 1), ft_strsub(stock, i, j));
	else
	{
		if (j + 1 == (int)ft_strlen(stock))
			res = ft_strjoin(ft_strsub(stock, 0, i - 1), ft_strsub(stock, i, j - i));
		else
			res = ft_strjoin(ft_strsub(stock, 0, i - 1), ft_strsub(stock, i, j - 2));
	}
	if (res[ft_strlen(res) - 1] == '"')
	{
		printf("4\n");
		j = j + 1;
		if (res[ft_strlen(res) - 1] == '"')
			rest = ft_strsub(res, 0, ft_strlen(res) - 1);
		else
			rest = ft_strjoin(res, ft_strsub(stock, j, ft_strlen(stock) - j));
	}
	if (rest != NULL)
	{
		if (pos == 0)
			ft_token_addf(&g_data.token, ft_token_new(WORD, rest));
		else
			ft_token_add(&g_data.token, ft_token_new(WORD, rest));
		tmp = g_data.token;
	}
	else
	{
		if (pos == 0)
			ft_token_addf(&g_data.token, ft_token_new(WORD, res));
		else
			ft_token_add(&g_data.token, ft_token_new(WORD, res));
		tmp = g_data.token;
	}
	printf("EL POSSOOO = %d y el IIII = %d\n", pos, i);
	if (pos == 0)
		delete_token(g_data.token, pos + 1);
	else
		delete_token(g_data.token, pos);
	return ;
}

void	case_squote_term(t_token *tmp, char *stock, char *res, int start, int i, int j, int pos)
{
	char	*rest;

	rest = NULL;
	stock = tmp->value;
	(void)start;
	printf("s_Quote = %s\n", tmp->value);
	printf("i = %d\n", i);
	// i = 0;
	// j = 0;
	while (stock[i] && stock[i] != '\'')
		i++;
	if (stock[i + 1])
		i = i + 1;
	j = i;
	printf("j %d\n", j);
	while (stock[j] && stock[j] != '\'')
		j++;
	// if (j == (int)ft_strlen(stock)
	if (j == (int)ft_strlen(stock))
		res = ft_strjoin(ft_strsub(stock, 0, i - 1), ft_strsub(stock, i, j));
	else
	{
		if (j + 1 == (int)ft_strlen(stock))
			res = ft_strjoin(ft_strsub(stock, 0, i - 1), ft_strsub(stock, i, j - i));
		else
			res = ft_strjoin(ft_strsub(stock, 0, i - 1), ft_strsub(stock, i, j - 2));
	}
	if (res[ft_strlen(res) - 1] == '\'')
	{
		j = j + 1;
		if (res[ft_strlen(res) - 1] == '\'')
			rest = ft_strsub(res, 0, ft_strlen(res) - 1);
		else
			rest = ft_strjoin(res, ft_strsub(stock, j, ft_strlen(stock) - j));
	}
	if (rest != NULL)
	{
		if (pos == 0)
			ft_token_addf(&g_data.token, ft_token_new(WORD, rest));
		else
			ft_token_add(&g_data.token, ft_token_new(WORD, rest));
		tmp = g_data.token;
	}
	else
	{
		if (pos == 0)
			ft_token_addf(&g_data.token, ft_token_new(WORD, res));
		else
			ft_token_add(&g_data.token, ft_token_new(WORD, res));
		tmp = g_data.token;
	}
	if (pos == 0)
		delete_token(g_data.token, pos + 1);
	else
		delete_token(g_data.token, pos);
	return ;
}


char	*help_some_quotes(t_token *tmp, char *res, int *i)
{
	char	*stock;

	stock = tmp->value;
	while (((ft_strlen(tmp->value) == 3) || (ft_strlen(tmp->value) == 1 && tmp->t_type == 3)
		|| (stock[ft_strlen(stock) - 1] != '\'' && tmp->t_type == 4)) && tmp)
	{
		*i = *i + 1;
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
		stock = tmp->value;

	}
	res = malloc(sizeof(char) * (*i + 1));
	tmp = g_data.token;
	while (tmp && ((ft_strlen(tmp->value) != 3 && tmp->t_type != 4 && tmp->t_type != 5)
		&& (ft_strlen(tmp->value) != 1 || tmp->t_type != 3)))
		tmp = tmp->next;
	*i = 0;
	printf("tmp - > value = %s\n", tmp->value);
	while (((ft_strlen(tmp->value) == 3) || (ft_strlen(tmp->value) == 1 && tmp->t_type == 3)
		|| (stock[ft_strlen(stock) - 1] != '\'' && tmp->t_type == 4)) && tmp)
	{
		if (ft_strlen(tmp->value) == 1 && tmp->t_type == 3)
		{
			res[*i] = tmp->value[0];
			res[*i] = tmp->value[0];
		}
		else
			res[*i] = tmp->value[1];
		*i = *i + 1;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	res[*i] = '\0';
	return (res);
}

char	*help_some_dquotes(t_token *tmp, char *res, int *i)
{
	char	*stock;

	stock = tmp->value;
	while (((ft_strlen(tmp->value) == 3) || (ft_strlen(tmp->value) == 1 && tmp->t_type == 3)
		|| (stock[ft_strlen(stock) - 1] != '\'' && tmp->t_type == 4)) && tmp)
	{
		*i = *i + 1;
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
		stock = tmp->value;

	}
	res = malloc(sizeof(char) * (*i + 1));
	tmp = g_data.token;
	while (tmp && ((ft_strlen(tmp->value) != 3 && tmp->t_type != 4 && tmp->t_type != 5)
		&& (ft_strlen(tmp->value) != 1 || tmp->t_type != 3)))
		tmp = tmp->next;
	*i = 0;
	printf("tmp - > value = %s\n", tmp->value);
	while (((ft_strlen(tmp->value) == 3) || (ft_strlen(tmp->value) == 1 && tmp->t_type == 3)
		|| (stock[ft_strlen(stock) - 1] != '\'' && tmp->t_type == 4)) && tmp)
	{
		if (ft_strlen(tmp->value) == 1 && tmp->t_type == 3)
		{
			res[*i] = tmp->value[0];
			res[*i] = tmp->value[0];
		}
		else
			res[*i] = tmp->value[1];
		*i = *i + 1;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	res[*i] = '\0';
	return (res);
}

void    some_quotes(t_token *tmp, char *stock, char *res, int start, int i)
{
	char    *tricky;

	tricky = NULL;
	printf("main_case\n");
	// if (ft_strlen(tmp->value) == 3)
	// {
		if (start == 0)
			start = i;
		res = help_some_quotes(tmp, res, &i);
		printf("i = %d\n", i);
		printf("Start = %d\n", start);

//      RAJOUTER LA DESTRUCTION DES AUTRES
		if (ft_strlen(res) == 1 && res[0] == '-')
		{
			if (tmp->next)
			{
				tricky = ft_strjoin(res, tmp->next->value);
				i++;
			}
		}
		afftoken(g_data.token, "la\n");
		if (start == 0)
		{
			printf("tu te fais avoir\n");
			destroyer(start, i);
		}
		destroyer(start, i + 1);
		printf("RESSSSS = %s\n", res);
		printf("i = %d\n", start);
		i = 0;
		printf("res stp = %s\n", res);
		printf("tricky = %s\n", tricky);
		if (tricky != NULL)
		{
			printf("laaa\n");
			split_res_main(tmp, tricky, stock, i);
		}
		else
			split_res_main(tmp, res, stock, i);
	// }
	printf("finito\n");
}

void    some_dquotes(t_token *tmp, char *stock, char *res, int start, int i)
{
	char    *tricky;

	tricky = NULL;
	printf("main_case\n");
	// if (ft_strlen(tmp->value) == 3)
	// {
		if (start == 0)
			start = i;
		res = help_some_dquotes(tmp, res, &i);
		printf("i = %d\n", i);
		printf("Start = %d\n", start);

//      RAJOUTER LA DESTRUCTION DES AUTRES
		if (ft_strlen(res) == 1 && res[0] == '-')
		{
			if (tmp->next)
			{
				tricky = ft_strjoin(res, tmp->next->value);
				i++;
			}
		}
		afftoken(g_data.token, "la\n");
		if (start == 0)
		{
			printf("tu te fais avoir\n");
			destroyer(start, i);
		}
		destroyer(start, i + 1);
		printf("RESSSSS = %s\n", res);
		printf("i = %d\n", start);
		i = 0;
		printf("res stp = %s\n", res);
		printf("tricky = %s\n", tricky);
		if (tricky != NULL)
		{
			printf("laaa\n");
			split_res_main(tmp, tricky, stock, i);
		}
		else
			split_res_main(tmp, res, stock, i);
	// }
	printf("finito\n");
}