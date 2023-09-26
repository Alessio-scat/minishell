/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:29:24 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/22 15:23:05 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	is_redirection(char *line, t_cmd *cmd);
void	add_cmd(char *s, t_cmd *cmd);
void	flag(char *line, t_cmd *cmd);

static void	cmd_simple(t_cmd *cmd, char *line)
{
	int	y;

	y = -1;
	while (line[++y])
	{
		if (line[y] == ' ')
			skip_space(line, &y);
		cmd->content = ft_split_no_quote(line, ' ');
		if (!cmd->content)
			exit_malloc(cmd);
		create_node(cmd->content, &cmd->commands, cmd);
		break ;
	}
}

static void	first_cmd(char *line, t_cmd *cmd)
{
	char	*tmp;

	tmp = NULL;
	if (line[cmd->i] == ' ')
		skip_space(line, &cmd->i);
	if (line[cmd->i] && line[cmd->i] != '<' && line[cmd->i] != '>')
	{
		cmd->start = cmd->i;
		cmd->lenght = 0;
		while (line[cmd->i] && line[cmd->i] != '<' && line[cmd->i] != '>')
		{
			cmd->lenght++;
			cmd->i++;
		}
		cmd->string_redir = ft_substr(line, cmd->start, cmd->lenght);
		if (!cmd->string_redir)
			exit_malloc(cmd);
		tmp = ft_substr(cmd->string_redir, 0, ft_strlen(cmd->string_redir));
		if (!tmp)
		{
			free(cmd->string_redir);
			exit_malloc(cmd);
		}
		add_cmd(tmp, cmd);
	}
}

static int	extract_command(char *line, t_cmd *cmd)
{
	cmd->count_squote = 0;
	cmd->count_dquote = 0;
	first_cmd(line, cmd);
	while (line[cmd->i])
	{
		count_quote(line[cmd->i], cmd);
		if (line[cmd->i] == '<' || line[cmd->i] == '>')
			flag(line, cmd);
		if (cmd->str_re)
		{
			free(cmd->str_re);
			cmd->str_re = NULL;
		}
	}
	if (!cmd->str)
		return (1);
	cmd->flag = ft_split_no_quote(cmd->str, ' ');
	if (!cmd->flag)
	{
		free(cmd->str);
		exit_malloc(cmd);
	}
	create_node(cmd->flag, &cmd->commands, cmd);
	return (0);
}

void	get_cmd(char *line, t_cmd *cmd)
{
	init_get_cmd(cmd);
	is_redirection(line, cmd);
	line = see_dollar(line, cmd);
	if (line == NULL)
		return ;
	if (cmd->count != 0)
	{
		if (extract_command(line, cmd) == 1)
			return ;
	}
	else
		cmd_simple(cmd, line);
	if (cmd->str)
		free(cmd->str);
	if (cmd->is_variable == 1)
		free(line);
}
