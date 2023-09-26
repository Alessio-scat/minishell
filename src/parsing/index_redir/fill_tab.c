/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:27:06 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 10:54:44 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	is_cmd_or_not(char *line, int *is_cmd);

static void	init_var(int *count, int *y, int *is_cmd, char *s)
{
	*count = 0;
	*y = 0;
	*is_cmd = 0;
	is_cmd_or_not(s, is_cmd);
}

static void	incrementation(int *count, int *y, int i)
{
	if (i == 0)
	{
		(*count)++;
		*y += 2;
	}
	if (i == 1)
	{
		(*count)++;
		(*y)++;
	}
}

static void	fill_tab_out(t_cmd *cmd, int count, int is_cmd, int *x)
{
	if (count == 0)
		cmd->tab_out[*x] = 1000;
	else if (is_cmd == 1)
		cmd->tab_out[*x] = count;
	else
		cmd->tab_out[*x] = (-1) * count;
	(*x)++;
}

static void	init_var_fill_tab(t_cmd *cmd, int *i, int *x)
{
	*i = -1;
	*x = 0;
	cmd->count_squote = 0;
	cmd->count_dquote = 0;
}

void	fill_tab(char **s, t_cmd *cmd)
{
	int	i;
	int	count;
	int	y;
	int	x;
	int	is_cmd;

	init_var_fill_tab(cmd, &i, &x);
	while (s[++i])
	{
		init_var(&count, &y, &is_cmd, s[i]);
		while (s[i][y])
		{
			count_quote(s[i][y], cmd);
			if (s[i][y] == '>' && s[i][y + 1] == '>' &&
				(cmd->count_squote % 2 == 0 && cmd->count_dquote % 2 == 0))
				incrementation(&count, &y, 0);
			else if (s[i][y] == '>' &&
				(cmd->count_squote % 2 == 0 && cmd->count_dquote % 2 == 0))
				incrementation(&count, &y, 1);
			else
				y++;
		}
		fill_tab_out(cmd, count, is_cmd, &x);
	}
	cmd->tab_out[x] = 0;
}
