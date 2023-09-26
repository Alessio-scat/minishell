/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:04:00 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/23 09:32:19 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	extract_infile(char *line, int *i, t_cmd *cmd)
{
	cmd->start = *i;
	cmd->lenght = 0;
	if (line[*i] == '\'' || line[*i] == '\"')
	{
		(*i)++;
		while (line[*i])
		{
			if (cmd->count_dquote % 2 == 0 && cmd->count_squote % 2 == 0
				&& line[*i] == ' ' && line[*i])
				break ;
			count_quote(line[*i], cmd);
			cmd->lenght++;
			(*i)++;
		}
	}
	else
	{
		while (line[*i] && line[*i + 1] != ' ' && line[*i + 1] != '|'
			&& line[*i + 1] != '>' && line[*i + 1] != '<')
		{
			cmd->lenght++;
			(*i)++;
		}
	}
}

void	get_infile(char *line, int *i, t_cmd *cmd)
{
	char				**s;

	s = NULL;
	cmd->count_dquote = 0;
	cmd->count_squote = 0;
	if (cmd->cmd.infile)
		free(cmd->cmd.infile);
	while (line[*i])
	{
		if (line[*i + 1] == ' ' || line[*i] == '<')
		{
			(*i)++;
			skip_space(line, i);
		}
		count_quote(line[*i], cmd);
		extract_infile(line, i, cmd);
		cmd->cmd.infile = ft_substr(line, cmd->start, cmd->lenght + 1);
		if (!cmd->cmd.infile)
			exit_malloc(cmd);
		s = ft_split(cmd->cmd.infile, '\0');
		if (!s)
			exit_malloc(cmd);
		add_redir(s, &cmd->in, 'i', cmd);
		break ;
	}
}
