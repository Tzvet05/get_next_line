/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:05:28 by ttrave            #+#    #+#             */
/*   Updated: 2023/11/19 21:31:15 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_parse_next_line(t_list **fd_arr, int fd)
{
	int		len_read;
	char	*buffer;

	len_read = BUFFER_SIZE;
	buffer = NULL;
	while (len_read == BUFFER_SIZE && !ft_in(buffer, 0, BUFFER_SIZE))
	{
		buffer = malloc(BUFFER_SIZE * sizeof(char));
		if (!buffer)
			return (!ft_lstclear(&fd_arr[fd]));
		len_read = read(fd, buffer, BUFFER_SIZE);
		if (len_read == -1)
		{
			free(buffer);
			return (!ft_lstclear(&fd_arr[fd]));
		}
		if (!len_read)
			free (buffer);
		else if (ft_lstnew_back(fd_arr, fd, buffer, len_read))
			return (1);
	}
	return (0);
}

char	*ft_join_lst(t_list **fd_arr, int fd, char *next_line, t_list *ptr)
{
	size_t	i;
	size_t	j;

	i = 0;
	ptr = fd_arr[fd];
	j = ptr->i;
	next_line = ft_alloc_next_line(fd_arr, fd, next_line);
	if (!next_line)
		return (NULL);
	while (ptr && !(j >= ptr->len && ptr->len < BUFFER_SIZE))
	{
		next_line[i] = ptr->content[j];
		if (ptr->content[j] == '\n')
			break ;
		if (j + 1 >= ptr->len)
		{
			ptr = ptr->next;
			j = 0;
		}
		else
			j++;
		i++;
	}
	ft_reinit_lst(fd_arr, fd);
	return (next_line);
}

char	*ft_alloc_next_line(t_list **fd_arr, int fd, char *next_line)
{
	t_list	*ptr;
	size_t	len;
	size_t	i;

	len = 0;
	ptr = fd_arr[fd];
	i = ptr->i;
	while (ptr && !(i >= ptr->len && ptr->len < BUFFER_SIZE))
	{
		len++;
		if (ptr->content[i] == '\n')
			break ;
		if (i + 1 >= ptr->len)
		{
			ptr = ptr->next;
			i = 0;
		}
		else
			i++;
	}
	next_line = malloc((len + 1) * sizeof(char));
	if (!next_line)
		return (NULL);
	next_line[len] = '\0';
	return (next_line);
}

char	*get_next_line(int fd)
{
	char			*next_line;
	static t_list	*fd_arr[1024] = {NULL};
	t_list			*ptr;

	next_line = NULL;
	ptr = NULL;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!fd_arr[fd] || (fd_arr[fd]->len == BUFFER_SIZE
			&& !ft_in(fd_arr[fd]->content, fd_arr[fd]->i, fd_arr[fd]->len)))
	{
		if (ft_parse_next_line(fd_arr, fd))
			return (NULL);
	}
	if (!fd_arr[fd])
		return (NULL);
	if (fd_arr[fd])
	{
		next_line = ft_join_lst(fd_arr, fd, next_line, ptr);
		if (!next_line)
			return (ft_lstclear(&fd_arr[fd]));
	}
	return (next_line);
}
