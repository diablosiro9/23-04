#include "../../include/include.h"

int ft_redir_detec_right(t_list *str)
{
	int i = 0;
	t_list *current = str;
	
	while (current != NULL)
	{
		if (ft_strcmp(current->content, ">") == 0
			|| ft_strcmp(current->content, ">>") == 0)
			i++;
		else if (ft_strcmp(current->content, "<") == 0
			|| ft_strcmp(current->content, "|") == 0)
			return (0);
		current = current->next;
	}
	printf("-> DETECTED %d R_REDIR RIGHT\n", i);
	return (i);
}

int ft_redir_detec_left(t_list *str)
{
   int i = 0;
	t_list *current = str;
	
	while (current->next != NULL)
	{
		if (ft_strcmp(current->content, "<") == 0)
			i++;
		else if (ft_strcmp(current->content, ">") == 0
			|| ft_strcmp(current->content, ">>") == 0
			|| ft_strcmp(current->content, "|") == 0)
			return (0);
		current = current->next;
	}
	return (i);
}

// int R_REDIR_left(t_list *str) {
//    int fd;
//    int ret = 0;
//    char *filename;
//    char *command;
//    char buf[BUFSIZ];
//    char **argv = ft_exec_args(str);

//    filename = argv[2];
//    printf("filename = %s\n", filename);
//    command = argv[0];
//    printf("command = %s\n", command);

//    fd = open(filename, O_RDONLY);

//    if(fd == -1) {
//       printf("Erreur filename %s\n", filename);
//       exit(1);
//    }

//    int pipe_fd[2];
//    if (pipe(pipe_fd) == -1) {
//       printf("tube pt\n");
//       exit(1);
//    }

//    pid_t pid = fork();

//    if (pid == -1) {
//       printf("fils dead\n");
//       exit(1);
//    } else if (pid == 0) {
//       close(pipe_fd[0]); 
//       dup2(pipe_fd[1], STDOUT_FILENO);
//       close(pipe_fd[1]);
//       dup2(fd, STDIN_FILENO);
//       ret = read(fd, buf, BUFSIZ);
//       printf("fd = %d - ret = %d\n, ", fd, ret);
//       close(fd);
//       char *cmd[] = {get_cmd_file(command), NULL};
//       execve(get_cmd_file(command), cmd, get_env_bis(g_data.env));
//       exit(1);
//    } else {
//       close(pipe_fd[1]); 

//       while (1) {
//          int bytes_read = read(pipe_fd[0], buf, BUFSIZ); 
//          printf("LECTURE = %d\n", bytes_read);
//          if (bytes_read <= 0) break;
//          write(STDOUT_FILENO, buf, bytes_read); 
//       }
//       close(pipe_fd[0]); 
//       close(fd);
//       waitpid(pid, NULL, 0);
//    }
//    return 0;
// }




// int ft_redir_right(t_list *str) 
// {
//    int fd, status;
//    char *filename;
//    char *command;
//    char **argv = ft_exec_args(str);
//    char buf[MAX_BUF_SIZE];
//    pid_t pid;

//    filename = argv[2];
//    printf("filename = %s\n", filename);
//    command = argv[0];
//    printf("command = %s\n", command);

//    fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH); // ouvrir le fichier en écriture
//    printf("fd = %d\n", fd);
//    if(fd == -1) {
//       fd = open(filename, O_WRONLY | O_TRUNC);
//       if (fd == -1) {
//          fd = open(filename, O_RDWR); 
//          if (fd == -1) {
//             printf("Erreur filename1 %s\n", filename);
//             exit(1);
//          }
//       }
//    }

//    int pipe_fd[2]; 
//    if (pipe(pipe_fd) == -1) {
//       printf("tube pt1\n");
//       exit(1);
//    }

//    pid = fork(); 
//    printf("FILS = %d\n", pid);
//    if (pid == -1) {
//       printf("fils dead1\n");
//       exit(1);
//    } else if (pid == 0) { 
//       close(pipe_fd[0]); 
//       dup2(pipe_fd[1], STDOUT_FILENO);
//       close(pipe_fd[1]); 
//       char *cmd[] = {get_cmd_file(command), NULL};
//       execve(get_cmd_file(command), cmd, get_env_bis(g_data.env)); 
//       exit(1);
//    } else { 
//       close(pipe_fd[1]); 

//       while (1) {
//          int bytes_read = read(pipe_fd[0], buf, MAX_BUF_SIZE); 
//          if (bytes_read <= 0) break;
//          write(fd, buf, bytes_read); 
//       }

