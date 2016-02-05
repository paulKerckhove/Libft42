/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkerckho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:59:04 by pkerckho          #+#    #+#             */
/*   Updated: 2016/02/04 10:21:49 by pkerckho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
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
** In the following function, the ternary ioperator is looking for any existing
** linked list and sets it to NULL.
** While we can't find any \n we join what we read (BUFF_SIZE) if we can find
** one we set our [ret] right after it and copy the previous string in our
** linked list plus the existing \n. Then we free it.
** At the end of our function we us 0 or 1 if there is still something to read
** or if we have reached the end of our file (nothing else to read).
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
	begin = list ? list : NULL;
	list = ft_findfd(&begin, fd);
	while (!ft_strchr(list->content, '\n') && (ret = read(fd, buf, BUFF_SIZE)))
		list->content = ft_freejoin(list->content, buf, ret);
	ret = 0;
	while (((char*)list->content)[ret] && ((char *)list->content)[ret] != '\n')
		++ret;
	*line = ft_strndup(list->content, ret);
	if (((char *)list->content)[ret] == '\n')
		++ret;
	l = list->content;
	list->content = ft_strdup(list->content + ret);
	free(l);
	list = begin;
	if (ret > 0)
		return (1);
	return (0);
}
