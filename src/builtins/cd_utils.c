/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:52:24 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/24 10:13:01 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	cd_tmppwd(t_export *export, t_cmd *c)
{
	char		*tmp;

	tmp = NULL;
	if (c->commands->cmd[1])
	{
		if (c->commands->cmd[1][0] == '-')
		{
			tmp = ft_builtin_pwd('n', export);
			if (tmp != NULL)
			{
				free(tmp);
				tmp = NULL;
				if (c->tmppwd)
					free(c->tmppwd);
				c->tmppwd = ft_builtin_pwd('n', export);
			}
			return (1);
		}
	}
	return (0);
}

int	update_oldpwd(t_export *export)
{
	char		*tmp;

	tmp = NULL;
	if (ft_strncmp(export->variable, "OLDPWD", \
	ft_strlen(export->variable)) == 0)
	{
		if (ft_strncmp(export->variable, "OLDPWD", 6) == 0)
		{
			tmp = ft_builtin_pwd('n', export);
			if (tmp != NULL)
			{
				free(tmp);
				tmp = NULL;
				free(export->content);
				export->content = ft_builtin_pwd('n', export);
			}
			return (1);
		}
	}
	return (0);
}

int	cd_verif(t_export *export, t_cmd *c)
{
	if (cd_tmppwd(export, c) == 1)
		return (1);
	if (update_oldpwd(export) == 1)
		return (1);
	return (0);
}
