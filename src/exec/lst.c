/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:49:42 by lveloso           #+#    #+#             */
/*   Updated: 2023/03/23 10:59:59 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_parsing	*ft_lst_last_exec(t_parsing *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_parsing	*ft_lst_new_exec(char *pathcmd)
{
	t_parsing	*elem;

	elem = malloc(sizeof(t_parsing));
	if (elem == NULL)
		return (NULL);
	elem->pathcmd = pathcmd;
	elem->next = NULL;
	return (elem);
}

void	ft_lst_add_back_exec(t_parsing **lst, t_parsing *new)
{
	t_parsing	*temp;

	if (lst == NULL)
		return ;
	if ((*lst) == NULL)
		*lst = new;
	else
	{	
		temp = ft_lst_last_exec(*lst);
		temp->next = new;
	}			
}

int	ft_lst_size_exec(t_parsing *lst)
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

void	free_stack_exec(t_parsing **pile)
{
	t_parsing	*tmp;

	while (*pile)
	{
		tmp = (*pile)->next;
		free(*pile);
		*pile = tmp;
	}
	*pile = NULL;
}
