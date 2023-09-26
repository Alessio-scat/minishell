/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:26:15 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/24 16:31:20 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	ft_open_out_without_cmd(t_cmd *c, t_pipex *pi)
{
	int	i;

	i = 0;
	while (c->out && i < pi->total + c->tab_out[pi->i])
	{
		i++;
		c->out = c->out->next;
	}
	i = 0;
	while (c->out && i-- > c->tab_out[pi->i])
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
	}
}

void	ft_close(t_pipex *pipex)
{
	int	j;

	j = 0;
	while (j < (2 * pipex->num_pipe))
	{
		close(pipex->pipefd[j]);
		j++;
	}
	if (pipex->fd2 >= 0)
		close(pipex->fd2);
	if (pipex->fd3 >= 0)
		close(pipex->fd3);
	if (pipex->fd1 >= 0)
		close(pipex->fd1);
}

void	free_cmds(t_parsing **pile)
{
	t_parsing	*tmp;

	while (*pile)
	{
		tmp = (*pile)->next;
		free(*pile);
		*pile = tmp;
	}
	*pile = NULL;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	wrong_pid(t_pipex *pipex)
{
	ft_close(pipex);
	perror("Fork: ");
	exit(-2);
}
