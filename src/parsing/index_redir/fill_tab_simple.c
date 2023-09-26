/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:27:02 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 10:54:26 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	is_cmd_or_not(char *line, int *is_cmd);

static void	init_var_fill_simple(int *i, int *count, int *x, int *is_cmd)
{
	*i = 0;
	*count = 0;
	*x = 0;
	*is_cmd = 0;
}

static	void	init_tab(t_cmd *cmd, char *line, int *is_cmd)
{
	cmd->count_squote = 0;
	cmd->count_dquote = 0;
	cmd->tab_out = NULL;
	cmd->tab_out = malloc(sizeof(int) * (1 + 1));
	if (!cmd->tab_out)
		exit_malloc(cmd);
	is_cmd_or_not(line, is_cmd);
}

static void	incrementation(int *count, int *i, int y)
{
	if (y == 0)
	{
		(*count)++;
		*i += 2;
	}
	if (y == 1)
	{
		(*count)++;
		(*i)++;
	}
}

static void	fill_tab_simple_out(t_cmd *cmd, int count, int is_cmd, int *x)
{
	if (count == 0)
		cmd->tab_out[*x] = 1000;
	else if (is_cmd == 1)
		cmd->tab_out[*x] = count;
	else
		cmd->tab_out[*x] = (-1) * count;
	(*x)++;
}

void	fill_simple_tab(char *line, t_cmd *cmd)
{
	int	i;
	int	count;
	int	x;
	int	is_cmd;

	init_var_fill_simple(&i, &count, &x, &is_cmd);
	init_tab(cmd, line, &is_cmd);
	while (line[i])
	{
		count_quote(line[i], cmd);
		if (line[i] == '>' && line[i + 1] == '>' && \
			(cmd->count_squote % 2 == 0 && cmd->count_dquote % 2 == 0))
			incrementation(&count, &i, 0);
		else if (line[i] == '>' && \
			(cmd->count_squote % 2 == 0 && cmd->count_dquote % 2 == 0))
			incrementation(&count, &i, 1);
		else
			i++;
	}
	fill_tab_simple_out(cmd, count, is_cmd, &x);
	cmd->tab_out[x] = 0;
	i++;
}
