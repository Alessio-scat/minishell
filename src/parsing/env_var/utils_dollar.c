/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:03:58 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/23 14:47:32 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	init_var(t_cmd *cmd, int *i)
{
	*i = -1;
	cmd->tmp_var = NULL;
}

char	*is_variable(char *variable, t_cmd *cmd)
{
	int		i;

	init_var(cmd, &i);
	while (cmd->ex)
	{
		if (ft_strncmp(cmd->ex->variable, variable, ft_strlen(variable)) == 0)
		{
			if (ft_strncmp(cmd->ex->variable, variable, \
			ft_strlen(cmd->ex->variable)) == 0)
			{
				cmd->is_variable = 1;
				if (!cmd->ex->content)
					return (NULL);
				cmd->tmp_var = ft_substr(cmd->ex->content, 0, \
					ft_strlen(cmd->ex->content));
				return (cmd->tmp_var);
			}
		}
		cmd->ex = cmd->ex->next;
	}
	while (variable[++i])
		if (variable[i] == '\'' || variable[i] == '\"')
			return (variable);
	return (NULL);
}

void	position_quote(char *line, t_cmd *cmd, int *i)
{
	if (line[*i] == '\'')
	{
		cmd->d.qpos = *i;
		cmd->d.quote++;
	}
	if (line[*i] == '\"')
	{
		cmd->d.dpos = *i;
		cmd->d.dquote++;
	}
	(*i)++;
	cmd->lenght++;
}
