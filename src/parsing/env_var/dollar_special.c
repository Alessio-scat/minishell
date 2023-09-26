/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:59:40 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 10:55:00 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	position_quote(char *line, t_cmd *cmd, int *i);

static void	extract_word(t_cmd *cmd, char *line, int *i, char *tmp)
{
	cmd->lenght = 0;
	cmd->start = *i;
	while (line[*i] && line[*i] != ' ' && \
		line[*i] != '\\' && line[*i + 1] != '$')
	{
		cmd->lenght++;
		(*i)++;
	}
	cmd->d.variable = ft_substr(line, cmd->start, cmd->lenght);
	if (!cmd->d.variable)
		free_dollar(cmd, tmp, 0);
}

static void	free_var(t_cmd *cmd, char *tmp)
{
	cmd->d.a++;
	cmd->is_variable = 1;
	if (cmd->d.variable)
		free(cmd->d.variable);
	if (tmp)
		free(tmp);
}

void	special_case(char *line, t_cmd *cmd, int *i)
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
	extract_word(cmd, line, i, tmp);
	if (cmd->d.a > 0 && tmp)
	{
		cmd->d.resultfin = ft_strjoin(tmp, cmd->d.variable);
		if (!cmd->d.resultfin)
			free_dollar(cmd, tmp, 1);
	}
	else
	{
		cmd->d.resultfin = ft_substr(cmd->d.variable, \
		0, ft_strlen(cmd->d.variable));
		if (!cmd->d.resultfin)
			free_dollar(cmd, tmp, 1);
	}
	free_var(cmd, tmp);
}

static void	extract_word_slash(t_cmd *cmd, char *line, int *i, char *tmp)
{
	*i += 2;
	cmd->lenght = 0;
	cmd->start = *i - 1;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\\' && line[*i] != '$')
		position_quote(line, cmd, i);
	cmd->d.variable = ft_substr(line, cmd->start, cmd->lenght + 1);
	if (!cmd->d.variable)
		free_dollar(cmd, tmp, 0);
}

void	dollar_slash(char *line, t_cmd *cmd, int *i)
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
	extract_word_slash(cmd, line, i, tmp);
	if (cmd->d.a > 0 && tmp)
	{
		cmd->d.resultfin = ft_strjoin(tmp, cmd->d.variable);
		if (!cmd->d.resultfin)
			free_dollar(cmd, tmp, 1);
	}
	else
	{
		cmd->d.resultfin = ft_substr(cmd->d.variable, 0, \
			ft_strlen(cmd->d.variable));
		if (!cmd->d.resultfin)
			free_dollar(cmd, tmp, 1);
	}
	free_var(cmd, tmp);
}
