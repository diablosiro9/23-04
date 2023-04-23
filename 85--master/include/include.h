/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:33:27 by mla-rosa          #+#    #+#             */
/*   Updated: 2023/04/23 04:32:58 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <limits.h>
# include "../lib/libft/libft.h"
# include "../lib/gnl/get_next_line.h"



#define MAX_LINE_LEN 1024

typedef struct s_env
{
	char	*name;
	char	*content;
	char 	**env;
	int		num_vars;
	struct s_env	*next;
}
t_env;


// enum struct
typedef struct s_token
{ 
	enum s_type
	{
		PIPE,
		R_REDIR,
		DR_REDIR, //infile
		WORD,
		QUOTE,
		SQUOTE,
		DOLLAR,
		OPTION,
		COMMAND,
		HERE_DOC,
		END_OF,
		L_REDIR,
		RREDIR,
	} t_type;
	char *value;
	struct s_token	*next;
} t_token;

typedef	struct	t_echo {
	t_token	*tmp;
	char	*cmd;
	char	*stock;
	size_t	i;
	int		j;
	int		flag;
	int		redir;
	int		stop;
	int		delim;
}	t_echo;

typedef struct	t_export {
	t_env	*env;
	t_token	*tmp;
	char	*s1;
	char	*s2;
	char	*new_env;
	size_t	i;
	int		fd;
	int		flag;
	int		redir;
}	t_export;

typedef struct t_alpha {
	t_env	*env;
	char	*s1;
	char	*s2;
	int		i;
	int		fd;
	int		flag;
}	t_alpha;
// void	write_fct(t_env *tmp, char *s1, int *i, int *flag, int fd)
// void	finish_alpha(t_env *env, char *s1, char *s2, int i, int fd)

/*
	Mimi - La structure t_list doit être dans le header de ta libft sinon les fonctions bonus vont pas marcher
	typedef struct s_list
	{
		void			*content;
		struct s_list	*next;
	}				t_list;
*/

typedef struct t_data {
	char 	*cmd;
	t_list	*list;
	t_env	*export;
	t_env	*env;
	t_token	*token;
	int		exit;
	char	*pwd;
}	t_data;

t_data		g_data;


void	norm(void);
void	ft_tab_delete(char **tab);
void	ft_list_delete(t_list **l);
void 	rl_replace_line(const char *text, int clear_undo);
//------------------------------------- main -------------------------------------

int 	main(int ac, char **av, char **env);

//------------------------------------exec------------------------------------

// Exec (./src/exec/exec.c)
int		ft_exec(t_list *str);
void    ft_exec_command(char *cmd_file, char **argv);
char 	**ft_exec_args(t_list *str);
int 	ft_exec_proc(pid_t pid);

// Split (./src/exec/split.c)
void	*split_cmd_file(char *str);
char	**ft_oldsplit(char const *s, char c);
char	*ft_alloc_str(char const *s, char c);
int		count_char_c(const char *s, char c);
int		ft_check_c(char s, char c);

// Pipe (./src/exec/pipe.c)
int		ft_pipe_detec(t_list *str);
int		ft_pipe(t_list *list, t_token *token);

// Redirection (./src/exec/redir.c)
int ft_redir_right(t_list *list, t_token *tmp);
int ft_redir_detec_right(t_list *str);
int ft_redir_detec_left(t_list *str);
int ft_redir_left(t_list *list, t_token *tmp);

// Redirection & Pipe (./src/exec/redir_pipe.c)
int	ft_redir_pipe_detect(t_list *list);
int ft_redir_pipe(t_list *list);

// Here_Doc (./src/exec/here_doc.c)
int	det_hd(void);
t_list	*simple_hd();
char	**fill_hd_arg(char *path, char *name);
t_list	*here_doc(char *delim, int flag);

// Here_Doc (./src/exec/help_hd.c)
int	print_hd_error(t_token *tmp);
int	det_nb_hd(void);

//------------------------------------lexer------------------------------------

// Lexer (./src/lexer/lexer.c)
t_list	*ft_lexer(char *str);

// Split (./src/lexer/split.c)
char	**ft_split (char *str);

// Tokenizateur (./src/lexer/tokenizateur.c)
t_token *tokenizateur(t_list *list);
void	ft_token_init( int type, char *value);
t_token *ft_token_add(t_token **alst, t_token *new);
t_token			*ft_token_new(int type, char *value);
void			ft_token_delete(t_token **l);
void			ft_token_addf(t_token **alst, t_token *new);
t_token 		*delete_token(t_token* head, int position);

