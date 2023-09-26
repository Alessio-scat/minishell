/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuction_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:25:22 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/12 10:58:41 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	skip_space(char *line, int *i)
{
	while (line[*i] && line[*i] == ' ')
	{
		(*i)++;
	}
}

void	free_2d(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i])
		{
			free(s[i]);
			i++;
		}
	}
	free(s);
}

char	*remove_tab(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
	return (line);
}

void	count_quote(char c, t_cmd *cmd)
{
	if (c == '\'')
		cmd->count_squote++;
	if (c == '\"')
		cmd->count_dquote++;
}

void	verif_hdoc_quote(char *s, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			cmd->hdoc_quote++;
		i++;
	}
}
