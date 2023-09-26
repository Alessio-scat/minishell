/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:18:19 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/22 14:19:47 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	add_cmd(char *s, t_cmd *cmd);

void	skip_word(char *line, t_cmd *cmd)
{
	if (line[cmd->i + 1] == '<' || line[cmd->i + 1] == '>')
		cmd->i++;
	count_quote(line[cmd->i], cmd);
	cmd->i++;
	count_quote(line[cmd->i], cmd);
	if (line[cmd->i] == ' ')
		skip_space(line, &cmd->i);
	count_quote(line[cmd->i], cmd);
	if (line[cmd->i] == '\'' || line[cmd->i] == '\"')
	{
		cmd->i++;
		while (line[cmd->i])
		{
			if (cmd->count_dquote % 2 == 0 && cmd->count_squote % 2 == 0
				&& line[cmd->i] == ' ' && line[cmd->i])
				break ;
			count_quote(line[cmd->i], cmd);
			cmd->i++;
		}
	}
	else
	{
		while (line[cmd->i] && line[cmd->i] != ' ')
			cmd->i++;
	}
}

void	flag(char *line, t_cmd *cmd)
{
	skip_word(line, cmd);
	if (line[cmd->i] == ' '
		&& (line[cmd->i - 1] == '<' || line[cmd->i - 1] == '>'))
		skip_space(line, &cmd->i);
	while (line[cmd->i] && line[cmd->i] != '<' && line[cmd->i] != '>')
	{
		if (cmd->str_re)
			free(cmd->str_re);
		cmd->i++;
		cmd->lenght = 0;
		cmd->start = cmd->i;
		while (line[cmd->i] && line[cmd->i] != ' '
			&& line[cmd->i] != '<' && line[cmd->i] != '>')
		{
			cmd->lenght++;
			cmd->i++;
		}
		cmd->str_re = ft_substr(line, cmd->start, cmd->lenght);
		if (!cmd->str_re)
		{
			free(cmd->str);
			exit_malloc(cmd);
		}
		add_cmd(cmd->str_re, cmd);
	}
}
