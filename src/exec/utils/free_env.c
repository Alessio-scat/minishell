/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:41:09 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/25 10:37:26 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	verif_strdup(char **env, char **envtmp)
{
	if (env[2] == NULL)
	{
		free_2d(envtmp);
		free_2d(env);
		exit(-2);
	}
}
