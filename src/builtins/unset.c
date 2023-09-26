/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:33:03 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/25 10:27:39 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_builtin_unset(char *name, t_export *export)
{
	int	sizename;

	sizename = ft_strlen(name);
	while (export)
	{
		if (ft_strncmp(name, export->variable, sizename) == 0)
		{
			free(export->variable);
			free(export->content);
			export->variable = ft_strdup("\0");
			if (!export->variable)
				exit (-2);
			export->content = ft_strdup("\0");
			if (!export->content)
			{
				free(export->variable);
				exit (-2);
			}
			break ;
		}
		export = export->next;
	}
}

void	message_unset(int error, char *cmd, int i, t_cmd *cmdstruc)
{
	if (error == 1)
	{
		ft_putstr_fd("unset: `-", cmdstruc->old_stdout);
		ft_putstr_fd(&cmd[1], cmdstruc->old_stdout);
		ft_putstr_fd("': not a valid identifier\n", cmdstruc->old_stdout);
	}
	else if (error == 2)
	{
		ft_putstr_fd("unset: `", cmdstruc->old_stdout);
		ft_putstr_fd(cmd, cmdstruc->old_stdout);
		ft_putstr_fd("': not a valid identifier\n", cmdstruc->old_stdout);
	}
	else if (error == 3)
	{
		ft_putstr_fd(&cmd[i], cmdstruc->old_stdout);
		ft_putstr_fd(": event not found\n", cmdstruc->old_stdout);
	}
}
