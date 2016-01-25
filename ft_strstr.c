/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkerckho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 11:23:56 by pkerckho          #+#    #+#             */
/*   Updated: 2016/01/25 11:23:57 by pkerckho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (s1[0] == '\0' && s2[0] == '\0')
		return ((char *)s1);
	while (s1[i] != '\0')
	{
		j = 0;
		while (s2[j] != '\0' && s1[i + j] == s2[j])
			j++;
		if (s2[j] == '\0')
			return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}
