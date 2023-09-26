/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:04:28 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 10:53:46 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	g_status = 0;

void	free_execute(t_cmd *cmd);
void	initialize_cmd_struct(t_cmd *cmd, t_export *export);

static void	check_param(int argc)
{
	if (argc != 1)
	{
		printf(": ./minishell\n");
		exit (0);
	}
}

void	initialize_signals(void)
{
	signal(SIGINT, ms_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	execute_cmd(char **env_tmp, t_cmd *cmd, t_export *export, char *line)
{
	int	export_size;
	int	error;

	cmd->old_stdout = dup(1);
	export_size = ft_lst_size(export);
	env_tmp = ft_create_env(export, export_size, cmd);
	cmd->env = env_tmp;
	error = parsing(line, cmd);
	if (error == -1)
		exit_malloc(cmd);
	if ((cmd->export == 0 && cmd->s_builtins) || cmd->exitalone == 1)
		ft_builtin(cmd->s_builtins, env_tmp, cmd->ex, cmd);
	if (error != -2 && cmd->export != 0 && cmd->exitalone != 1)
		exec(env_tmp, cmd);
	else if (error != -2)
		free_execute(cmd);
	else if (error == -2)
	{
		if (cmd->old_stdout >= 0)
			close(cmd->old_stdout);
	}
	free_array(env_tmp, 0);
}

void	prompt(char *line, t_cmd cmd, t_export *export)
{
	char	**env_tmp;

	env_tmp = NULL;
	while (1)
	{
		while (line != NULL)
		{
			initialize_signals();
			cmd.exitalone = 0;
			cmd.export = 1;
			cmd.s_builtins = NULL;
			add_history(line);
			cmd.ex = export;
			execute_cmd(env_tmp, &cmd, export, line);
			free(line);
			line = readline("\033[0;36m\033[1mminishell ▸ \033[0m");
		}
		if (!line)
			my_controld_free(&export, &cmd);
		rl_clear_history();
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_cmd		cmd;
	t_export	*export;
	char		*line;

	export = NULL;
	(void)argv;
	(void)env;
	initialize_cmd_struct(&cmd, export);
	check_param(argc);
	initialize_signals();
	get_env(&export, env, &cmd);
	shlvl(export, 'u', &cmd);
	line = readline("\033[0;36m\033[1mminishell ▸ \033[0m");
	prompt(line, cmd, export);
}
