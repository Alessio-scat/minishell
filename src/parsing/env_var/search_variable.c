/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:45:28 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/22 16:32:21 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	d_questionning(t_cmd *cmd, char *code_error, int *i);
void	dollar_slash(char *line, t_cmd *cmd, int *i);
void	special_case(char *line, t_cmd *cmd, int *i);
void	dollar_simple(t_cmd *cmd, int *i);
void	dollar_with_variable(char *line, t_cmd *cmd, int *i);
void	no_dollar_var(char *line, t_cmd *cmd, int *i);

char	*see_dollar(char *s, t_cmd *cmd)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '$' && (s[i + 1] == '>' || s[i + 1] == '<'))
			return (s);
		if (s[i] == '$' || (s[i] == '\\' && s[i + 1] == '$'))
		{
			cmd->dollar = search_variable(s, cmd);
			count++;
			break ;
		}
		i++;
	}
	if (count == 0)
		return (s);
	else
		return (cmd->dollar);
}

static void	extract_dollar(t_cmd *cmd, char *code_error, int *i, char *line)
{
	if ((line[*i] == '$' && line[*i + 1] == '?'))
		d_questionning(cmd, code_error, i);
	if (line[*i] == '$' && (line[*i + 1] == ':' || line[*i + 1] == '='))
		special_case(line, cmd, i);
	if (line[*i] == '$' && (line[*i + 1] == '\0' || line[*i + 1] == ' ' \
		|| (line[*i + 1] == '\"' && cmd->d.dquote % 2 == 1)))
		dollar_simple(cmd, i);
	if (line[*i] == '$' && (line[*i + 1] >= '0' && line[*i + 1] <= '9'))
		(*i) += 2;
	if (*i > 0)
	{
		if (((line[*i] == '$' && line[*i + 1] != ' ' && line[*i - 1] != '\\' \
		&& cmd->d.quote % 2 == 0) || (cmd->d.quote % 2 == 1 \
		&& cmd->d.dquote % 2 == 1 && line[*i + 1] != '?' )))
			dollar_with_variable(line, cmd, i);
	}
	else
		if (((line[*i] == '$' && line[*i + 1] != ' ' && cmd->d.quote % 2 == 0) \
			|| (cmd->d.quote % 2 == 1 && cmd->d.dquote % 2 == 1)))
			dollar_with_variable(line, cmd, i);
	if (line[*i] == '\\' && line[*i + 1] == '$')
		dollar_slash(line, cmd, i);
	if ((line[*i] != '$' && line[*i] != '\\') || (cmd->d.quote % 2 != 0 && \
		(line[*i] == '$' || line[*i] == '\'')))
		no_dollar_var(line, cmd, i);
}	

char	*search_variable(char *line, t_cmd *cmd)
{
	int				i;
	char			*code_error;

	i = 0;
	code_error = NULL;
	init_struct_dollar(cmd);
	while (line[i])
		extract_dollar(cmd, code_error, &i, line);
	return (cmd->d.resultfin);
}
