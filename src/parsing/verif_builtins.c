/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:32:39 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 10:45:30 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	verif_malloc(t_cmd *cmd);
void	parse_exun(t_cmd *cmd);

static void	parse_cd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->s_builtins[i] == ' ')
		skip_space(cmd->s_builtins, &i);
	while (cmd->s_builtins[i] && cmd->s_builtins[i] != ' ')
		i++;
	if (cmd->s_builtins[i] == ' ')
		skip_space(cmd->s_builtins, &i);
	if (cmd->nbr_cmd == 1)
		cmd->export = 0;
}

static void	exec_builtins(t_cmd *cmd)
{
	t_lst	*tmp;

	tmp = NULL;
	tmp = cmd->commands;
	while (cmd->commands)
	{
		if ((ft_strncmp(cmd->commands->cmd[0], "export", 6) == 0))
			parse_exun(cmd);
		else if ((ft_strncmp(cmd->commands->cmd[0], "unset", 5) == 0))
			parse_exun(cmd);
		else if ((ft_strncmp(cmd->commands->cmd[0], "cd", 2) == 0))
			parse_cd(cmd);
		cmd->commands = cmd->commands->next;
	}
	cmd->commands = tmp;
}

static void	verif_exec_builtins(t_cmd *cmd, char **test)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	cmd->s_builtins = test[cmd->y];
	while (cmd->s_builtins[i] && cmd->s_builtins[i + 1] != '>')
	{
		i++;
		len++;
	}
	cmd->s_builtins = ft_substr(cmd->s_builtins, 0, len);
	exec_builtins(cmd);
}

static int	verif_pipe_built(t_cmd *cmd, char *line)
{
	char	**test;
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ')
			skip_space(line, &i);
		test = ft_split_no_quote(line, '|');
		if (test == NULL)
			exit_malloc(cmd);
		else
		{
			verif_exec_builtins(cmd, test);
		}
		if (test)
			free_2d(test);
		return (1);
	}
	return (0);
}

int	verif_buildtins(char *line, t_cmd *cmd)
{
	int		count;
	t_lst	*tmp;
	int		x;

	cmd->y = 0;
	count = 0;
	x = 0;
	tmp = NULL;
	cmd->builtpos = NULL;
	cmd->builtpos = malloc(sizeof(int) * (cmd->nbr_cmd + 1));
	verif_malloc(cmd);
	tmp = cmd->commands;
	while (cmd->commands)
	{
		if_built(cmd->commands->cmd[0], cmd, &x, &count);
		cmd->commands = cmd->commands->next;
	}
	cmd->commands = tmp;
	cmd->y = x - 1;
	if (count != 0)
	{
		if (verif_pipe_built(cmd, line) == 1)
			return (1);
	}
	return (0);
}
