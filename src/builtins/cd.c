/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:48:09 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/25 11:41:40 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	cd_tild(void);

void	ft_builtin_cd(char *path)
{
	if (chdir(path) == -1)
	{
		g_status = 1;
		printf("bash: cd: %s: No such file or directory\n", path);
	}
}

static void	cd_alone(t_export *export, t_cmd *cmdstruc)
{
	if (!cmdstruc->commands->cmd[1])
	{
		while (export)
		{
			if (ft_strncmp(export->variable, "HOME", \
			ft_strlen(export->variable)) == 0)
			{
				if (ft_strncmp(export->variable, "HOME", 3) == 0)
				{
					if (!export->content)
					{
						printf("bash: cd: HOME not set\n");
						break ;
					}
					ft_builtin_cd(export->content);
					break ;
				}
			}
			export = export->next;
		}
		if (!export)
			printf("bash: cd: HOME not set\n");
	}
}

static void	update_pwd(t_export *export)
{
	char		*tmp2;

	tmp2 = NULL;
	while (export)
	{
		if (ft_strncmp(export->variable, "PWD", \
		ft_strlen(export->variable)) == 0)
		{
			if (ft_strncmp(export->variable, "PWD", 3) == 0)
			{
				tmp2 = ft_builtin_pwd('n', export);
				if (tmp2 != NULL)
				{
					free(export->content);
					export->content = tmp2;
				}
			}
		}
		export = export->next;
	}
}

static void	minus_cd(t_export *e, t_cmd *c)
{
	while (e)
	{
		if (ft_strncmp(e->variable, "OLDPWD", ft_strlen(e->variable)) == 0)
		{
			if (ft_strncmp(e->variable, "OLDPWD", 6) == 0)
			{
				ft_builtin_cd(e->content);
				if (chdir(e->content) != -1)
					ft_builtin_pwd('y', e);
				if (c->tmppwd)
				{
					free(e->content);
					e->content = ft_substr(c->tmppwd, 0, ft_strlen(c->tmppwd));
				}
				break ;
			}
		}
		e = e->next;
	}
	if (!e)
		printf("bash: cd: OLDPWD not set\n");
}

void	ft_cd_cmd(t_export *export, t_cmd *c)
{
	while (export)
	{
		if (cd_verif(export, c) == 1)
			break ;
		export = export->next;
	}
	if (c->commands->cmd[1])
	{
		if (c->commands->cmd[2] == NULL && c->commands->cmd[1][0] == '-')
			minus_cd(export, c);
		else if (c->commands->cmd[2] == NULL && c->commands->cmd[1][0] == '~')
			cd_tild();
		else if (c->commands->cmd[2] == NULL && c->commands->cmd[1][0] != '~')
			ft_builtin_cd(c->commands->cmd[1]);
		else
		{
			g_status = 1;
			printf("bash: cd: too many arguments\n");
		}
	}
	export = c->ex;
	cd_alone(export, c);
	update_pwd(export);
}
