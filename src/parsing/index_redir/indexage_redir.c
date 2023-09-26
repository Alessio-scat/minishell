/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexage_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:13:40 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/23 10:32:02 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int		count_pipe(char *line);
char	**pipe_split(char *line, t_cmd *cmd);
void	fill_simple_tab(char *line, t_cmd *cmd);
void	fill_tab(char **s, t_cmd *cmd);

void	indexage_redir(char *line, t_cmd *cmd)
{
	int		num_pipe;
	char	**split_pipe;

	cmd->tab_out = NULL;
	split_pipe = NULL;
	num_pipe = count_pipe(line);
	if (num_pipe > 0)
	{
		cmd->tab_out = malloc(sizeof(int) * (num_pipe + 2));
		if (!cmd->tab_out)
			exit_malloc(cmd);
		split_pipe = pipe_split(line, cmd);
		if (split_pipe)
			fill_tab(split_pipe, cmd);
		if (split_pipe)
			free_2d(split_pipe);
	}
	else
		fill_simple_tab(line, cmd);
	return ;
}
