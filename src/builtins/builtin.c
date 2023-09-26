/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:48:42 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/25 10:47:02 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	check_export_error(char *cmd, int i, t_cmd *cmdstruc)
{
	if (cmd[0] == '-')
		return (message(1, cmd, i, cmdstruc), g_status = 2);
	if (ft_isdigit(cmd[0]) || cmd[0] == '=' || cmd[0] == '\0')
		return (message(2, cmd, i, cmdstruc), g_status = 1);
	while (cmd[i] != '\0' && cmd[i] != '=')
	{
		if (cmd[i] == '!')
			return (message(3, cmd, i, cmdstruc), g_status = 1);
		if (cmd[i] == '@' || cmd[i] == '%' || cmd[i] == '?'
			|| cmd[i] == '*' || cmd[i] == '\\' || cmd[i] == '~'
			|| cmd[i] == '-' || cmd[i] == '.' || cmd[i] == '{'
			|| cmd[i] == '}' || cmd[i] == '#' || cmd[i] == '+')
			return (message(2, cmd, i, cmdstruc), g_status = 1);
		i++;
	}
	while (cmd[i])
	{
		if (cmd[i] == '!')
			return (message(3, cmd, i, cmdstruc), g_status = 1);
		i++;
	}
	return (0);
}

static int	check_unset_error(char *cmd, int i, t_cmd *cmdstruc)
{
	if (cmd[0] == '-')
		return (message_unset(1, cmd, i, cmdstruc), g_status = 2);
	if (ft_isdigit(cmd[0]) || cmd[0] == '=' || cmd[0] == '\0')
		return (message_unset(2, cmd, i, cmdstruc), g_status = 1);
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '!')
			return (message(3, cmd, i, cmdstruc), g_status = 1);
		if (cmd[i] == '@' || cmd[i] == '%' || cmd[i] == '?'
			|| cmd[i] == '*' || cmd[i] == '\\' || cmd[i] == '~'
			|| cmd[i] == '-' || cmd[i] == '.' || cmd[i] == '{'
			|| cmd[i] == '}' || cmd[i] == '#' || cmd[i] == '+'
			|| cmd[i] == '=' || cmd[i] == '^' || cmd[i] == '/')
			return (message_unset(2, cmd, i, cmdstruc), g_status = 1);
		i++;
	}
	return (0);
}

static int	ft_export(t_cmd *cmdstruc, t_export *exp, t_builtins builtins)
{
	int	i;

	if (cmdstruc->commands->cmd[1] == NULL)
	{
		print_export(exp);
		return (1);
	}
	if (cmdstruc->commands->cmd[1])
	{
		i = 1;
		while (cmdstruc->commands->cmd[i])
		{
			if (check_export_error(cmdstruc->commands->cmd[i], 0, \
			cmdstruc) == 0)
				ft_builtin_export(cmdstruc->commands->cmd[i], exp, &builtins);
			i++;
		}
	}
	return (0);
}

static void	ft_unset(t_cmd *cmdstruc, t_export *export)
{
	int	i;

	if (cmdstruc->commands->cmd[1])
	{
		i = 1;
		while (cmdstruc->commands->cmd[i])
		{
			if (check_unset_error(cmdstruc->commands->cmd[i], 0, cmdstruc) == 0)
				ft_builtin_unset(cmdstruc->commands->cmd[i], export);
			i++;
		}
	}
}

void	ft_builtin(char *input, char *env[], t_export *export, t_cmd *cmdstruc)
{
	t_builtins	builtins;

	(void)input;
	(void)env;
	builtins.verif_n = 0;
	if (ft_strncmp(cmdstruc->commands->cmd[0], "pwd", 3) == 0)
		ft_pwd(cmdstruc, export);
	if (ft_strncmp(cmdstruc->commands->cmd[0], "cd", 2) == 0)
		ft_cd_cmd(export, cmdstruc);
	if (ft_strncmp(cmdstruc->commands->cmd[0], "exit", 4) == 0)
		ft_builtin_exit(cmdstruc->commands->cmd, cmdstruc);
	if (ft_strncmp(cmdstruc->commands->cmd[0], "export", 6) == 0)
	{
		if (ft_export(cmdstruc, export, builtins) == 1)
			return ;
	}
	if (ft_strncmp(cmdstruc->commands->cmd[0], "echo", 4) == 0)
		ft_echo(cmdstruc, builtins);
	if (ft_strncmp(cmdstruc->commands->cmd[0], "unset", 5) == 0)
		ft_unset(cmdstruc, export);
	if (ft_strncmp(cmdstruc->commands->cmd[0], "env", 3) == 0)
		ft_builtin_env(env);
}
