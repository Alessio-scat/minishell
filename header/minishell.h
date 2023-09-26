/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:08:22 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 11:12:27 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h> 
# include <readline/history.h>
# include  <sys/ioctl.h>

extern int	g_status;

typedef struct s_export
{
	char			*variable;
	char			*content;
	struct s_export	*next;
}					t_export;

typedef struct s_lst
{
	char			file;
	char			**cmd;
	struct s_lst	*next;
}					t_lst;

typedef struct s_redir
{
	char	*infile;
	char	*outfile;
	char	*del;
	char	*out_append;
}	t_redir;

typedef struct s_d
{
	char			*variable;
	char			*result;
	char			*resultfin;
	t_export		*tmp;
	int				quote;
	int				a;
	int				dquote;
	int				qpos;
	int				dpos;
}			t_d;

typedef struct s_parsing
{
	char				*pathcmd;
	struct s_parsing	*next;
}					t_parsing;

typedef struct t_cmd
{
	int				e;
	char			*tmp_var;
	char			*tp;
	char			*tp2;
	char			*tp3;
	char			**env;
	int				hdoc_quote;
	int				y;
	int				exit;
	int				verifbuilt;
	char			*dollar;
	t_d				d;
	int				index;
	int				count_dquote;
	int				count_squote;
	int				len;
	int				*tab_out;
	char			*string_redir;
	int				i;
	unsigned int	start;
	size_t			lenght;
	int				count;
	int				i_cmd;
	char			*str;
	char			*sauvegarde;
	int				export;
	char			*s_builtins;
	int				stop;
	char			*s;
	char			**split_line;
	int				nbr_cmd;
	char			**content;
	char			**flag;
	t_lst			*in;
	t_lst			*here_doc_test;
	t_lst			*commands;
	t_lst			*out;
	t_redir			cmd;
	t_export		*ex;
	char			*tmppwd;
	int				old_stdout;
	int				*builtpos;
	int				exitalone;
	int				is_variable;
	char			*str_re;
	t_parsing		*tmp_path;
	t_lst			*tmp2;
	t_lst			*tmp;
	t_lst			*tmp_out;
	t_lst			*tmp_here;
}	t_cmd;

typedef struct s_pipex
{
	int		i;
	int		free;
	int		fd1;
	int		fd2;
	int		fd3;
	int		total;
	int		save_out;
	int		num_pipe;
	int		*pipefd;
	char	*pathcmd;
	char	*join_cmd;
	char	**mycmd;
	char	*path;
	char	*tmp;
	int		file_here;
	char	**split_path;
	t_cmd	*cmd;
	char	*env[];
}					t_pipex;

typedef struct s_builtins
{
	int		count_dquote;
	int		count_squote;
	int		i;
	int		j;
	int		countspace;
	int		sizevariable;
	int		start;
	int		verif_n;
	int		verif_find;
	char	*var;
	t_pipex	builtfd;
}					t_builtins;

