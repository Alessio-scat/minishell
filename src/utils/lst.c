/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:11:39 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/16 15:09:59 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_export	*ft_lst_last(t_export *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_export	*ft_lst_new(char *content, char *variable)
{
	t_export	*elem;

	elem = malloc(sizeof(t_export));
	if (elem == NULL)
		return (NULL);
	if (content == NULL)
		elem->content = NULL;
	else
		elem->content = content;
	elem->variable = variable;
	elem->next = NULL;
	return (elem);
}

void	ft_lst_add_back(t_export **lst, t_export *new)
{
	t_export	*end;

	if (lst == NULL)
		return ;
	end = ft_lst_last(*lst);
	if (end != NULL)
		end->next = new;
	else
		*lst = new;
}

int	ft_lst_size(t_export *lst)
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

void	free_stack(t_export **pile)
{
	t_export	*tmp;

	while (*pile)
	{
		tmp = (*pile)->next;
		free(*pile);
		*pile = tmp;
	}
	*pile = NULL;
}
