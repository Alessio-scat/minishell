/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:43:50 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/25 10:47:51 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_outfile(t_pipex *pipex, t_cmd *cmd, t_lst *cmds)
{
	if (pipex->num_pipe > 1 && cmd->tab_out[pipex->i] != 1000 && cmds->next)
	{
		while (cmd->tab_out[pipex->i] < 0)
			pipex->i++;
		ft_total_out(cmd, pipex);
		ft_open_fd3(pipex, cmd);
		if (dup2(pipex->fd3, 1) < 0)
			exit(1);
	}
}

void	ft_no_last_cmd(t_lst *cmds, t_pipex *pipex, int i, t_cmd *cmd)
{
	if (cmds->next)
	{
		if (ft_open_in(cmd, pipex) == 1)
			exit(1);
		if (pipex->fd1 >= 0 && i == 0)
		{
			if (dup2(pipex->fd1, STDIN_FILENO) < 0)
				exit(1);
		}
		if (dup2(pipex->pipefd[i + 1], 1) < 0)
			exit(1);
	}
	else if (pipex->num_pipe == 1)
	{
		if (pipex->fd1 < 0)
		{
			if (ft_open_in(cmd, pipex) == 1)
			{
				free_exec_child(cmd, pipex, cmd->tmp_path);
				exit(1);
			}
		}
		if (pipex->fd1 >= 0)
			dup2(pipex->fd1, 0);
	}
}

void	ft_no_first_cmd(t_lst *cmds, t_pipex *pipex, int i, t_cmd *cmd)
{
	if (i != 0)
	{
		if (cmds->next == NULL && cmd->tab_out[pipex->i] > 0
			&& cmd->tab_out[pipex->i] != 1000)
		{
			ft_total_out(cmd, pipex);
			ft_open_out(cmd, pipex);
			if (dup2(pipex->fd2, 1) < 0)
				exit(1);
		}
		if (dup2(pipex->pipefd[i - 2], 0) < 0)
			exit(1);
	}
	else if (pipex->num_pipe == 1 && cmd->tab_out[pipex->i] > 0
		&& cmd->tab_out[pipex->i] != 1000)
	{
		ft_total_out(cmd, pipex);
		ft_open_out(cmd, pipex);
		if (dup2(pipex->fd2, 1) < 0)
		{
			free_exec_child(cmd, pipex, cmd->tmp_path);
			exit(1);
		}
	}
}

static int	pid_where(t_pipex *p, t_parsing *path, char *envp[], pid_t pid)
{
	if (pid == 0)
		loop_exec(p->cmd, p, envp, path);
	if (pid < 0)
		wrong_pid(p);
	if (p->cmd->commands->next == NULL)
		return (1);
	return (0);
}

void	ft_pipex_bonus2(t_pipex *p, t_cmd *cmd, char *envp[], t_parsing *path)
{
	pid_t	pid;
	int		*pipefd;

	pipefd = malloc(sizeof(int) * (2 * p->num_pipe));
	if (!pipefd)
		exit (-2);
	p->pipefd = pipefd;
	fill_pipe(p);
	init_pipe(p, cmd, path);
	while (cmd->tab_out[p->i] < 0 && cmd->tab_out[p->i] && cmd->commands)
		p->i++;
	while (cmd->commands && cmd->export != 0)
	{
		pid = fork();
		signal(SIGQUIT, ms_handle_sigquit);
		signal(SIGINT, ms_handle_fork);
		if (pid_where(p, path, envp, pid) == 1)
			break ;
		path = path->next;
		cmd->commands = cmd->commands->next;
		incrementation_exec(cmd, p);
	}
	pid = 0;
	verif_file_signal(cmd, p, pid);
}
