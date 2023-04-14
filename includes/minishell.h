/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 04:26:50 by oufisaou          #+#    #+#             */
/*   Updated: 2023/04/14 06:54:07 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define YES 1
# define NO 0
# define PATH_MAX 4096

typedef enum type_s
{
	WORD,
	QUOTE,
	DQUOTE,
	SPAACE,
	GREAT,
	DGREAT,
	LESS,
	DLESS,
	PIPE,
	DOLLAR
}					t_type;

typedef struct token_s
{
	char			*data;
	char			*old_data;
	unsigned int	type;
	struct token_s	*next;
	struct token_s	*prev;

}					t_token;

typedef struct s_cmd
{
	char			*cmd_path;
	char			**cmd_args;
	int				infile;
	int				outfile;
	int				pipe_in;
	int				pipe_out;
	int				exec;
	t_token			*tokens_cmd;
}					t_cmd;

typedef struct s_var
{
	t_list			**tmp;
	t_list			*p1;
	t_list			*p2;
	int				index1;
	int				index2;
	int				swapped;
}					t_var;

typedef struct s_gen
{
	int				exit_status;
	int				exec;
	int				skip_all;
	t_list			*env;
	char			**envp;
	char			*pwd;
}					t_gen;

extern t_gen		g_gen;

int				check_arg(char *next);
int				check_arg2(char *next);
int				array_len(char **array);
char			*ft_to_lower(char *str);
int				ft_strlen2(char **str);
char			*join_str(const char *s1, const char *s2);
void			print_err_exp(char *next);
void			print_err_uns(char *next);
int				modify_env(char *pwd);
int				change_env(char *p);
int				ft_add_list(t_list **env_list, char *str);
void			suite(char **str);
int				set_flag(char *s);
void			ft_env(char **str);
void			suite7(char *str);
int				ft_exit(char **next);
int				is_long(char *next);
int				check_valid(char *next);
void			suite3(char *str);
int				has_equal(char *str);
void			suite4(char *str);
void			print_export(t_list *env);
int				commands(char **line);
void			go_commands(char **line);
int				small(char **p);
int				small2(char **p);
int				small3(char **pwd);
int				s1(char *str);
int				start_unset(t_list *env, char *next);
long long		ft_atoll(const char *dest);
char			**get_cmds(t_token *tokens);
void			creat_cmd_args(t_cmd **cmds, int pipe);
t_cmd			*setup_cmd(t_token **tokens, int *pipes);
void			parse_cmds(t_token **toknes);
void			cmd_not_found(char *cmd);
void			open_rest_file_err(int fd, t_token **tokens, int status);
int				is_directory(const char *path);
void			is_a_dir(char *dir);
char			*return_path(char **cmd_path, char **paths);
char			*ft_strjoin_1(char const *s1, char const *s2);
void			free_arr(char **arr);
t_cmd			*creat_cmds(t_token **tokens, int *pipes);
t_list			*env_create(char **envp);
char			**set_env(char **envp);
void			error_free(char *str);
void			free_envp(void);
char			*str_to_lower(char *str);
void			free_cmds(t_cmd *cmds, int pipes_num);
void			sig_ign(void);
void			sig_dfl(void);
void			sig_handler(void);
void			wait_all(int pid, int i, int pipes_num);
void			expander(t_token **tokens);
void			expander_in_quotes_utils(t_token **token, t_list *env);
void			expander_in_quotes(t_token **tokens);
t_list			*swap(t_list *ptr1, t_list *ptr2);
int				len_list(t_list **list);
void			ft_sort(t_gen *gen);
void			change_data(t_token **tokens, char *data);
void			play_with_tokens(t_token **tokens, char *str, t_list *env);
char			*get_var_utils(char **str, int *i, t_list *env);
char			*get_var(char **str, char *final_quote, t_list *env);
char			*find_value(char *str, t_list *env_l);
char			*get_var_str(char *str, int *i);
char			*get_env_var(char *str, t_list *env);
int				get_dollars(char *str);
void			get_sympol_less(t_token **tokens, char **str, int *here);
void			get_token_utils(t_token **tokens,
						char **str,
						int *here,
						int *here2);
int				get_quote(char **str, char c);
int				get_word(char **str, int *here, int *here2);
char			*get_char(char **str, char *c, int increment);
void			get_sympol_great(t_token **tokens, char **str);
int				ft_strcmp(char *s1, char *s2);
void			write_to_fd(int fd, char *str);
int				expand_y_n(char **str);
char			*expander_heredoc(char *line);
int				heredoc(char *limiter, int *exit_status);
void			wait_heredoc(int *exit_status, int pid);
void			handler1(int sig);
void			rm_redirecitons(t_cmd **cmds, int pipes);
void			check_file_direcitons(t_cmd **cmds, int pipes);
int				open_file(t_token **tokens, int type);
int				creat_in_files(t_cmd **cmds, t_token *tokens, int i);
int				creat_out_files(t_cmd **cmds, t_token *tokens, int i);
char			*join_mix(t_token *token1, t_token *token2);
void			join_word(t_token **tokens);
char			*join(char *final_quote, char *tmp);
t_token			*new_token(unsigned int type, char *data);
void			add_at_end(t_token **tokens_head, t_token *token);
void			add_token_last(t_token **token_head,
					unsigned int type, char *data);
int				count_pipes(t_token *tokens);
char			*rm_quotes(char *str, char c);
void			rm_quotes_tokens(t_token **tokens);
void			rm_token(t_token **tokens);
void			rm_spaces(t_token **tokens);
int				check_pipe(t_token *token);
int				check_directions(t_token *token);
int				syntax_err(t_token *token);
void			handler(int sig);
int				handle_signals(void);
int				check_quotes(t_token *token);
int				check_inside(t_token *tmp);
int				check_newline(t_token *c);
int				handle_spaces(t_token *c);
void			get_token(t_token **tokens, char **str);
int				count_tokens(t_token *tokens);
void			clear_tokens(t_token **tokens);
t_token			*tokenize(char *line);
char			*join_cmd(char *path, char *cmd);
void			free_all(t_list *tokens);
int				check_nature(char *next);
int				error(char *next);
void			suite8(char *str);
char			*ft_itoa1(long long n);
int				to_num(char c);
void			suite9(char *str);
/*Exec functions*/
void			execute(t_cmd *cmds, int pipes_count);
int				simple_error(char *msg);
int				fatal_error(char *msg);
/*utils functions*/
char			*ft_strjoin_adjusted(char *s1, char *s2);
char			*ft_substr_adjusted(char const *s, unsigned int start,
						size_t len);
