/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:17:34 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/24 16:19:02 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	error_message(t_cmd *cmd)
{
	g_status = 126;
	ft_putstr_fd("bash: ", cmd->old_stdout);
	ft_putstr_fd(cmd->commands->cmd[0], cmd->old_stdout);
	ft_putstr_fd(": No such file or directory\n", cmd->old_stdout);
}

void	error_message_out(t_cmd *c, t_pipex *pi)
{
	pi->fd2 = open(c->out->cmd[0], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (pi->fd2 < 0)
		printf("zsh: no such file or directory: %s\n", c->out->cmd[0]);
}

void	ft_error_message(char *str, t_pipex *pipex)
{
	ft_printf("%s", str);
	ft_close(pipex);
}

int	modif_shlvl(int shlvl, char a)
{
	if (shlvl >= 999 && a == 'u')
	{
		printf("bash: warning: shell level (1000) too high, resetting to 1\n");
		shlvl = 1;
	}
	else if (shlvl > 999 || shlvl < -999)
	{
		if (shlvl > 999)
			shlvl = 1;
		else
			shlvl = 0;
	}
	else if (shlvl == 0)
		shlvl = 2;
	else if (a == 'u')
		shlvl++;
	else
		shlvl--;
	return (shlvl);
}

void	verif_minishell(t_cmd *c, t_pipex *pipex, char *cmd)
{
	if (ft_strncmp(cmd, "minishell", 9) == 0)
	{
		if (ft_strncmp(cmd, "minishell", ft_strlen(cmd)) == 0)
		{
			g_status = 127;
			ft_putstr_fd(c->commands->cmd[0], c->old_stdout);
			ft_putstr_fd(": command not found\n", c->old_stdout);
			free_exec_child(c, pipex, c->tmp_path);
			exit(0);
		}
	}
}
