/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newecho.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:18:13 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/24 14:09:39 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	verif_n(t_cmd *cmd, t_builtins *built)
{
	int	y;

	built->i = 1;
	y = 0;
	while (cmd->commands->cmd[built->i]
		&& cmd->commands->cmd[built->i][y] == '-'
		&& cmd->commands->cmd[built->i][y + 1] == 'n')
	{
		if (cmd->commands->cmd[built->i][y + 1] == 'n')
		{
			y++;
			while (cmd->commands->cmd[built->i][y] == 'n')
				y++;
		}
		if (cmd->commands->cmd[built->i][y] == '\0')
			built->i++;
		else
			break ;
		y = 0;
	}
}

void	new_echo(t_cmd *cmd, t_builtins *built)
{
	verif_n(cmd, built);
	while (cmd->commands->cmd[built->i])
	{
		printf("%s", cmd->commands->cmd[built->i]);
		if (cmd->commands->cmd[built->i + 1])
			printf(" ");
		built->i++;
	}
	if (built->verif_n == 0)
		printf("\n");
}

void	ft_echo(t_cmd *cmdstruc, t_builtins builtins)
{
	int	i;

	if (cmdstruc->commands->cmd[1] == NULL)
	{
		printf("\n");
		return ;
	}
	if (cmdstruc->commands->cmd[1][0] == '-'
		&& cmdstruc->commands->cmd[1][1] == 'n'
			&& cmdstruc->commands->cmd[1][0] != '$')
	{
		i = 1;
		while (cmdstruc->commands->cmd[1][i] == 'n')
			i++;
		if (cmdstruc->commands->cmd[1][i] == '\0')
			builtins.verif_n = 1;
		new_echo(cmdstruc, &builtins);
	}
	else
		new_echo(cmdstruc, &builtins);
}
