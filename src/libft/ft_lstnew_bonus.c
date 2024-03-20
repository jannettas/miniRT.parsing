/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:55:35 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/17 12:07:07 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#1.The content to create the new element with.
Return value The new element.
External functs. malloc
Description 
Allocates (with malloc(3)) and returns a new element.
The variable ’content’ is initialized with the value of the parameter ’content’.
The variable ’next’ is initialized to NULL.
*/

t_list	*ft_lstnew(void *content)

{
	t_list	*new;

	new = (t_list *)malloc(sizeof(*new));
	if (!new)
		return (0);
	new->content = content;
	new->next = NULL;
	return (new);
}
