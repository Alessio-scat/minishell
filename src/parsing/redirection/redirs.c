/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:50:43 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/23 11:22:50 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	here_doc(char *line, int *i, t_cmd *cmd);
void	get_out(char *line, int *i, t_cmd *cmd);
void	o_append_out(char *line, int *i, t_cmd *cmd);
void	get_infile(char *line, int *i, t_cmd *cmd);

static void	get_redir(char *line, t_cmd *cmd, int i)
{
	cmd->count_squote = 0;
	cmd->count_dquote = 0;
	while (line[i])
	{
		count_quote(line[i], cmd);
		if (line[i] == '<' && \
			(cmd->count_squote % 2 == 0 && cmd->count_dquote % 2 == 0))
		{
			if (line[i + 1] == '<')
				here_doc(line, &i, cmd);
			else
				get_infile(line, &i, cmd);
		}
		else if (line[i] == '>' \
			&& (cmd->count_squote % 2 == 0 && cmd->count_dquote % 2 == 0))
		{
			if (line[i + 1] == '>')
				o_append_out(line, &i, cmd);
			else
				get_out(line, &i, cmd);
		}
		if (line[i])
			i++;
	}
}

void	redirs(char *line, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '<' || line [i] == '>')
		{
			get_redir(line, cmd, 0);
			break ;
		}
	}
}
