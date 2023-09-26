/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:00:55 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/25 11:25:13 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_fill_lst(t_lst **cmd, t_pipex *pipex, char *envp[], t_parsing **path)
{
	t_parsing	*element;
	char		*tmp;

	pipex->i = 0;
	while ((*cmd))
	{
		ft_parsing_exec(pipex, envp, cmd);
		tmp = ft_substr(pipex->pathcmd, 0, ft_strlen(pipex->pathcmd));
		free (pipex->pathcmd);
		pipex->pathcmd = NULL;
		element = ft_lst_new_exec(tmp);
		ft_lst_add_back_exec(path, element);
		(*cmd) = (*cmd)->next;
		pipex->i++;
	}
}
