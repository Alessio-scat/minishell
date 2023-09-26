/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:23:10 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/25 10:25:45 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	cd_tild(void)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strdup(getenv("HOME"));
	ft_builtin_cd(tmp);
	free(tmp);
}
