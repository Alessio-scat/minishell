/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsepipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:02:15 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/22 10:33:25 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	verif_pipe(t_cmd *cmd)
{
	int	i;
	int	y;

	i = 0;
	while (cmd->split_line[i])
	{
		y = 0;
		cmd->str = NULL;
		cmd->content = NULL;
		cmd->i_cmd = 0;
		while (cmd->split_line[i][y])
		{
			get_cmd(cmd->split_line[i], cmd);
			break ;
		}
		i++;
	}
}

int	parsepipe(char *line, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '|')
		{
			cmd->split_line = ft_split_no_quote(line, '|');
			if (!cmd->split_line)
				return (-1);
			verif_pipe(cmd);
			free_2d(cmd->split_line);
			break ;
		}
	}
	return (0);
}
