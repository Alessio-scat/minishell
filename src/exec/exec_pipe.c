/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:43:32 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/24 16:29:31 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	fill_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->num_pipe))
	{
		if (pipe(pipex->pipefd + i * 2) < 0)
		{
			perror("pipe");
			return ;
		}
		i++;
	}
}

void	wrong_cmd(t_cmd *cmd, t_pipex *pipex, t_parsing *path)
{
	if ((cmd->commands->cmd[0][0] == '.' && cmd->commands->cmd[0][1] == '/'
		&& path->pathcmd[0] == '\0'))
		error_message(cmd);
	else if ((cmd->commands->cmd[0][0] == '.'
		&& cmd->commands->cmd[0][1] == '/'))
	{
		g_status = 126;
		ft_putstr_fd("bash: ", cmd->old_stdout);
		ft_putstr_fd(cmd->commands->cmd[0], cmd->old_stdout);
		ft_putstr_fd(": Permission denied\n", cmd->old_stdout);
	}
	else if (cmd->commands->cmd[0][0] == '/' && path->pathcmd[0] != '\0')
	{
		g_status = 126;
		ft_putstr_fd("bash: ", cmd->old_stdout);
		ft_putstr_fd(cmd->commands->cmd[0], cmd->old_stdout);
		ft_putstr_fd(": Is a directory\n", cmd->old_stdout);
	}
	else if (pipex->path && cmd->commands->cmd[0][0] != '/')
	{
		g_status = 127;
		ft_putstr_fd(cmd->commands->cmd[0], cmd->old_stdout);
		ft_putstr_fd(": command not found\n", cmd->old_stdout);
	}
}

void	loop_exec(t_cmd *cmd, t_pipex *pipex, char *envp[], t_parsing *path)
{
	ft_no_last_cmd(cmd->commands, pipex, cmd->i, cmd);
	ft_outfile(pipex, cmd, cmd->commands);
	ft_no_first_cmd(cmd->commands, pipex, cmd->i, cmd);
	ft_close(pipex);
	if (cmd->s_builtins && cmd->builtpos[cmd->y] == 1 && cmd->export != 0)
	{
		ft_builtin(cmd->s_builtins, envp, cmd->ex, cmd);
		free_exec_child(cmd, pipex, cmd->tmp_path);
		exit(0);
	}
	verif_minishell(cmd, pipex, cmd->commands->cmd[0]);
	if (cmd->commands->next == NULL && cmd->tab_out[pipex->i + 1] < 0
		&& cmd->tab_out[pipex->i] == 1000)
	{
		free_exec_child(cmd, pipex, cmd->tmp_path);
		exit(0);
	}
	else if ((execve(path->pathcmd, cmd->commands->cmd, envp) == -1
			&& cmd->builtpos[cmd->y] == 0))
	{
		wrong_cmd(cmd, pipex, path);
		free_exec_child(cmd, pipex, cmd->tmp_path);
		exit(g_status);
	}
}

void	verif_file_signal(t_cmd *cmd, t_pipex *pipex, pid_t pid)
{
	int	j;
	int	status;

	status = 0;
	if (cmd->commands)
	{
		if (ft_strncmp(cmd->commands->cmd[0], "./minishell", 11) == 0)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, ms_handle_mini);
		}
	}
	while (cmd->tab_out[++pipex->i])
	{
		ft_total_out(cmd, pipex);
		ft_open_out(cmd, pipex);
	}
	ft_close(pipex);
	j = 0;
	while (j++ < pipex->num_pipe + 1)
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ms_handle_sigint);
}

void	incrementation_exec(t_cmd *cmd, t_pipex *pipex)
{
	cmd->i += 2;
	pipex->i++;
	if (cmd->tab_out[pipex->i] < 0)
	{
		while (cmd->tab_out[pipex->i] < 0 && cmd->tab_out[pipex->i])
		{
			ft_total_out(cmd, pipex);
			ft_open_out_without_cmd(cmd, pipex);
			pipex->i++;
		}
	}
	cmd->y++;
}