//       close(pipe_fd[0]); 
//       close(fd); 

//       waitpid(pid, &status, 0); 
//    }

//    return 0;
// }


// char *ft_R_REDIR_rigth_file(t_token *token)
// {
//    t_token *tmp = token;

//    while (tmp && tmp->t_type != R_REDIR) {
//       tmp = tmp->next;
//    }
//    return tmp->next->value;
// }

// int ft_redir_right_exec(t_token cmd, char **argv, char *file)
// {
   
//    printf("EXEC CMD = %s | %u\n", cmd.value, cmd.t_type);
//    for (int i = 0; argv[i]; i++) {
//       printf("argv[%d] = %s\n", i, argv[i]);
//    }
//    printf("file = %s\n", file);

//    int fds[2];
//    int status = 0;
//    pid_t pid = 0;
//    static int file_fd = 0;

//    if (access(file, F_OK | R_OK) == 0 && (file_fd = open(file, O_WRONLY | O_TRUNC | O_RDONLY)) == -1)
//       perror("open");
//    else if ((file_fd = open(file, O_CREAT | O_WRONLY, 0644)) == -1)
//       perror("open");
//    pipe(fds);
//    if ((pid = fork()) == -1)
//       perror("fork");
//    else if (pid == 0) {
//       dup2(fds[0], STDIN_FILENO);
//       dup2(fds[1], STDOUT_FILENO);
//       dup2(file_fd, STDOUT_FILENO);
//       if (execve(cmd.value, argv, get_env_bis(g_data.env)) == -1) {
//          perror("execve");
//          exit(EXIT_FAILURE);
//       }
//    }
//    else {
//       waitpid(pid, &status, 0);
//       if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
//          close(fds[0]);
//          close(fds[1]);
//          close(file_fd);
//          return WEXITSTATUS(status);
//       }
//    }
//    close(fds[0]);
//    close(fds[1]);
//    close(file_fd);
//    return 0;
// }

int   ft_redir_cmd_size(t_token *token)
{
   int   size = 0;
   t_token *tmp = token;

   while (tmp && tmp->t_type != R_REDIR) {
      tmp = tmp->next;
      size += 1;
   }
   return size;
}

char  **ft_redir_cmd(t_token **token)
{
   int idx = 0;
   char **cmd = NULL;
   int size = ft_redir_cmd_size(*token);
   
   if (!(cmd = malloc(sizeof(char *) * (size + 1))))
      return NULL;
   while (*token && (*token)->t_type != R_REDIR && (*token)->t_type != DR_REDIR && (*token)->t_type != L_REDIR) {
      cmd[idx] = ft_strdup((*token)->value);
      *token = (*token)->next;
      idx += 1;
   }
   cmd[idx] = NULL;
   return cmd;
}

char  **ft_redir_cmd_argv(char **cmd, char *argv)
{
	int idx = 0;
	char **new_cmd = NULL;
	int size = ft_tablen(cmd);

	printf("qrgv = %s\n", argv);
	if (!(new_cmd = malloc(sizeof(char *) * (size + 2))))
		return NULL;
	else if (cmd != NULL) {
		while (cmd[idx]) {
			new_cmd[idx] = ft_strdup(cmd[idx]);
			idx += 1;
		}
		free_tab(cmd);
	}
	new_cmd[idx] = ft_strdup(argv);
	new_cmd[idx + 1] = NULL;
	return new_cmd;
}

int ft_redir_file(char *file, int r_type)
{
	int fd = 0;

	if (r_type == L_REDIR) {
		if (access(file, F_OK | R_OK) == 0)
			return (open(file, O_RDONLY));
		printf("minishell: %s: No such file or directory\n", file);
		return (-1);
	}
	else if (access(file, F_OK | R_OK) == 0) {
		if ((r_type == R_REDIR && (fd = open(file, O_WRONLY | O_RDONLY | O_TRUNC)) == -1)
			|| (r_type == DR_REDIR && (fd = open(file, O_WRONLY | O_RDONLY | O_APPEND)) == -1))
			perror("open");
	}
	else if ((fd = open(file, O_CREAT | O_WRONLY, 0644)) == -1) {
		perror("open");
	}
	return (fd);
}

