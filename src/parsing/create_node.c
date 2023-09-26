/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:29:32 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 10:54:05 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	see_quote(char **cmds, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	(void)cmd;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			if (cmds[i][j] == '"' || cmds[i][j] == '\'')
			{
				cmds[i] = remove_quote(cmds[i], ft_strlen(cmds[i]));
				break ;
			}
			j++;
		}
		i++;
	}
}

void	add_redir(char **s, t_lst **lst, char file, t_cmd *cmd)
{
	t_lst	*new;

	if (!s)
		return ;
	see_quote(s, cmd);
	new = lst_new_redir(s, file);
	lst_add_back(lst, new);
}

void	create_node(char **cmds, t_lst **command, t_cmd *cmd)
{
	t_lst	*new;

	if (cmds[0] == NULL)
		return ;
	see_quote(cmds, cmd);
	if (cmds[0] == NULL)
		return ;
	cmd->nbr_cmd++;
	new = lst_new(cmds);
	lst_add_back(command, new);
}
