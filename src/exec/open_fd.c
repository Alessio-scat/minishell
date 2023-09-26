/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:46:17 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/24 16:21:28 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_open_fd(t_cmd *cmd, t_pipex *pipex)
{
	if (cmd->here_doc_test)
	{
		pipex->file_here = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipex->file_here < 0)
			ft_printf("zsh: no such file or directory: file");
	}
}

void	ft_open_out(t_cmd *c, t_pipex *pi)
{
	int	nb_out;

	nb_out = 0;
	if (c->out)
	{
		while (c->out && nb_out < pi->total)
		{
			if (pi->fd2 >= 0)
				close(pi->fd2);
			if (c->out->file == 'o')
			{
				pi->fd2 = open \
				(c->out->cmd[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
				if (pi->fd2 < 0)
					printf \
					("zsh: no such file or directory: %s\n", c->out->cmd[0]);
			}
			else if (c->out->file == 'a')
				error_message_out(c, pi);
			nb_out++;
			c->out = c->out->next;
		}
	}
}

void	ft_open_fd3(t_pipex *pi, t_cmd *c)
{
	int	nb_out;

	nb_out = 0;
	while (nb_out < pi->total)
	{
		if (c->out->file == 'o')
		{
			pi->fd3 = open(c->out->cmd[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (pi->fd3 < 0)
				printf("zsh: no such file or directory: %s\n", c->out->cmd[0]);
		}
		else if (c->out->file == 'a')
		{
			pi->fd3 = open(c->out->cmd[0], O_CREAT | O_RDWR | O_APPEND, 0644);
			if (pi->fd3 < 0)
				printf("zsh: no such file or directory: %s\n", c->out->cmd[0]);
		}
		c->out = c->out->next;
		nb_out++;
	}
}

int	ft_open_in(t_cmd *cmd, t_pipex *pipex)
{
	if (cmd->in)
	{
		while (cmd->in->next)
			cmd->in = cmd->in->next;
		pipex->fd1 = open(cmd->in->cmd[0], O_RDONLY);
		if (pipex->fd1 < 0)
		{
			printf("zsh: no such file or directory: %s\n", cmd->in->cmd[0]);
			return (1);
		}
	}
	return (0);
}

void	ft_total_out(t_cmd *cmd, t_pipex *pipex)
{
	int	i;
	int	total;

	total = 0;
	i = 0;
	pipex->total = 0;
	while (i <= pipex->i)
	{
		if (cmd->tab_out[i] > 0 && cmd->tab_out[i] != 1000)
			total += cmd->tab_out[i];
		else if (cmd->tab_out[i] < 0 && cmd->tab_out[i] != 1000)
			total += (cmd->tab_out[i] * -1);
		i++;
	}
	pipex->total = total;
}
