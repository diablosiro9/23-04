/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:04:10 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/23 07:27:29 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

/*
    Mimi
    Déplacement de la fonction lexer dans le dossier/.c dédié ./src/lexer/lexer.c
    simplement par claireté et norme

*/

t_token	*recuperator(void)
{
	t_token	*tmp;

	tmp = g_data.token;
	while (tmp)
	{
		if (tmp->t_type == 9)
		{
			if (tmp->next && tmp->next->t_type == 3)
				tmp->next->t_type = 10;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_token	*modificator(void)
{
	t_token	*tmp;

	tmp = g_data.token;
	while (tmp)
	{
		if (tmp->t_type == 9)
		{
			if (tmp->next)
			{
				if (tmp->next->t_type != 0 && tmp->next->t_type != 1
					&& tmp->next->t_type != 2 && tmp->next->t_type != 9)
					tmp->next->t_type = 10;
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	destroyer(int start, int i)
{
	t_token *tmp;
	int		compare;

	tmp = g_data.token;
	compare = 0;
	while (compare < i)
	{
		if (compare >= start && compare < i)	
		{
			tmp = delete_token(tmp, compare);
			compare = compare - 1;
			i = i - 1;
			start = start - 1;
		}
		compare++;
	}
	g_data.token = tmp;
}

int	other_term(t_token *tmp, char *stock, char *res, int start, int i, int j, int pos)
{
	if (det_squote(tmp->value) == 1 || det_dquote(tmp->value) == 1)
	{
		if (det_dquote(tmp->value) == 1)
			case_dquote(tmp, stock, res, start, i, j, pos);
		else if (det_squote(tmp->value) == 1)
			case_squote_term(tmp, stock, res, start, i, j, pos);
		return (1);
	}
	if (!tmp->next)
		return (0);
	else
	{
		printf("la\n");
		tmp = tmp->next;
		pos++;
		return (2);
	}
}

void	split_res_main( t_token *tmp, char *res, char *stock, int i)
{
	(void)tmp;
	printf("res = |%s|\n", res);
	if (res[0] == '-')
	{
		printf("yeepp\n");
		ft_token_add(&g_data.token, ft_token_new(OPTION, res));
		afftoken(g_data.token, "lui");
	}
	else
	{
		while (res[i] != '-' && res[i])
			i++;
		if (i != (int)ft_strlen(res))
		{
			printf("on a det un truc\n");
			stock = ft_strsub(res, 0, i);
			printf("stock = %s\n", stock);
			ft_token_addf(&g_data.token, ft_token_new(WORD, stock));
			stock = ft_strsub(res, i, ft_strlen(res) - 1);
			printf("stock = %s\n", stock);
			ft_token_add(&g_data.token, ft_token_new(WORD, stock));
		}
		else
		{
			printf("WSSSHH\n");
			ft_token_addf(&g_data.token, ft_token_new(WORD, res));
			printf("Sprs\n");
		}
	}
	return ;
}

int	size_token(t_token *tmp)
{
	int		i;
	t_token	*stock;

	i = 0;
	stock = tmp;
	while (stock && stock->value)
	{
		i++;
		stock = stock->next;
	}
	return (i);
}

t_token	*terminator(void)
{
	t_token	*tmp;
	char	*res;
	char	*stock;
	char	*save;
	int		i;
	int		start;
	int		j;
	int		pos;
	int		data;
	int		flag;

	data = 0;
	j = 0;
	i = 0;
	pos = 0;
	start = 0;
	flag = 0;
	stock = NULL;
	tmp = g_data.token;
	res = NULL;
	printf("g_data.token = %s\n", g_data.token->value);
	if (g_data.token->next)
	{
		save = g_data.token->next->value;
		flag = 1;
	}
	while (tmp && pos <= size_token(tmp))
	{
		if (flag == 1)
		{
			if (pos != 1 && ft_strcmp(save, tmp->value) == 0)
				break ;
		}
		if (tmp->value == NULL)
			break ;
		printf("DET_QUOTTe(tmp) = %d\n", det_squote(tmp->value));
		printf("pos %d, et i = %d\n", pos, i);
		printf("t_type = %d\n", tmp->t_type);
		printf("tmp->value = %s\n", tmp->value);
		stock = tmp->value;
		if (tmp->t_type != 4 && tmp->t_type != 5)
		{
			printf("entre\n");
			printf("tmp->value - %s\n", tmp->value);
			data = other_term(tmp, stock, res, start, i, j, pos);
			if (data == 0)
				break ;
			else if (data != 2)
				tmp = g_data.token;
			// i = i - 1;
		}
		else if (tmp->t_type == 4 || tmp->t_type == 5)
		{

			printf("tmp->t_typr = %s\n", tmp->value);
			printf("ft_strlen(tmp->value) = %zu\n", ft_strlen(tmp->value));
			if (stock[0] == '\'' && stock[ft_strlen(stock) - 1] == '\''
				&& ft_strlen(stock) <= 3)
				some_quotes(tmp, stock, res, start, i);
			else if (stock[0] == '"' && stock[ft_strlen(stock) - 1] == '"'
				&& ft_strlen(stock) <= 3)
				some_dquotes(tmp, stock, res, start, i);
			else
			{
				if (tmp->next)
					tmp = tmp->next;
				else
					return (g_data.token);
			}
			// if (data == 0)
			// 	break ;
			// else if (data != 2)
			tmp = g_data.token;
			// i = i - 1;
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			return (g_data.token);
		pos++;
		i++;
	}
	return (g_data.token);
}

t_token	*reunificator()
{
	t_token	*tmp;
	char	*stock = NULL;
	int		i;
	int		start;
	char	*res;

	res = NULL;
	i = 0;
	start = 0;
	tmp = g_data.token;
	while (tmp)
	{
		stock = tmp->value;
		if (ft_strlen(stock) == 1 && tmp->value[0] == '-')
		{
			tmp = tmp->next;
			stock = tmp->value;
			while (stock[i])
				i++;
			res = malloc(sizeof(char) * i + 2);
			i = 0;
			res[0] = '-';
			while (stock[i])
			{
				res[i + 1] = stock[i];
				i++;
			}
			res[i + 1] = '\0';
			tmp = g_data.token;
			while (tmp)
			{
				if (ft_strlen(tmp->value) == 1 && tmp->value[0] == '-')
				{	
					destroyer(start, i + 1);
					tmp = g_data.token;
				}
				if (!tmp && !tmp->next)
					break;
				tmp = tmp->next;
				i++;
			}
			ft_token_add(&g_data.token, ft_token_new(OPTION, res));
		}
		if (!tmp || !tmp->next || tmp->next == NULL)
			break ;
		tmp = tmp->next;
		start++;
	}
	return (g_data.token);
}

void	ft_tab_delete(char **tab)
{
	// char	*tmp;
	int		i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}


t_list	*ft_lexer(char *str)
{
	int		i;
	t_list	*list;
	char	**tab;

	i = 0;
	list = NULL;
	printf("al\n");
	tab = ft_split(str);
	printf("al\n");

	printf("tab[0] = %s\n", tab[0]);
	if (!tab || tab[0] == NULL)
	{
		// printf("Error : malloc failed() in ft_lexer.\na");
		return (NULL);
	}
	while (tab[i])
	{
		ft_lstadd(&list, ft_lstnew(tab[i]));
		i++;
	}
	afflist(list, "lexer");
	tokenizateur(list);
	recuperator();
	modificator();
	afflist(list, "lexer");
	if (terminator() == NULL)
		return (NULL);
	// if (reunificator() == NULL)
	// 	return (NULL);
	free(tab);
	printf("fin lexer\n");
	afftoken(g_data.token, "fin kexer");
	return (list);
}
