# include "../../include/include.h"


void	ft_print(t_token *token)
{
	t_token *tmp2 = token;
	
	printf("---------- TOKEN CMD = ");
	while (tmp2) {
		printf("%s ", tmp2->value);
		tmp2 = tmp2->next;
	}
	printf("\n");
}

// CMD = cat new/85--master/Makefile | wc -l > a
// -> Creates a 'a' file with the number of lines in the Makefile
// SPLIT = cat new/85--master/Makefile
// SPLIT = wc -l > a

// CMD = cat < a | wc -l
// -> Prints the number of lines in the 'a' file (created above)
// SPLIT = cat < a
// SPLIT = wc -l

// CMD = cat < a | wc -l > b
// -> Creates a 'b' file with the number of lines in the 'a' file
// SPLIT = cat < a
// SPLIT = wc -l > b

// CMD = cat < a | wc -l > b | cat < b
// -> Prints the number of lines in the 'a' file from 'b' file (created above)
//    as same file descriptor
// SPLIT = cat < a
// SPLIT = wc -l > b
// SPLIT = cat < b

// CMD = ls > a | cat a | wc -l
// -> Outputs 0 as ls > a | overwrites the cat a 
// SPLIT = ls > a
// SPLIT = cat a
// SPLIT = wc -l

// CMD = ls > a | wc -l new/85--master/Makefile 
// - Outputs line count of the Makefile as wc -l new/85--master/Makefile
//   is not the same file descriptor as ls > a 
// SPLIT = ls > a
// SPLIT = wc -l new/85--master/Makefile

// CMD = ls > a | wc -l a
// -> Outputs 0 as ls > a | overwrites the wc -l a as same file descriptor
// SPLIT = ls > a
// SPLIT = wc -l a

// CMD =  cat < a > b
// -> Creates a 'b' file with the content of the 'a' file
// SPLIT = cat < a > b

// CMD = cat < a > b | cat < a
// -> Prints the content of the 'a' file from 'b' file (created above)
// SPLIT = cat < a > b
// SPLIT = cat < a

// CMD = cat < a > b | cat < b
// -> Prints nothing a file descriptor for 'b' file is overwritten
// SPLIT = cat < a > b
// SPLIT = cat < b

// CMD = > a | cat a | wc -l
// -> Outputs 0 as > a | overwrites the cat a

// CMD = ls | wc > lol
// -> Creates a 'lol' file with the number of lines in the Makefile


int	ft_redir_pipe_detect(t_list *list)
{
	int pipe_nb = 0;
	int redir_right_nb = 0;
	int redir_left_nb = 0;

	t_list *current = list;

	while (current)
	{
		if (ft_strcmp(current->content, "|") == 0)
			pipe_nb++;
		if (ft_strcmp(current->content, ">") == 0
			|| ft_strcmp(current->content, ">>") == 0)
			redir_right_nb++;
		if (ft_strcmp(current->content, "<") == 0)
			redir_left_nb++;
		current = current->next;
	}
	if (pipe_nb == 0 && (redir_right_nb == 0 || redir_left_nb == 0))
		return (0);
	else if (redir_right_nb == 0 && redir_left_nb == 0 && pipe_nb > 0)
		return (0);
	return (1);
}

t_token	*ft_redir_pipe_prim_cmd(t_token **token)
{
	t_token *cmd = NULL;
	int index_redir = 0;
	int index_pipe = 0;

	while (*token) {

		if ((index_pipe == 1 || index_redir == 1) && ((*token)->t_type == PIPE || (*token)->t_type == L_REDIR || (*token)->t_type == R_REDIR || (*token)->t_type == DR_REDIR))
			break ;
		if ((*token)->t_type == L_REDIR || (*token)->t_type == R_REDIR || (*token)->t_type == DR_REDIR)
			index_redir = 1;
		else if ((*token)->t_type == PIPE)
			index_pipe = 1;
		if (cmd == NULL)
			cmd = ft_token_new((*token)->t_type, (*token)->value);
		else
			ft_token_add(&cmd, ft_token_new((*token)->t_type, (*token)->value));
		*token = (*token)->next;
	}
	return (cmd);
}

