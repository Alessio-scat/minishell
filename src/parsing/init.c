/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:31:18 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 09:57:24 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	init_get_cmd(t_cmd *cmd)
{
	cmd->dollar = NULL;
	cmd->i = 0;
	cmd->start = 0;
	cmd->lenght = 0;
	cmd->string_redir = NULL;
	cmd->count = 0;
	cmd->flag = NULL;
	cmd->content = NULL;
	cmd->str = NULL;
	cmd->is_variable = 0;
	cmd->d.result = NULL;
	cmd->str_re = NULL;
}

void	init_param(t_cmd *cmd)
{
	cmd->here_doc_test = NULL;
	cmd->commands = NULL;
	cmd->out = NULL;
	cmd->in = NULL;
	cmd->cmd.del = NULL;
	cmd->cmd.infile = NULL;
	cmd->cmd.out_append = NULL;
	cmd->cmd.outfile = NULL;
	cmd->nbr_cmd = 0;
	cmd->i_cmd = 0;
	cmd->verifbuilt = 0;
}

void	init_quote(t_cmd *cmd)
{
	cmd->index = 0;
	cmd->count_dquote = 0;
	cmd->count_squote = 0;
	cmd->len = 0;
}

void	init_struct_dollar(t_cmd *cmd)
{
	cmd->d.a = 0;
	cmd->d.tmp = NULL;
	cmd->d.variable = NULL;
	cmd->d.resultfin = NULL;
	cmd->d.quote = 0;
	cmd->d.dquote = 0;
	cmd->d.qpos = 0;
	cmd->d.dpos = 0;
}

void	initialize_cmd_struct(t_cmd *cmd, t_export *export)
{
	cmd->exit = 0;
	cmd->nbr_cmd = 0;
	cmd->content = NULL;
	cmd->old_stdout = 0;
	cmd->tmppwd = ft_builtin_pwd('n', export);
}
