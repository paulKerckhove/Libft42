/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkerckho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 11:16:08 by pkerckho          #+#    #+#             */
/*   Updated: 2016/01/25 11:16:11 by pkerckho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstaddend(t_list **alst, t_list *new)
{
	t_list		*tmp;

	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = NULL;
	tmp = new;
}
