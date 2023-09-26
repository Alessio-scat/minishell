/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:57:38 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/22 16:03:21 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

char	*is_variable(char *variable, t_cmd *cmd);
void	position_quote(char *line, t_cmd *cmd, int *i);

static void	incr(t_cmd *cmd, int *i)
{
	cmd->d.a++;
	cmd->is_variable = 1;
	(*i)++;
}

void	dollar_simple(t_cmd *cmd, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (cmd->d.resultfin)
	{
		tmp = ft_substr(cmd->d.resultfin, 0, ft_strlen(cmd->d.resultfin));
		if (!tmp)
			free_dollar(cmd, tmp, 0);
		free(cmd->d.resultfin);
	}
	if (cmd->d.a > 0 && tmp)
	{
		cmd->d.resultfin = ft_strjoin(tmp, "$");
		if (!cmd->d.resultfin)
			free_dollar(cmd, tmp, 2);
		free(tmp);
	}
	else
	{
		cmd->d.resultfin = ft_strdup("$");
		if (!cmd->d.resultfin)
			free_dollar(cmd, tmp, 2);
	}
	incr(cmd, i);
}

static void	word_extract(t_cmd *cmd, char *tmp, int *i, char *line)
{
	(*i)++;
	cmd->start = *i;
	cmd->lenght = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\''
		&& line[*i] != '\"' && line[*i] != '$' && line[*i] != '\\'
		&& line[*i] != '%' && line[*i] != ']' && line[*i] != '='
		&& line[*i - 1] != '?' && line[*i] != '-')
	{
		cmd->lenght++;
		(*i)++;
	}
	cmd->d.variable = ft_substr(line, cmd->start, cmd->lenght);
	if (!cmd->d.variable)
		free_dollar(cmd, tmp, 2);
	cmd->d.tmp = cmd->ex;
	if (cmd->d.dpos > cmd->d.qpos && \
		cmd->d.dquote % 2 == 1 && cmd->d.quote % 2 == 1)
	{
		cmd->d.result = ft_substr(cmd->d.variable, 0, \
			ft_strlen(cmd->d.variable));
		if (!cmd->d.result)
			free_dollar(cmd, tmp, 1);
	}
	else
		cmd->d.result = is_variable(cmd->d.variable, cmd);
}

static void	process_with_var(t_cmd *cmd, char *tmp)
{
	if (cmd->d.a > 0 && cmd->d.result && tmp)
	{
		cmd->d.resultfin = ft_strjoin(tmp, cmd->d.result);
		if (!cmd->d.resultfin)
			free_dollar(cmd, tmp, 3);
		free(cmd->d.result);
	}
	else if (cmd->d.result)
		cmd->d.resultfin = cmd->d.result;
	else
	{
		if (tmp)
		{
			cmd->d.resultfin = ft_substr(tmp, 0, ft_strlen(tmp));
			if (!cmd->d.resultfin)
				free_dollar(cmd, tmp, 3);
			cmd->is_variable = 1;
		}
	}
}

void	dollar_with_variable(char *line, t_cmd *cmd, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (cmd->d.resultfin)
	{
		tmp = ft_substr(cmd->d.resultfin, 0, ft_strlen(cmd->d.resultfin));
		if (!tmp)
			free_dollar(cmd, tmp, 0);
		free(cmd->d.resultfin);
		cmd->d.resultfin = NULL;
	}
	word_extract(cmd, tmp, i, line);
	cmd->ex = cmd->d.tmp;
	process_with_var(cmd, tmp);
	cmd->d.a++;
	if (cmd->d.variable)
		free(cmd->d.variable);
	if (tmp)
		free(tmp);
}
