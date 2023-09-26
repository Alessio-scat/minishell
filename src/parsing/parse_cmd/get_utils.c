/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:18:56 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/23 13:29:53 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	is_redirection(char *line, t_cmd *cmd)
{
	int	x;

	x = 0;
	cmd->count_squote = 0;
	cmd->count_dquote = 0;
	while (line[x])
	{
		if (line[x] == '\'')
			cmd->count_squote++;
		if (line[x] == '\"')
			cmd->count_dquote++;
		if ((line[x] == '<' || line[x] == '>')
			&& (cmd->count_squote % 2 == 0 && cmd->count_dquote % 2 == 0))
			cmd->count++;
		x++;
	}
}

static void	free_tmp(t_cmd *cmd, char *s, int i, char *tmp)
{
	if (i == 0)
	{
		free(cmd->string_redir);
		free(s);
	}
	if (i == 1)
	{
		free(tmp);
		free(s);
		free(cmd->str);
	}
	if (i == 2)
	{
		free(s);
		free(tmp);
	}
	exit_malloc(cmd);
}

static void	free_add_cmd(t_cmd *cmd, char *s, char *tmp3, char *tmp2)
{
	free(s);
	free(tmp3);
	free(tmp2);
	exit_malloc(cmd);
}

static void	free_first_try(t_cmd *cmd, char *tmp3, char *s)
{
	cmd->i_cmd++;
	tmp3 = ft_substr(s, 0, ft_strlen(s));
	if (!tmp3)
		free_tmp(cmd, s, 0, NULL);
	cmd->str = tmp3;
	if (cmd->string_redir)
	{
		free(cmd->string_redir);
		free(s);
	}
}

void	add_cmd(char *s, t_cmd *cmd)
{
	cmd->tp = NULL;
	cmd->tp2 = NULL;
	cmd->tp3 = NULL;
	if (s[0] == '\0')
		return ;
	if (cmd->i_cmd == 0)
		free_first_try(cmd, cmd->tp3, s);
	else
	{
		if (cmd->str)
		{
			cmd->tp = ft_substr(cmd->str, 0, ft_strlen(cmd->str));
			if (!cmd->tp)
				free_tmp(cmd, s, 1, cmd->tp3);
			free(cmd->str);
		}
		cmd->tp2 = ft_strjoin(cmd->tp, " ");
		if (!cmd->tp2)
			free_tmp(cmd, s, 2, cmd->tp);
		free(cmd->tp);
		cmd->str = ft_strjoin(cmd->tp2, s);
		if (!cmd->str)
			free_add_cmd(cmd, s, cmd->tp3, cmd->tp2);
		free(cmd->tp2);
	}
}
