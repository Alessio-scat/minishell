/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:57:20 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 11:08:22 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	my_controld_free(t_export **export, t_cmd *cmd)
{
	printf("exit\n");
	free_export(export);
	if (cmd->tmppwd)
		free(cmd->tmppwd);
	if (cmd->old_stdout >= 0)
		close(cmd->old_stdout);
	exit(g_status);
}

void	exit_free(t_cmd *cmd)
{
	shlvl(cmd->ex, 'a', cmd);
	free_export(&cmd->ex);
	free_array(cmd->env, 0);
	if (cmd->tmppwd)
		free(cmd->tmppwd);
	free_cmd(&cmd->commands, cmd);
	free(cmd->builtpos);
	if (cmd->s_builtins)
		free(cmd->s_builtins);
	if (cmd->old_stdout >= 0)
		close(cmd->old_stdout);
	free(cmd->tab_out);
	free_redirec(&cmd->cmd);
	free_cmd(&cmd->in, cmd);
	free_cmd(&cmd->out, cmd);
	free_cmd(&cmd->here_doc_test, cmd);
}

void	free_execute(t_cmd *cmd)
{
	free(cmd->tab_out);
	if (cmd->s_builtins)
		free(cmd->s_builtins);
	free(cmd->builtpos);
	free_cmd(&cmd->commands, cmd);
	if (cmd->old_stdout >= 0)
		close(cmd->old_stdout);
	free_redirec(&cmd->cmd);
	free_cmd(&cmd->in, cmd);
	free_cmd(&cmd->out, cmd);
	free_cmd(&cmd->here_doc_test, cmd);
}

void	exit_malloc(t_cmd *cmd)
{
	shlvl(cmd->ex, 'a', cmd);
	free_export(&cmd->ex);
	free_array(cmd->env, 0);
	if (cmd->tmppwd)
		free(cmd->tmppwd);
	if (cmd->s_builtins)
		free(cmd->s_builtins);
	if (cmd->old_stdout >= 0)
		close(cmd->old_stdout);
	free(cmd->tab_out);
	free_redirec(&cmd->cmd);
	free_cmd(&cmd->in, cmd);
	free_cmd(&cmd->out, cmd);
	free_cmd(&cmd->here_doc_test, cmd);
	exit(-2);
}

void	free_dollar(t_cmd *cmd, char *tmp, int i)
{
	if (i == 0)
		free(cmd->d.resultfin);
	if (i == 1)
	{
		free(cmd->d.variable);
		free(tmp);
	}
	if (i == 2)
		free(tmp);
	if (i == 3)
	{
		free(cmd->d.variable);
		free(tmp);
		free(cmd->d.result);
	}
	exit_malloc(cmd);
}
