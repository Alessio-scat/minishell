/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:05:26 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/25 11:32:44 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	free_array(char **array, int i)
{
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_free_join(t_pipex *pipex)
{
	free_array(pipex->mycmd, 0);
	free_array(pipex->split_path, 0);
	ft_close(pipex);
	exit(-2);
}

void	ft_free_all(t_pipex *pipex)
{
	if (pipex->split_path != NULL)
		free_array(pipex->split_path, 0);
	if (pipex->mycmd != NULL)
		free_array(pipex->mycmd, 0);
}

void	free_exec(t_cmd *cmd, t_pipex *pipex, t_parsing *path)
{
	ft_free_all(pipex);
	free(cmd->tab_out);
	if (cmd->s_builtins)
		free(cmd->s_builtins);
	free(cmd->builtpos);
	if (cmd->commands)
	{
		free_path(&path);
		free_cmd(&cmd->tmp, cmd);
	}
	if (cmd->old_stdout)
		close(cmd->old_stdout);
	free_redirec(&cmd->cmd);
	free_cmd(&cmd->in, cmd);
	free_cmd(&cmd->tmp_out, cmd);
	free_cmd(&cmd->tmp_here, cmd);
	if (pipex->pipefd)
		free(pipex->pipefd);
}

void	free_exec_child(t_cmd *cmd, t_pipex *pipex, t_parsing *path)
{
	ft_free_all(pipex);
	free(cmd->tab_out);
	if (cmd->s_builtins)
		free(cmd->s_builtins);
	free(cmd->builtpos);
	free_path(&path);
	free_cmd(&cmd->tmp, cmd);
	free_2d(cmd->env);
	free_export(&cmd->ex);
	if (cmd->tmppwd)
		free(cmd->tmppwd);
	if (cmd->old_stdout >= 0)
		close(cmd->old_stdout);
	free_redirec(&cmd->cmd);
	free_cmd(&cmd->in, cmd);
	free_cmd(&cmd->tmp_out, cmd);
	free_cmd(&cmd->tmp_here, cmd);
	ft_close(pipex);
	if (pipex->pipefd)
		free(pipex->pipefd);
}
