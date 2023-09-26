/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:26:46 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/23 10:33:27 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	count_pipe(char *line)
{
	int	num_pipe;
	int	i;

	num_pipe = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '|')
		{
			num_pipe++;
		}
	}
	return (num_pipe);
}

char	**pipe_split(char *line, t_cmd *cmd)
{
	char	**s;
	int		i;

	(void)cmd;
	s = NULL;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '|')
		{
			s = ft_split_no_quote(line, '|');
			if (!s)
				exit_malloc(cmd);
			break ;
		}
	}
	return (s);
}

static int	skip_del(char *line, int *i, int *is_cmd)
{
	if (line[*i] == ' ')
		skip_space(line, i);
	if (line[*i] && line[*i] != '>' && line[*i] != '<')
	{
		(*is_cmd) = 1;
		return (1);
	}
	if ((line[*i] == '>' && line[*i + 1] == '>' )
		|| (line[*i] == '<' && line[*i + 1] == '<'))
		(*i) += 2;
	else
		(*i)++;
	return (0);
}

void	is_cmd_or_not(char *line, int *is_cmd)
{
	int	i;

	i = 0;
	if (skip_del(line, &i, is_cmd) == 1)
		return ;
	while (line[i])
	{
		skip_space(line, &i);
		while (line[i] && line[i] != ' ' && line[i] != '>' && line[i] != '<')
			i++;
		if (line[i] == ' ' && line[i])
			skip_space(line, &i);
		if ((line[i] == '>' && line[i + 1] == '>' )
			|| (line[i] == '<' && line[i + 1] == '<'))
			i += 2;
		else if (line[i] == '>' || line[i] == '<')
			i++;
		else if (line[i] != '>' && line[i] != '<' && line[i] != '\0')
		{
			(*is_cmd) = 1;
			return ;
		}
	}
}
