/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:31:10 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/16 15:52:51 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	simple_op(char *line);
int	pipeline_multiple(char *line);
int	redir_err_newline(char *line);
int	redir_err(char *line);
int	pipeline_err(char *line);

static int	count_quotes_check(char *line)
{
	int	sq;
	int	dq;
	int	i;

	sq = 0;
	dq = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			dq++;
		if (line[i] == '\'')
			sq++;
		i++;
	}
	if (dq % 2 == 0 && sq % 2 == 0)
		return (0);
	else
	{
		ft_putstr_fd
			("Our minishell does not accept quotes that are not close\n", 2);
		return (1);
	}
}

int	check_syntax(char *line)
{
	if (count_quotes_check(line) == 1)
		return (1);
	if (simple_op(line) == 1)
		return (1);
	if (pipeline_err(line) == 1)
		return (1);
	if (redir_err(line) == 1)
		return (1);
	if (redir_err_newline(line) == 1)
		return (1);
	if (pipeline_multiple(line) == 1)
		return (1);
	return (0);
}
