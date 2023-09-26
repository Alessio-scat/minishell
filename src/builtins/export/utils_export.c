/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:48:28 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/24 14:07:28 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	print_list_exp(char **export)
{
	int		i;
	int		j;
	char	*tmp2;

	i = 0;
	while (export[i])
	{
		j = 0;
		while (export[j] && export[j + 1])
		{
			if (ft_strncmp(export[j], export[j + 1], ft_strlen(export[j])) > 0)
			{
				tmp2 = export[j];
				export[j] = export[j + 1];
				export[j + 1] = tmp2;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (export[i])
		printf("declare -x %s\n", export[i++]);
	free_2d(export);
}

int	ft_lst_size_export(t_export *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	verif_variable(t_export *ex, int sizevar, char **var, t_builtins *bu)
{
	char	*tmp;

	tmp = NULL;
	if (var[1] == NULL)
	{
		if (bu->countspace == 1)
		{
			tmp = ft_strdup("\0");
			free(ex->content);
			ex->content = tmp;
		}
		return ;
	}
	sizevar = ft_strlen(var[1]);
	if (export_verif_cote(ex, sizevar, var) == 1)
		return ;
	free(ex->content);
	tmp = ft_substr(var[1], 0, ft_strlen(var[1]));
	ex->content = tmp;
	free_2d(var);
	return ;
}

void	message(int error, char *cmd, int i, t_cmd *cmdstruc)
{
	if (error == 1)
	{
		ft_putstr_fd("export: `-", cmdstruc->old_stdout);
		ft_putstr_fd(&cmd[1], cmdstruc->old_stdout);
		ft_putstr_fd("': not a valid identifier\n", cmdstruc->old_stdout);
	}
	else if (error == 2)
	{
		ft_putstr_fd("export: `", cmdstruc->old_stdout);
		ft_putstr_fd(cmd, cmdstruc->old_stdout);
		ft_putstr_fd("': not a valid identifier\n", cmdstruc->old_stdout);
	}
	else if (error == 3)
	{
		ft_putstr_fd(&cmd[i], cmdstruc->old_stdout);
		ft_putstr_fd(": event not found\n", cmdstruc->old_stdout);
	}
}
