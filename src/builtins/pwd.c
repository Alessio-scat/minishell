/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:36:02 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/24 14:34:19 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*pwd_export(char c, t_export *export)
{
	while (export)
	{
		if (ft_strncmp(export->variable, "PWD", \
		ft_strlen(export->variable)) == 0)
		{
			if (ft_strncmp(export->variable, "PWD", 3) == 0)
			{
				if (c == 'n')
					return (ft_substr(export->content, 0, \
					ft_strlen(export->content)));
				else
					printf("%s\n", export->content);
			}
		}
		export = export->next;
	}
	return (NULL);
}

char	*ft_builtin_pwd(char c, t_export *export)
{
	char	cwd[PATH_MAX];
	char	*str;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (c == 'n')
		{
			str = ft_strdup(cwd);
			if (!str)
				exit(-2);
			return (str);
		}
		else
			printf("%s\n", cwd);
	}
	else
	{
		str = pwd_export(c, export);
		return (str);
	}
	return (NULL);
}

void	ft_pwd(t_cmd *cmdstruc, t_export *export)
{
	char	a[2];

	if (cmdstruc->commands->cmd[1])
	{
		if (cmdstruc->commands->cmd[1][0] == '-'
			&& cmdstruc->commands->cmd[1][1] == '-'
				&& cmdstruc->commands->cmd[1][2] == 0)
			ft_builtin_pwd('y', export);
		else if (cmdstruc->commands->cmd[1][0] == '-'
			&& cmdstruc->commands->cmd[1][1] != 0)
		{
			a[0] = cmdstruc->commands->cmd[1][1];
			a[1] = 0;
			g_status = 2;
			ft_putstr("bash: pwd: -", cmdstruc->old_stdout);
			ft_putstr(a, cmdstruc->old_stdout);
			ft_putstr(": invalid option\n", cmdstruc->old_stdout);
		}
		else
			ft_builtin_pwd('y', export);
	}
	else
		ft_builtin_pwd('y', export);
}
