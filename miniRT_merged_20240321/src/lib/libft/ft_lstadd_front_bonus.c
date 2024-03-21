/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:12:09 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/22 23:23:14 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
content : The data contained in the element. The void * allows to store any kind
of data.
next : The next element’s address or NULL if it’s the last element.
#1.  The address of a pointer to the first link of
a list.
#2.  The address of a pointer to the element to be
added to the list.
Return value none
External functs. none
Description: Adds the element ’new’ at the beginning of the
list.
*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}
