/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_questioning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:46 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/23 09:13:52 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	free_questionning(t_cmd *cmd, char *code_error, char *tmp, int i)
{
	if (i == 0)
		free(cmd->d.resultfin);
	if (i == 1)
		free(tmp);
	if (i == 2)
	{
		free(code_error);
		free(tmp);
	}
	exit_malloc(cmd);
}

static	void	simple_questionning(t_cmd *cmd, char *code_error, char *tmp)
{
	cmd->d.resultfin = ft_strjoin(tmp, code_error);
	if (!cmd->d.resultfin)
		free_questionning(cmd, code_error, tmp, 2);
	free(tmp);
	free(code_error);
}

static void	incre(t_cmd *cmd, int *i)
{
	cmd->d.a++;
	cmd->is_variable = 1;
	if (cmd->d.dpos < cmd->d.qpos && cmd->d.dpos != 0 && cmd->d.qpos != 0)
		(*i)++;
	else
		(*i) += 2;
}

void	d_questionning(t_cmd *cmd, char *code_error, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (cmd->d.dpos > cmd->d.qpos && cmd->d.qpos != 0)
		return ;
	if (cmd->d.resultfin)
	{
		tmp = ft_substr(cmd->d.resultfin, 0, ft_strlen(cmd->d.resultfin));
		if (!tmp)
			free_questionning(cmd, code_error, tmp, 0);
		free(cmd->d.resultfin);
	}
	code_error = ft_itoa(g_status);
	if (!code_error)
		free_questionning(cmd, code_error, tmp, 1);
	if (cmd->d.a > 0 && tmp)
		simple_questionning(cmd, code_error, tmp);
	else
	{
		cmd->d.resultfin = ft_substr(code_error, 0, ft_strlen(code_error));
		if (!cmd->d.resultfin)
			free_questionning(cmd, code_error, tmp, 2);
		free(code_error);
	}
	incre(cmd, i);
}
