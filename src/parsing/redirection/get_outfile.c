/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_outfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:58:58 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/23 09:34:21 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	extract_outfile_append(char *line, int *i, t_cmd *cmd)
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

static	void	extract_outfile(char *line, int *i, t_cmd *cmd)
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

void	get_out(char *line, int *i, t_cmd *cmd)
{
	char			**s;

	s = NULL;
	cmd->count_dquote = 0;
	cmd->count_squote = 0;
	if (cmd->cmd.outfile)
		free(cmd->cmd.outfile);
	while (line[*i])
	{
		if (line[*i + 1] == ' ' || line[*i] == '>')
		{
			(*i)++;
			skip_space(line, i);
		}
		count_quote(line[*i], cmd);
		extract_outfile(line, i, cmd);
		cmd->cmd.outfile = ft_substr(line, cmd->start, cmd->lenght + 1);
		if (!cmd->cmd.outfile)
			exit_malloc(cmd);
		s = ft_split(cmd->cmd.outfile, '\0');
		if (!s)
			exit_malloc(cmd);
		add_redir(s, &cmd->out, 'o', cmd);
		break ;
	}
}

void	o_append_out(char *line, int *i, t_cmd *cmd)
{
	char			**s;

	s = NULL;
	cmd->count_dquote = 0;
	cmd->count_squote = 0;
	if (cmd->cmd.out_append)
		free(cmd->cmd.out_append);
	while (line[*i])
	{
		if (line[*i + 2] == ' ' || line[*i + 1])
		{
			(*i) += 2;
			skip_space(line, i);
		}
		count_quote(line[*i], cmd);
		extract_outfile_append(line, i, cmd);
		cmd->cmd.out_append = ft_substr(line, cmd->start, cmd->lenght + 1);
		if (!cmd->cmd.out_append)
			exit_malloc(cmd);
		s = ft_split(cmd->cmd.out_append, '\0');
		if (!s)
			exit_malloc(cmd);
		add_redir(s, &cmd->out, 'a', cmd);
		break ;
	}
}