int				det_squote(char *str);
int				det_dquote(char *str);
void			some_quotes(t_token *tmp, char *stock, char *res, int start, int i);
void			case_dquote(t_token *tmp, char *stock, char *res, int start, int i, int j, int pos);
void			case_squote_term(t_token *tmp, char *stock, char *res, int start, int i, int j, int pos);
void			some_dquotes(t_token *tmp, char *stock, char *res, int start, int i);
void			destroyer(int start, int i);
void			split_res_main( t_token *tmp, char *res, char *stock, int i);


//------------------------------------parsor------------------------------------

// Parsor (./src/parsor/parsor.c)
t_list			*ft_parsor(t_list *str);
void			*find_all_dollars();
void			*checking_solo_name(t_token *tmp);
void			*solo_command();
void			*manage_double();
int				token_size();

// Checker (./src/parsor/check.c)
int				checking_closed(char *tp);
int				closed_elem(char *str, char c);

//------------------------------------signals------------------------------------

void 			sig_handler(int sig);
void 			sig_quit(int sig);


//------------------------------------builtin------------------------------------

//(./src/built_in/det_built.c)
int				help_builtin();
int				det_builtin();

// (./src/built_in/cd.c)
void			ft_cd(char *path);
void			ft_exit(long long nb, int flag);
unsigned int	starter_env(char *s);
int				back_path(char *str);
char			*cut_pwd(char *str, int n_back);
void			change_env_content (char *name, char *new);
void			finish_cd(char *pwd, char *tmp, char *res);




// (./src/built_in/env.c)
char			*ft_sub(char const *s, unsigned int start, size_t len);
void			ft_env(char	*s);
char			*search_env_content_do(t_env *env, char *name);

// (./src/built_in/echo.c)
int				ft_echo( int R_REDIR);
int				ft_iswspace(char c);
int				ft_isquote(int c);
int				case_quote(t_echo *echo);
int				case_squote(t_echo *echo);
int				case_option(t_echo *echo, int f_round);
int				case_string(char *cmd, t_token **tmp, size_t *i, int redir);
void			help_echo(t_echo *echo);
void			flag_equal_two(t_echo *echo);
void			stock_diff_null(t_echo *echo);
void			main_case_quote(t_echo *echo);
void			main_case_squote(t_echo *echo);




// (./src/buil_in/export.c)
int				ft_export(int R_REDIR);

// (./src/buil_in/help_export.c)
int				check_str(char *s1, char *s2);
int				ft_lstadd_back_env(t_env **alst, t_env *new);
t_env			*ft_lstnew_env(char *name, char *content);
int				ft_same_content(char *name, char *content);
char			*ft_strjoin_w(char *s1, char *s2);
void			print_export(t_env *env, int fd);
void			print_for_alpha(t_env *tmp, int fd);
void			finish_alpha(t_env *env, char *s1, char *s2, int fd);
int				skip(char **new_env, size_t *i, t_token **tmp, char *cmd);
int				env_exist(char *name);
char			*reverse_chr(char *s, char c);
int				help_export(t_export *export);
char			*treat_last_part(char *str);
int				export_norm(t_token *tmp, char *new_env, char **stock, int flag);




// (./src/built_in/unset_pwd)
void			ft_unset();
void			ft_pwd();
void			cmd_unset_assist(char *name, char *content);
void			true_unset();

// (./src/built_in/cd_exit.c)
unsigned int	starter_env(char *s);
t_env			*ft_envnew(char *name, char *content, int i);
void			ft_envadd(t_env **lst, t_env *new);
t_env			*get_env_do(char **env);

//------------------------------------utils------------------------------------

// Environnement (./src/utils/env.c)
t_env			*get_env(char **env);
unsigned int	get_env_starter(char *s);
int				checking_str(char *ref, char *find);
char			*search_env_content(t_env *env, char *name);
char **get_env_bis(t_env *env);
void	*get_cmd_file(char *cmd);
t_env *get_env_do(char **env);


// Affichage (./src/utils/aff.c)
void	afftab(char **tab);
void	afflist(t_list *list, char *name);
void 	afftoken(t_token *list, char *name);

// List (./src/utils/list.c)
t_list	*ft_lstadd(t_list **alst, t_list *new);
t_token	*ft_lstlat_token(t_token *lst);


// String (./src/utils/str.c)
char	*ft_strchr(const char *s, int c);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
void	ft_putstr(char *str);
char	*ft_strjoin_bis(char const *s1, char const *s2);

// Free (./src/utils/free.c)
void	free_tab(char **cmd);
void	ft_free_token(t_token *token);

// Tab (./src/utils/tab.c)
int     ft_tablen(char **tab);

t_list	*dquote_mod(char *delim, int flag);

int	det_hd();

#define MAX_BUF_SIZE 4096


#endif

