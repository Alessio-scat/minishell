/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:54:20 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 09:53:42 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*remove_tab(char *line);

int	parsing(char *line, t_cmd *cmd)
{
	int	error;

	cmd->sauvegarde = line;
	init_param(cmd);
	if (line[0] == '\0')
		return (-2);
	line = remove_tab(line);
	error = check_syntax(line);
	if (error == 1)
		return (-2);
	indexage_redir(line, cmd);
	redirs(line, cmd);
	error = parsepipe(line, cmd);
	if (error == -1)
		return (-1);
	if (cmd->nbr_cmd == 0)
		get_cmd(line, cmd);
	if (verif_buildtins(line, cmd) == 1)
		return (1);
	return (0);
}