char			**ft_split_adjusted(char const *s, char c);
/*builtins functions*/
int				is_builtin(t_cmd *cmd);
void			sig_handler(void);
void			sig_dfl(void);
void			sig_ign(void);
int				exec_builtin(t_cmd *cmds, int cmd_num);
int				exec_echo(t_cmd *cmd);
int				exec_exit(int cmd_num, int ret);
int				exec_pwd(void);
int				exec_cd(t_cmd *cmds);
int				exec_env(t_cmd *cmds);
int				exec_export(t_cmd *cmds);
void			print_sorted_args(void);
void			sort_string(char **strings, int n);
void			print_processed_env(char *env);
int				exec_unset(t_cmd *cmds);
void			remove_env_var(t_list *ptr);
int				remove_env(char *env);
char			*find_path_env(void);
int				get_envp_size(void);
char			**make_envp(void);
void			close_files(t_cmd *cmd);
void			set_pipes(t_cmd *cmd, int *pipe_in, int *pipe_out);
int				open_pipes(int **pipes, int pipes_count);
int				**alloc_pipes(int num);
int				check_cmd_nbr(t_cmd *cmds, int num);
char			*get_path(char *cmd, char *env_path);
int				cd_error(char **dir);
void			close_pipes(int **pipes, int pipes_count);
void			wait_child(int pids[2]);
int				check_cmd(t_cmd *cmd, int cmd_num);
#endif