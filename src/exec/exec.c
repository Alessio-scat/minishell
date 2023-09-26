/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:59:49 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/24 15:40:59 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	here_doc_file(t_cmd *cmd, char *chemin, int file)
{	
	int	len;

	if (g_status == 130)
		return (1);
	if (cmd->here_doc_test->next == NULL)
	{
		if (ft_strcmp(cmd->here_doc_test->cmd[0], chemin) == 0)
			return (1);
		if (cmd->hdoc_quote == 0)
			chemin = see_dollar(chemin, cmd);
		len = write(file, chemin, ft_strlen(chemin));
		len = write(file, "\n", 1);
		(void)len;
	}
	if ((ft_strcmp(cmd->here_doc_test->cmd[0], chemin) == 0)
		&& cmd->here_doc_test->next)
		cmd->here_doc_test = cmd->here_doc_test->next;
	free(chemin);
	return (0);
}

static void	loop(t_cmd *cmd, char *chemin, int file)
{
	while (1)
	{
		signal(SIGINT, ms_handle_hdoc);
		chemin = readline("> ");
		if (!chemin)
		{
			printf ("bash: warning: here-document at line number \
			delimited by end-of-file (wanted `%s')\n", \
			cmd->here_doc_test->cmd[0]);
			if (cmd->here_doc_test->next == NULL)
				break ;
			else
				cmd->here_doc_test = cmd->here_doc_test->next;
		}
		if (chemin)
		{
			if (here_doc_file(cmd, chemin, file) == 1)
				break ;
		}
	}
	signal(SIGINT, ms_handle_sigint);
}

static void	here_doc(t_pipex *pipex, t_cmd *cmd, char *envp[])
{
	char		*chemin;
	t_lst		*tmp_cmd_arg;
	t_parsing	*path;

	path = NULL;
	chemin = NULL;
	tmp_cmd_arg = cmd->commands;
	loop(cmd, chemin, pipex->file_here);
	free(chemin);
	close(pipex->file_here);
	pipex->fd1 = open(".tmp", O_RDONLY);
	if (pipex->fd1 < 0)
		perror("File ");
	unlink(".tmp");
	ft_fill_lst(&tmp_cmd_arg, pipex, envp, &path);
	ft_pipex_bonus2(pipex, cmd, envp, path);
	free_exec(cmd, pipex, path);
}

static void	verif_outfile(t_cmd *cmd, t_pipex pipex)
{
	int			verif;
	int			nb;

	verif = 0;
	nb = 0;
	pipex.i = 0;
	while (cmd->tab_out[pipex.i])
	{
		if (cmd->tab_out[pipex.i] > 0 && cmd->tab_out[pipex.i] != 1000)
			verif = 1;
		if (cmd->tab_out[pipex.i] > 0 && cmd->tab_out[pipex.i] != 1000)
			nb += cmd->tab_out[pipex.i];
		else if (cmd->tab_out[pipex.i] < 0 && cmd->tab_out[pipex.i] != 1000)
			nb += (cmd->tab_out[pipex.i] * -1);
		pipex.i++;
	}
	pipex.total = nb;
	if (verif == 0 && cmd->tab_out[0] != 1000)
	{
		ft_open_in(cmd, &pipex);
		ft_open_out(cmd, &pipex);
		close(pipex.fd2);
	}
}

int	exec(char *envp[], t_cmd *cmd)
{
	t_pipex		pipex;
	t_parsing	*path;
	t_lst		*tmp_cmd_arg;

	path = NULL;
	pipex.cmd = cmd;
	tmp_cmd_arg = cmd->commands;
	pipex.cmd = cmd;
	init_exec(&pipex, cmd);
	ft_open_fd(cmd, &pipex);
	verif_outfile(cmd, pipex);
	if (cmd->here_doc_test)
	{
		here_doc(&pipex, cmd, envp);
		return (0);
	}
	ft_fill_lst(&tmp_cmd_arg, &pipex, envp, &path);
	ft_pipex_bonus2(&pipex, cmd, envp, path);
	free_exec(cmd, &pipex, path);
	return (0);
}
