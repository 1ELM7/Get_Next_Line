/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:15:53 by jmendez           #+#    #+#             */
/*   Updated: 2022/11/29 19:36:30 by jmendez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
int		found_newline(t_list *stock);
t_list	*ft_lst_get_last(t_list *stock);
void	read_stock(int fd, t_list **stock);
void	add_stock(t_list **stock, char *buf, int passed);
void	extract_line(t_list *stock, char **line);
void	generate_line(char **line, t_list *stock);
void	clean_stock(t_list **stock);
size_t	ft_strlen(const char *str);
void	free_stock(t_list *stock);
#endif
