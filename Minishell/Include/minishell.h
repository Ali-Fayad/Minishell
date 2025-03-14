/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:11:36 by afayad            #+#    #+#             */
/*   Updated: 2025/02/22 06:11:49 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>

extern int	g_s;

typedef struct s_env {
	char			*var;
	int				check;
	struct s_env	*next;
}	t_env;

typedef struct s_exec_data {
	int		g_exit_status;
	t_env	**head;
	pid_t	*pids;
	int		i;
}	t_exec_data;

typedef struct s_pars {
	int		count;
	int		*open_q;
	int		*close_q;
}	t_pars;

typedef struct s_op {
	char	*first;
	char	*second;
	int		i;
}	t_op;

typedef struct s_parsd {
	char	*str;
	int		quotes;
}	t_parsd;

typedef struct s_exp {
	char	*var;
	char	*value;
}	t_exp;

typedef struct s_dollar {
	int		i;
	int		j;
	int		len;
	int		result_len;
	int		quotes;
	int		quotes2;
	int		exit_len;
	char	*result;
	char	*var_name;
	char	*env_value;
	char	*exit_str;
}	t_dollar;

typedef struct s_pipe {
	char		**cmds;
	char		*msg;
	char		**raw_cmds;
	t_exec_data	exec_data;
	int			num_pipes;
	int			i;
	int			prev_fd;
	int			status;
	int			pipe_fd[2];
	int			cmd_index;
	pid_t		heredoc_pid;
}	t_pipe;

typedef struct s_splitting_pipe {
	int		i;
	int		j;
	int		k;
	int		quotes;
	char	**args;
	char	*tmp;
	char	current_char;
}	t_splitting_pipe;

// Parsing Functions
char	*ft_quotes(char *msg);
char	*ft_valid(char *msg, t_env **head, int *g_exit_status);
char	*quotes(char *msg);
int		valquotes(char *str);
int		c_dollar(char *msg);
int		count_quotes(char *msg);
t_pars	ft_pars(char *msg);
t_exp	*parse_exp(char *msg);

// Environment Functions
char	**transfer_to_2d_array(t_env *head);
char	*find_env_var(char *msg, t_env **head, int *g_exit_status);
char	*get_env_value(char *new, t_env **head);
char	*replace_env_varss(char *input, t_env **head, int *g_exit_status);
char	*g_path(char *cmd, t_env *head);
char	**export_split(char *msg);
char	*remove_dot_segments(char *direction);
void	handle_env_var(t_dollar *dollar, char *input, t_env **head,
			int *g_exit_status);
int		get_oldpwd(t_env **head);
int		ft_isvar(char *var, int *exit_status);
int		export_split_helper(char *msg);
int		search_env_var(t_env **head, char *search);
int		should_process_dollar(t_dollar *dollar, char *input);
int		process_dollar_logic(t_dollar *dollar, char *input,
			t_env **head, int *g_exit_status);
int		process_input_string(t_dollar *dollar, char *input, t_env **head,
			int *g_exit_status);
int		handle_exit_status(t_dollar *dollar, int *g_exit_status);
int		is_special_char(char c);
void	handle_dollar_char(t_dollar *dollar, char *input);
void	pwd(t_env **head);
void	unset(t_env **head, char *msg);
void	add_env(char **envp, t_env **head);
void	cd(char *msg, t_env **head, int *g_exit_status);
void	cd_null(t_env **head);
void	change_check(char *var, t_env **head, int new);
void	change_env(t_env **head, char *catch, char *replace);
void	echo(char *str, int *g_exit_status);
void	ft_addvariable(t_env **head, char *variable);
void	print_export(t_env *head);
void	no_dir(char *msg, t_env **head);
void	export(char *msg, t_env **head, int *exit_status);
void	update_variable(t_env **head, char *var, char *fullvar);
void	handle_empty_env(t_env **head);
void	increment_shlvl(t_env **head);
void	cd_null_null(t_env **head);

// Execution && Pipe Functions
void	execute_command(char *arg, t_env *head, int *g_exit_status);
void	ft_check2(char *msg, t_env **head, int *g_exit_status);
void	ft_pipe(char *msg, t_env **head, int *g_exit_status);
void	command_menu(char *result, t_env **head, int *g_exit_status);
void	handle_heredoc_failure(t_pipe *pipe_data, int *g_exit_status);
int		count_pipe(char *msg);
void	wait_for_children(t_pipe *pipe_data, int *g_exit_status);
void	execute_commands(t_pipe *pipe_data, t_env **head,
			int *g_exit_status);
void	process_heredocs_child(t_pipe *pipe_data);
void	handle_child_process(t_pipe *pipe_data, t_env **head,
			int *g_exit_status);
int		process_input_string2(t_splitting_pipe *norm, char *msg);
int		init_splitting_pipe(t_splitting_pipe *norm, char *msg);

// Operations Functions
char	*operations(char *msg, int *g_exit_status);
int		catch_op(char *msg);
int		op_first(char *msg);
int		handle_heredoc_process(t_pipe *pipe_data, int *g_exit_status);
void	dir_input(const char *filename, int *g_exit_status);
void	dir_output(const char *filename, int append, int *g_exit_status);
void	process_input(char *input, t_env **head, int *g_exit_status);
void	input_op2(char *tmp, int *exit_status, int count);
void	output_op2(char *tmp, int *exit_status, int count);
void	op_redirection(char *msg, int *g_exit_status);
t_op	op_extract_command(char *msg);

// Heredoc Functions
char	**process_heredocs_with_copy(char **strs, int checeker);
char	*split_heredoc_helper(char *msg, int checker);
int		c_heredoc(char *msg);
int		count_here_docs(char *msg);
void	here_doc(char **end_marker);
void	here_doc2(char *end_marker);
void	extract_heredoc(char *input);

// Libft Utils Functions
char	**ft_split(char const *s, char c);
char	**spliting_pipe(char *msg);
char	*split_backslash(char *msg, t_env **head, int *g_exit_status);
char	*char_to_string(char c);
char	*strip_dot_slash(char *cmd);
char	*ft_s_strjoin(int size, char **strs, char *sep);
char	*ft_strcat(char *dest, char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(char *src);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strndup(const char *src, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strskip(char *str, size_t size);
char	*ft_strskip_spaces(char *str);
char	*ft_itoa(int n);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*last_char_ptr(char *msg);
char	*r_l_b(char *str);
char	*remove_last_char(char *msg);
char	*remove_quotes_and_equals(char *str);
char	*remove_spaces(char *str);
int		ft_catchchar(char *str, char c);
int		ft_count_char(char *str, char c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isquotes(char *msg);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_strnstr(const char *str, const char *to_find, size_t len);
int		ft_strstr(char *str, char *to_find);
int		get_index(char *str);
int		is_only_spaces(char *str);
int		str_isnum(char *msg);
int		strs_arenum(char **msg);
int		count_double_ptr(char **msg);
int		ft_atoi(char *str);
int		ft_exit(char *msg, int *status);
int		dollar_counter(char *str, t_env **head);
int		is_first_word_directory(char *msg);
size_t	ft_number_size(int number);
size_t	ft_strlcat(char *dest, char *src, unsigned int size);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
void	*ft_memcpy(void *dest, void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_putnbr(int nb);
void	ft_strncpy(char *str, char const *src, int n);
void	v_strcat(char *dest, char *src);
void	v_strcpy(char *dest, char *src);
void	v_strncat(char *dest, const char *src, size_t n);
void	v_strncpy(char *dest, const char *src, size_t n);

// Free Functions
void	free_cmds(char **cmds, int i);
void	free_env(t_env *head);
void	free_env_array(char **env_array);
void	write_to_file(char *str);
void	free_exp(t_exp *exp);
void	cleanup_and_finalize(t_pipe *pipe_data, int *g_exit_status);

// File Functions
void	append_chars_to_file(const char *filename, char *str);
void	clear_file(char *filename);
void	dup_file(char *filein, char *fileout);

// Print Functions
void	handle_error(char *msg, int exit_code);
void	print_double_ptr(char **args);
void	print_env(t_env *head);
void	print_error(char *message, int exit, int *g_exit_status);
void	print_error_arg(char *message, char *var, int exit, int *g_exit_status);

// Signals Functions
void	ignore_signals(void);
void	restore_signals(void);
void	setup_signals(void);

#endif