t_token *ft_redir_pipe_sec_cmd(t_token **token)
{
	t_token *cmd = NULL;

	if (*token == NULL)
		return (NULL);
	cmd = ft_token_new((*token)->t_type, (*token)->value);
	*token = (*token)->next;
	while (*token) {
		if ((*token)->t_type == L_REDIR || (*token)->t_type == R_REDIR
			|| (*token)->t_type == DR_REDIR || (*token)->t_type == PIPE)
			break ;
		ft_token_add(&cmd, ft_token_new((*token)->t_type, (*token)->value));
		*token = (*token)->next;
	}
	return (cmd);
}

int	ft_redir_pipe_argv_size(t_token *tmp)
{
    int count = 0;

    while(tmp && tmp->t_type != 0)
    {
        count++;
        tmp = tmp->next;
    }
    return (count);
}

char **ft_redir_pipe_argv(t_token *token)
{
    int i = 0;
    char **argv = NULL;
    t_token *tmp = token;
    int size = ft_redir_pipe_argv_size(tmp);

    if (!(argv = malloc(sizeof(char *) * (size + 1)))) {
        perror("malloc");
        exit (-1);
    }
    while(tmp && tmp->t_type != 0)
    {
        if (!(argv[i] = ft_strdup(tmp->value))) {
            perror("malloc");
            exit (-1);
        }
        tmp = tmp->next;
        i++;
    }
    argv[i] = NULL;
    return (argv);
}

int		ft_redir_pipe_type(t_token *token)
{
	t_token *tmp = token;

	while (tmp) {
		if (tmp->t_type == L_REDIR || tmp->t_type == R_REDIR || tmp->t_type == DR_REDIR || tmp->t_type == PIPE)
			return (tmp->t_type);
		tmp = tmp->next;
	}
	return (0);
}

t_list	*ft_redir_pipe_list(t_list *list, t_token *token)
{
	t_list *new_list = NULL;
	t_list *tmp_list = list;
	t_token *tmp_token = token;

	while (tmp_list && tmp_token && !ft_strcmp(tmp_list->content, tmp_token->value)) {
		tmp_list = tmp_list->next;
		if (!new_list)
			new_list = tmp_list;
		tmp_token = tmp_token->next;
	}
	tmp_list->next = NULL;
	return (new_list);
}

// int		ft_redir_pipe_prim_exec(t_list *list, t_token *token)
// {
// 	int fds[2];
//     char buffer[1024];
// 	pid_t pid = 0;
// 	int type = ft_redir_pipe_type(token);
	
// 	ft_print(token);

// 	pipe(fds);

// 	dup2(pipefd[1], STDOUT_FILENO);

// 	if (type == PIPE)
// 		ft_pipe(ft_redir_pipe_list(list, token), token);
// 	else if (type == R_REDIR || type == DR_REDIR)
// 		ft_redir_right(ft_redir_pipe_list(list, token), token);
// 	else if (type == L_REDIR)
// 		ft_redir_left(ft_redir_pipe_list(list, token), token);

// 	read(pipefd[0], buffer, sizeof(buffer));
// 	// close(fds[0]);
// 	close(fds[1]);
// 	fd = fds[0];
// 	return (0);
// }

int	ft_redir_pipe(t_list *list)
{
	// t_token *cmd = NULL;
	t_token *tmp = g_data.token;
	t_token last = *ft_lstlat_token(g_data.token);

	printf("-------> REDIR & PIPE\n");

	if (last.t_type == L_REDIR || last.t_type == R_REDIR
		|| last.t_type == DR_REDIR || tmp->t_type == PIPE) {
		printf("minishell: syntax error near unexpected token `newline'\n");
		g_data.exit = 258;
		return (258);
	}
	// ft_redir_pipe_prim_exec(list, ft_redir_pipe_prim_cmd(&tmp));
	// while (tmp && tmp->next && (cmd = ft_redir_pipe_sec_cmd(&tmp))) {

	// 	ft_print(cmd);
		
	// 	ft_free_token(cmd);
	// 	cmd = NULL;
	// }
	(void)tmp;
	(void)list;
	return (0);
}