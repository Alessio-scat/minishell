/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:11:10 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 11:07:44 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

long long	ft_atoi_exit(const char *str);
long long	return_number(double long nb, int sign);
void		exit_to_many_arg(t_cmd *cmd);
void		ft_exit(t_cmd *cmd, char **args);

static void	error_numeric(char *args, t_cmd *cmd)
{
	ft_putstr_fd("exit\n", cmd->old_stdout);
	ft_putstr_fd("bash: exit: ", cmd->old_stdout);
	ft_putstr_fd(args, cmd->old_stdout);
	ft_putstr_fd(": numeric argument required\n", cmd->old_stdout);
	cmd->e++;
	g_status = 2;
	if (cmd->nbr_cmd == 1)
	{
		exit_free(cmd);
		exit(g_status);
	}
}

static void	verif_arg_exit(char *args, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (args[i] == '+' || args[i] == '-')
		i++;
	while (args[i])
	{
		if (args[i] != ' ' && args[i] != '\t')
		{
			if (args[i] < 48 || args[i] > 57)
			{
				error_numeric(args, cmd);
				break ;
			}
		}
		i++;
	}
}

static void	handle_no_arg(t_cmd *cmd)
{
	if (cmd->nbr_cmd == 1)
		ft_putstr_fd("exit\n", cmd->old_stdout);
	shlvl(cmd->ex, 'a', cmd);
	free_export(&cmd->ex);
	free_array(cmd->env, 0);
	if (cmd->tmppwd)
		free(cmd->tmppwd);
	free_cmd(&cmd->commands, cmd);
	free(cmd->builtpos);
	if (cmd->s_builtins)
		free(cmd->s_builtins);
	if (cmd->old_stdout >= 0)
		close(cmd->old_stdout);
	free(cmd->tab_out);
	free_redirec(&cmd->cmd);
	free_cmd(&cmd->in, cmd);
	free_cmd(&cmd->out, cmd);
	free_cmd(&cmd->here_doc_test, cmd);
	exit(0);
}

static void	handle_min_one_arg(t_cmd *cmd, char **args)
{
	long long	result;

	if (ft_strcmp(args[1], "-1") == 0)
	{
		g_status = 255;
		ft_putstr_fd("exit\n", cmd->old_stdout);
		exit_free(cmd);
		exit(g_status);
	}
	result = ft_atoi_exit(args[1]);
	if (result == -1)
		error_numeric(args[1], cmd);
}

void	ft_builtin_exit(char **args, t_cmd *cmd)
{
	int			i;

	i = 0;
	cmd->e = 0;
	if (!args[1])
	{
		if (cmd->nbr_cmd > 1)
			return ;
		handle_no_arg(cmd);
	}
	verif_arg_exit(args[1], cmd);
	while (args[i])
		i++;
	if (i > 2 && cmd->e == 0)
	{
		exit_to_many_arg(cmd);
		return ;
	}
	else
	{
		handle_min_one_arg(cmd, args);
	}
	if (cmd->nbr_cmd > 1)
		return ;
	ft_exit(cmd, args);
}
