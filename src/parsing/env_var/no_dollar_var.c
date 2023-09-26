/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_dollar_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:51:15 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/22 15:40:43 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	position_quote(char *line, t_cmd *cmd, int *i);
void	free_dollar(t_cmd *cmd, char *tmp, int i);

static void	incre(t_cmd *cmd, char *tmp)
{
	cmd->d.a++;
	if (cmd->d.variable)
		free(cmd->d.variable);
	if (tmp)
		free(tmp);
	cmd->is_variable = 1;
}

static void	extract_word_no_var(t_cmd *cmd, char *line, int *i, char *tmp)
{
	cmd->start = *i;
	cmd->lenght = 0;
	if (cmd->d.quote % 2 == 0)
	{
		while (line[*i] && line[*i] != '$' && line[*i] != '\\')
			position_quote(line, cmd, i);
	}
	else
	{
		(*i)++;
		cmd->lenght++;
		while (line[*i] && line[*i] != '$' && line[*i] != '\\')
			position_quote(line, cmd, i);
	}
	cmd->d.variable = ft_substr(line, cmd->start, cmd->lenght);
	if (!cmd->d.variable)
		free_dollar(cmd, tmp, 2);
}

void	no_dollar_var(char *line, t_cmd *cmd, int *i)
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
	extract_word_no_var(cmd, line, i, tmp);
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
	incre(cmd, tmp);
}
