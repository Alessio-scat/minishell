/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:42:19 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/23 09:44:25 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	init_exec(t_pipex *pipex, t_cmd *cmd)
{
	pipex->split_path = NULL;
	pipex->mycmd = NULL;
	pipex->join_cmd = NULL;
	pipex->pathcmd = NULL;
	pipex->pipefd = 0;
	pipex->fd1 = -1;
	pipex->fd2 = -1;
	pipex->fd3 = -1;
	pipex->num_pipe = cmd->nbr_cmd;
	cmd->tmp_out = cmd->out;
	cmd->tmp = cmd->commands;
	cmd->tmp_here = cmd->here_doc_test;
}

void	init_pipe(t_pipex *pipex, t_cmd *cmd, t_parsing *path)
{
	cmd->tmp_path = path;
	cmd->y = 0;
	cmd->i = 0;
	pipex->i = 0;
}
