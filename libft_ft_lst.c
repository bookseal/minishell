/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_ft_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:43:34 by gichlee           #+#    #+#             */
/*   Updated: 2023/07/27 14:46:43 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_lstadd_back(t_pipex **lst, t_pipex *new)
{
	t_pipex	*head;
	t_pipex	*temp_lst;

	head = *lst;
	if (head == 0)
		*lst = new;
	else
	{
		temp_lst = head;
		while (temp_lst->next != 0)
			temp_lst = temp_lst->next;
		temp_lst->next = new;
	}
}

t_pipex	*ft_lstlast(t_pipex *lst)
{
	t_pipex	*temp_lst;

	temp_lst = lst;
	if (temp_lst)
	{
		while (temp_lst->next != 0)
			temp_lst = temp_lst->next;
	}
	return (temp_lst);
}
