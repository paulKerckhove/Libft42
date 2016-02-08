/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkerckho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:59:04 by pkerckho          #+#    #+#             */
/*   Updated: 2016/02/08 16:00:33 by pkerckho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/*
** this function creates a new nodes and gives it an empty string if there is
** none before it, then it creates a new node everytime there is something else
** to read.
*/

static t_list	*ft_findfd(t_list **begin, int fd)
{
	t_list *tmp;

	tmp = *begin;
	if (tmp)
	{
		while (tmp)
		{
			if (fd == (int)tmp->content_size)
				return (tmp);
			tmp = tmp->next;
		}
	}
	tmp = ft_lstnew("\0", 1);
	tmp->content_size = fd;
	ft_lstadd(begin, tmp);
	return (tmp);
}

static char		*ft_freejoin(char *tmp, char *buf, int ret)
{
	char	*l;

	l = tmp;
	tmp = ft_strnjoin(tmp, buf, ret);
	free(l);
	return (tmp);
}

/*
** In this function after checking if the read asn't failed we first get into
** our linked list and we create the first node.
** The first while is looking of any \n and is joinning all that we've been
** (BUFF_SIZE)
** Second while : while the strings exist as a char * (cast from void*) we are
** looking for a \n , if we are able to find one we copy what we had before it
** with ft_strndup and we put it into our linked list.
** The Second if locates the \n and use ++ret so we can avoid it for the next
** step, we then use the variable l to temporary hold what is currently in
** list->content. Ad we use ft_strdup to alocate the memory for our current
** position in list->content based on the variable ret (++\n) and we free
** what's inside l from our memory.
** The ternary operator is used to return (1) at the end of a line and at the
** end of a file (\n or \0) and once we call gnl again he returns 0.
*/

int				get_next_line(int const fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	static t_list	*list = NULL;
	t_list			*begin;
	char			*l;

	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	begin = list;
	list = ft_findfd(&begin, fd);
	while (!ft_strchr(list->content, '\n') && (ret = read(fd, buf, BUFF_SIZE)))
		list->content = ft_freejoin(list->content, buf, ret);
	ret = 0;
	while (((char *)list->content)[ret] && ((char *)list->content)[ret] != '\n')
		++ret;
	*line = ft_strndup(list->content, ret);
	if (((char *)list->content)[ret] == '\n')
		++ret;
	l = list->content;
	list->content = ft_strdup(list->content + ret);
	free(l);
	list = begin;
	return (ret ? 1 : 0);
}
