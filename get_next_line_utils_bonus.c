/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:05:39 by ttrave            #+#    #+#             */
/*   Updated: 2023/11/17 19:13:47 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_lstclear(t_list **lst)
{
	t_list	*ptr1;
	t_list	*ptr2;

	ptr1 = *lst;
	*lst = NULL;
	while (ptr1)
	{
		ptr2 = ptr1->next;
		free(ptr1->content);
		free(ptr1);
		ptr1 = ptr2;
	}
	return (NULL);
}

size_t	ft_lstnew_back(t_list **fd_arr, int fd, char *content, size_t len)
{
	t_list	*new;
	t_list	*lst;

	new = malloc(sizeof(t_list));
	if (!new)
	{
		free(content);
		return (!ft_lstclear(&fd_arr[fd]));
	}
	new->content = content;
	new->len = len;
	new->i = 0;
	new->next = NULL;
	if (!fd_arr[fd])
		fd_arr[fd] = new;
	else
	{
		lst = fd_arr[fd];
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
	return (0);
}

void	ft_reinit_lst(t_list **fd_arr, int fd)
{
	t_list	*ptr1;
	t_list	*ptr2;
	size_t	i;

	i = 0;
	ptr1 = fd_arr[fd];
	while (ptr1->next)
	{
		ptr2 = ptr1->next;
		free(ptr1->content);
		free(ptr1);
		ptr1 = ptr2;
	}
	fd_arr[fd] = ptr1;
	i = fd_arr[fd]->i;
	while (i < fd_arr[fd]->len && fd_arr[fd]->content[i] != '\n')
		i++;
	i += (i < fd_arr[fd]->len && fd_arr[fd]->content[i] == '\n');
	fd_arr[fd]->i = i;
	if (fd_arr[fd]->i >= fd_arr[fd]->len)
	{
		free(fd_arr[fd]->content);
		free(fd_arr[fd]);
		fd_arr[fd] = NULL;
	}
}

size_t	ft_in(char *s, size_t i_start, size_t len)
{
	if (!s || i_start >= len)
		return (0);
	while (i_start < len)
	{
		if (s[i_start] == '\n')
			return (1);
		i_start++;
	}
	return (0);
}
