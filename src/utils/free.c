/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:51:30 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 11:32:22 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_export(t_export **cmd)
{
	t_export	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		free((*cmd)->content);
		free((*cmd)->variable);
		free(*cmd);
		*cmd = tmp;
	}
	free(*cmd);
}

void	free_path(t_parsing **cmd)
{
	t_parsing	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		free((*cmd)->pathcmd);
		free(*cmd);
		(*cmd) = tmp;
	}
	free(*cmd);
}

void	free_cmd(t_lst **cmd, t_cmd *c)
{
	t_lst	*tmp;

	(void)c;
	while ((*cmd))
	{
		tmp = (*cmd)->next;
		free_2d((*cmd)->cmd);
		free((*cmd));
		(*cmd) = tmp;
	}
	free((*cmd));
}

void	free_redirec(t_redir *cmd)
{
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->del)
		free(cmd->del);
	if (cmd->outfile)
	{
		free(cmd->outfile);
	}
	if (cmd->out_append)
		free(cmd->out_append);
}