void		message_unset(int error, char *cmd, int i, t_cmd *cmdstruc);
void		message(int error, char *cmd, int i, t_cmd *cmdstruc);
void		verif_minishell(t_cmd *c, t_pipex *pipex, char *cmd);
int			modif_shlvl(int shlvl, char a);
void		get_env_malloc2(char **envtmp, t_cmd *cmd);
void		get_env_malloc(char **envtmp, t_cmd *cmd);
void		free_tmp_var(t_cmd *cmd, char **tmp_env);
void		env_malloc(char *tmp_variable, char **tmp_env, \
t_cmd *cmd, char *tmp);
void		shlvl_malloc(t_export *exp, t_cmd *cmd);
void		ft_echo(t_cmd *cmdstruc, t_builtins builtins);
void		ft_pwd(t_cmd *cmdstruc, t_export *export);
void		verif_variable(t_export *ex, int sizevar, char **var, \
t_builtins *bu);
int			ft_lst_size_export(t_export *lst);
void		print_list_exp(char **export);
void		if_built(char *cmd, t_cmd *c, int *x, int *count);
int			cd_verif(t_export *export, t_cmd *c);
void		ft_cd_cmd(t_export *export, t_cmd *cmdstruc);
int			add_export(t_export *export, t_builtins *bu, char **variable, \
char *maVariable);
void		malloc_copy_lst(char **variable, int sizevariable, \
t_export *export);
int			variable_exist(t_export *ex, int sizevar, char **var, \
t_builtins *bu);
void		free_add_export(t_export *export, char **variable, t_builtins *bu);
void		malloc_copy(char **variable, int sizevariable, t_export *export);
int			export_verif_cote(t_export *export, int sizevar, char **variable);
void		error_message_out(t_cmd *cmd, t_pipex *pi);
void		init_pipe(t_pipex *pipex, t_cmd *cmd, t_parsing *path);
void		init_exec(t_pipex *pipex, t_cmd *cmd);
void		error_message(t_cmd *cmd);
void		wrong_pid(t_pipex *pipex);
void		incrementation_exec(t_cmd *cmd, t_pipex *pipex);
void		verif_file_signal(t_cmd *cmd, t_pipex *pipex, pid_t pid);
void		ft_no_first_cmd(t_lst *cmds, t_pipex *pipex, int i, t_cmd *cmd);
void		ft_no_last_cmd(t_lst *cmds, t_pipex *pipex, int i, t_cmd *cmd);
void		ft_outfile(t_pipex *pipex, t_cmd *cmd, t_lst *cmds);
void		loop_exec(t_cmd *cmd, t_pipex *pipex, char *envp[], \
t_parsing *path);
void		fill_pipe(t_pipex *pipex);
void		free_exec_child(t_cmd *cmd, t_pipex *pipex, t_parsing *path);
void		free_exec(t_cmd *cmd, t_pipex *pipex, t_parsing *path);
void		get_env(t_export **envp, char *env[], t_cmd *cmd);
char		**ft_create_env(t_export *export, int size, t_cmd *cmd);
void		ft_builtin(char *input, char *env[], t_export *export, t_cmd *cmd);
void		ft_builtin_exit(char **args, t_cmd *cmd);
char		*ft_builtin_pwd(char c, t_export *export);
void		ft_builtin_cd(char *path);
void		ft_builtin_env(char *env[]);
void		ft_builtin_export(char *maVariable, t_export *export, \
t_builtins *built);
void		new_echo(t_cmd *cmd, t_builtins *built);
void		ft_builtin_echo(char *variable, t_export *export, \
t_builtins *built);
void		echo_dollar(char *variable, t_export *export, t_builtins *built);
void		echo_variable(t_export *exp, char *var, t_builtins *built);
void		squote(char *variable, t_builtins *built);
void		ft_builtin_unset(char *name, t_export *export);
int			ft_check_export(char *input);
void		print_export(t_export *export);
void		shlvl(t_export *export, char a, t_cmd *cmd);
t_export	*ft_lst_last(t_export *lst);
t_export	*ft_lst_new(char *content, char *variable);
void		ft_lst_add_back(t_export **lst, t_export *new);
int			ft_lst_size(t_export *lst);
void		free_stack(t_export **pile);
void		ft_free_pile(t_export *pile);
void		ft_open_fd(t_cmd *cmd, t_pipex *pipex);
void		ft_open_out(t_cmd *cmd, t_pipex *pipex);
void		ft_open_fd3(t_pipex *pi, t_cmd *c);
int			ft_open_in(t_cmd *cmd, t_pipex *pipex);
void		ft_open_out_without_cmd(t_cmd *c, t_pipex *pi);
void		ft_total_out(t_cmd *cmd, t_pipex *pipex);
t_parsing	*ft_lst_last_exec(t_parsing *lst);
t_parsing	*ft_lst_new_exec(char *pathcmd);
void		ft_lst_add_back_exec(t_parsing **lst, t_parsing *new);
int			ft_lst_size_exec(t_parsing *lst);
void		free_stack_exec(t_parsing **pile);
void		ft_free_pile_exec(t_parsing *pile);
void		ft_parsing_exec(t_pipex *pipex, char *envp[], t_lst **cmd_arg);
void		free_array(char **array, int i);
void		ft_free_all(t_pipex *pipex);
void		ft_free_join(t_pipex *pipex);
void		ft_error_message(char *str, t_pipex *pipex);
void		ft_close(t_pipex *pipex);
void		free_export(t_export **cmd);
void		free_path(t_parsing **cmd);
void		free_redirec(t_redir *cmd);
int			exec(char *envp[], t_cmd *cmd);
void		ft_fill_lst(t_lst **cmd_arg, t_pipex *pipex, \
char *envp[], t_parsing **path);
void		ft_pipex_bonus2(t_pipex *pipex, t_cmd *cmd, \
char *envp[], t_parsing *path);
int			ft_strcmp(const char *s1, const char *s2);

t_lst		*lst_last(t_lst *lst);
int			lst_add_back(t_lst **lst, t_lst *new);
t_lst		*lst_new(char **cmd);
t_lst		*lst_new_redir(char **cmd, char file);
void		create_node(char **cmds, t_lst **command, t_cmd *cmd);
void		print_list(t_lst **command);
void		print_redir(t_lst **redir);
void		add_redir(char **s, t_lst **lst, char file, t_cmd *cmd);
int			parsing(char *line, t_cmd *cmd);
int			parsepipe(char *line, t_cmd *cmd);
void		redirs(char *line, t_cmd *cmd);
int			check_syntax(char *line);
void		skip_space(char *line, int *i);
void		free_2d(char **s);
void		count_quote(char c, t_cmd *cmd);
void		free_str(char **s);
void		free_cmd(t_lst **cmd, t_cmd *c);
void		my_controld_free(t_export **export, t_cmd *cmd);
void		exit_free(t_cmd *cmd);
void		exit_malloc(t_cmd *cmd);
void		free_dollar(t_cmd *cmd, char *tmp, int i);
char		*remove_quote(char *line, int l);
int			verif_buildtins(char *line, t_cmd *cmd);
char		*dollar(char *line, t_cmd *cmd);
void		get_cmd(char *line, t_cmd *cmd);
void		init_get_cmd(t_cmd *cmd);
void		init_param(t_cmd *cmd);
void		init_quote(t_cmd *cmd);
void		init_struct_dollar(t_cmd *cmd);
void		indexage_redir(char *line, t_cmd *cmd);
char		*see_dollar(char *s, t_cmd *cmd);
char		*search_variable(char *line, t_cmd *cmd);
void		ms_handle_sigint(int sig);
void		ms_handle_sigquit(int sig);
void		ms_handle_fork(int sig);
void		ms_handle_mini(int sig);
void		ms_handle_hdoc(int sig);
void		remove_dollar(char *line);

#endif