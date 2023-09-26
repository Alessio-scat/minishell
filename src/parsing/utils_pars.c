/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:06:16 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/25 10:48:14 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	if_built(char *cmd, t_cmd *c, int *x, int *count)
{
	if ((ft_strncmp(cmd, "echo", 4) == 0 && cmd[4] == '\0')
		|| (ft_strncmp(cmd, "export", 6) == 0 && cmd[6] == '\0')
		|| (ft_strncmp(cmd, "unset", 5) == 0 && cmd[5] == '\0')
		|| (ft_strncmp(cmd, "cd", 2) == 0 && cmd[2] == '\0')
		|| (ft_strncmp(cmd, "exit", 4) == 0 && cmd[4] == '\0')
		|| (ft_strncmp(cmd, "pwd", 3) == 0 && cmd[3] == '\0')
		|| (ft_strncmp(cmd, "env", 3) == 0 && cmd[3] == '\0'))
	{
		if (ft_strncmp(cmd, "exit", 4) == 0 && c->nbr_cmd == 1)
			c->exitalone = 1;
		c->builtpos[c->y] = 1;
		if (c->commands->cmd[1])
		{
			if (ft_strncmp(cmd, "env", 3) == 0)
				c->builtpos[c->y] = 0;
		}
		(*count)++;
		c->y++;
		*x = c->y;
	}
	else
	{
		c->builtpos[c->y] = 0;
		c->y++;
	}
}

void	verif_malloc(t_cmd *cmd)
{
	if (!cmd->builtpos)
	{
		free_cmd(&cmd->commands, cmd);
		exit_malloc(cmd);
	}
}

void	parse_exun(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->s_builtins[i] == ' ')
		skip_space(cmd->s_builtins, &i);
	while (cmd->s_builtins[i] && cmd->s_builtins[i] != ' ')
		i++;
	if (cmd->s_builtins[i] == ' ')
		skip_space(cmd->s_builtins, &i);
	if (cmd->s_builtins[i] != '\0' && cmd->nbr_cmd == 1)
		cmd->export = 0;
}
