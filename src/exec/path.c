/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:21:22 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/25 11:32:56 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	*ft_path_finding(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH", envp[i], 3) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static void	ft_join_path(t_pipex *pipex, char *split, char *mycmd)
{
	char	*str;

	str = ft_strjoin(split, "/");
	if (!str)
		ft_free_join(pipex);
	pipex->join_cmd = ft_strjoin(str, mycmd);
	if (!pipex->join_cmd)
		ft_free_join(pipex);
	free(str);
}

static char	*ft_access(t_pipex *pipex, char **split, char *mycmd)
{
	int		i;

	pipex->tmp = NULL;
	i = -1;
	if (access(mycmd, X_OK) == 0)
	{
		pipex->tmp = ft_substr(mycmd, 0, ft_strlen(mycmd));
		return (pipex->tmp);
	}
	while (split[++i])
	{
		ft_join_path(pipex, split[i], mycmd);
		if (access(pipex->join_cmd, X_OK) == 0)
		{
			pipex->free = i;
			return (pipex->join_cmd);
		}
		free(pipex->join_cmd);
	}
	pipex->free = i;
	return (NULL);
}

void	ft_parsing_exec(t_pipex *pi, char *envp[], t_lst **cmd_arg)
{	
	pi->path = ft_path_finding(envp);
	if (pi->i == 0)
		pi->split_path = ft_split(pi->path, ':');
	if (pi->split_path || access((*cmd_arg)->cmd[0], F_OK) == 0)
		pi->pathcmd = ft_access(pi, pi->split_path, (*cmd_arg)->cmd[0]);
	if (!pi->pathcmd)
	{
		if ((*cmd_arg)->cmd[0][0] == '/')
		{
			printf("bash: %s: No such file or directory\n", (*cmd_arg)->cmd[0]);
			g_status = 127;
		}
		else if (!pi->path && pi->cmd->builtpos[pi->i] != 1)
		{
			printf \
			("bash: %s: No such file or directory\n", (*cmd_arg)->cmd[0]);
			g_status = 127;
		}
		pi->pathcmd = malloc(sizeof(char) * 1);
		if (!pi->pathcmd)
			exit_malloc(pi->cmd);
		pi->pathcmd[0] = '\0';
	}
}
