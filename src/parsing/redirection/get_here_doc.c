/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:15:03 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/23 09:30:00 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	verif_hdoc_quote(char *s, t_cmd *cmd);

static void	hdoc_quote(char *str, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] == '$')
		{
			if (i + 1 < len && str[i + 1] == '$')
				i++;
			else if (i + 1 < len && (str[i + 1] == '"' || str[i + 1] == '\''))
			{
				j = i;
				while (j < len)
				{
					str[j] = str[j + 1];
					j++;
				}
				len--;
			}
		}
		i++;
	}
}

void	remove_dollar(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && (line[i + 1] == '\"' || line[i + 1] == '\''))
		{
			hdoc_quote(line, ft_strlen(line) - 1);
			return ;
		}
		i++;
	}
}

static void	extract_here_doc(char *line, int *i, t_cmd *cmd)
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

static void	init_hdoc(t_cmd *cmd)
{
	cmd->count_dquote = 0;
	cmd->count_squote = 0;
	cmd->hdoc_quote = 0;
	if (cmd->cmd.del)
		free(cmd->cmd.del);
}

void	here_doc(char *line, int *i, t_cmd *cmd)
{
	char			**s;

	s = NULL;
	init_hdoc(cmd);
	while (line[*i])
	{
		if (line[*i + 2] == ' ' || line[*i + 1])
		{
			(*i) += 2;
			skip_space(line, i);
		}
		count_quote(line[*i], cmd);
		extract_here_doc(line, i, cmd);
		cmd->cmd.del = ft_substr(line, cmd->start, cmd->lenght + 1);
		if (!cmd->cmd.del)
			exit_malloc(cmd);
		remove_dollar(cmd->cmd.del);
		s = ft_split(cmd->cmd.del, '\0');
		if (!s)
			exit_malloc(cmd);
		verif_hdoc_quote(cmd->cmd.del, cmd);
		add_redir(s, &cmd->here_doc_test, 'h', cmd);
		break ;
	}
}
