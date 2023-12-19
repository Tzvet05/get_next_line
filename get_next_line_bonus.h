/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:05:17 by ttrave            #+#    #+#             */
/*   Updated: 2023/11/08 17:05:21 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	char			*content;
	size_t			len;
	size_t			i;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
char	*ft_join_lst(t_list **fd_arr, int fd, char *next_line, t_list *ptr);
char	*ft_alloc_next_line(t_list **fd_arr, int fd, char *next_line);
size_t	ft_parse_next_line(t_list **fd_arr, int fd);

size_t	ft_lstnew_back(t_list **fd_arr, int fd, char *content, size_t len);
void	ft_reinit_lst(t_list **fd_arr, int fd);
size_t	ft_in(char *s, size_t i_start, size_t len);
char	*ft_lstclear(t_list **lst);

#endif