int ft_redir_right_exec(int fd, char **argv)
{
	int fds[3];
	int status = 0;
	pid_t pid = 0;

	pipe(fds);
	if ((pid = fork()) == -1)
		perror("fork");
	else if (pid == 0) {
		dup2(fds[0], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		if (execve(argv[0], argv, get_env_bis(g_data.env)) == -1) {
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else {
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
			close(fds[0]);
			close(fds[1]);
			close(fd);
			return WEXITSTATUS(status);
		}
	}
	close(fds[0]);
	close(fds[1]);
	close(fd);
	return 0;
}



int ft_redir_right(t_list *list, t_token *tmp)
{
	int fd = 0;
	char **cmd = NULL;
	int type_redir = 0;
	int type_start = 0;
	t_token last = *ft_lstlat_token(g_data.token);
	t_token *prev = NULL;

	printf("-------> REDIR RIGHT\n");

	g_data.list = list;
	if (tmp == NULL)
		tmp = g_data.token;
	if (((tmp->t_type == R_REDIR || tmp->t_type == DR_REDIR) && tmp->next == NULL) 
		|| last.t_type == R_REDIR || last.t_type == DR_REDIR) {
		printf("minishell: syntax error near unexpected token `newline'\n");
		g_data.exit = 258;
		return (258);
	}
	if (tmp->t_type != R_REDIR && tmp->t_type != DR_REDIR) {
		cmd = ft_redir_cmd(&tmp);
		type_start = 1;
	}
	while (tmp) {
		if (tmp->t_type == R_REDIR || tmp->t_type == DR_REDIR)
			type_redir = tmp->t_type;
		else if (type_start == 0 && prev && prev->t_type != R_REDIR && prev->t_type != DR_REDIR) {
			if (cmd == NULL)
				cmd = ft_redir_cmd_argv(cmd, (char *)get_cmd_file(tmp->value));
			else
				cmd = ft_redir_cmd_argv(cmd, tmp->value);
		}
		else if (type_start == 1 && (tmp->t_type == OPTION || (tmp->t_type == WORD && prev && prev->t_type == WORD)))
			cmd = ft_redir_cmd_argv(cmd, tmp->value);
		
		else if (tmp->t_type == WORD)
			fd = ft_redir_file(tmp->value, type_redir);
		prev = tmp;
		tmp = tmp->next;
	}
	if (cmd) {
		if (access(cmd[0], F_OK | X_OK) == -1) {
			printf("minishell: %s: command not found\n", cmd[0]);
			g_data.exit = 127;
			return (127);
		}
		ft_redir_right_exec(fd, cmd);
		free_tab(cmd);
	}
	return (0);
}

int	ft_redic_left_exec(char **cmd)
{
	int status = 0;
	pid_t pid = 0;

	if ((pid = fork()) == -1)
		perror("fork");
	else if (pid == 0) {
		if (execve(cmd[0], cmd, get_env_bis(g_data.env)) == -1) {
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else {
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
			return WEXITSTATUS(status);
		}
	}
	return 0;
}

int ft_redir_left(t_list *list, t_token *tmp) {
	
	int fd = 0;
	char *file = NULL;
	char **cmd = NULL;
	int type_start = 0;
	t_token last = *ft_lstlat_token(g_data.token);
	t_token *prev = NULL;

	printf("-------> REDIR LEFT\n");
   	

	g_data.list = list;
	if (tmp == NULL)
		tmp = g_data.token;

	if ((tmp->t_type == L_REDIR && tmp->next == NULL) || last.t_type == L_REDIR) {
		printf("minishell: syntax error near unexpected token `newline'\n");
		g_data.exit = 258;
		return (258);
	}
	if (tmp->t_type != L_REDIR) {
		cmd = ft_redir_cmd(&tmp);
		type_start = 1;
	}
	while (tmp) {
		if (type_start == 0 && prev && prev->t_type != L_REDIR) {
			if (cmd == NULL)
				cmd = ft_redir_cmd_argv(cmd, (char *)get_cmd_file(tmp->value));
			else
				cmd = ft_redir_cmd_argv(cmd, tmp->value);
		}
		else if (type_start == 1 && (tmp->t_type == OPTION || (tmp->t_type == WORD && prev && prev->t_type == WORD)))
			cmd = ft_redir_cmd_argv(cmd, tmp->value);
		else if (tmp->t_type == WORD) {
			fd = ft_redir_file(tmp->value, L_REDIR);
			if (fd == -1)
				return (1);
			free(file);
			file = ft_strdup(tmp->value);
		}
		prev = tmp;
		tmp = tmp->next;
		
	}
	if (cmd) {
		if (access(cmd[0], F_OK | X_OK) == -1) {
			printf("minishell: %s: command not found\n", cmd[0]);
			g_data.exit = 127;
			return (127);
		}
		cmd = ft_redir_cmd_argv(cmd, file);
		ft_redic_left_exec(cmd);
		free_tab(cmd);
	}
   	return 0;
}