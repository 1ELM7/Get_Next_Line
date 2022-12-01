/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:15:29 by jmendez           #+#    #+#             */
/*   Updated: 2022/11/29 19:42:10 by jmendez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stock = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	read_stock(fd, &stock);
	if (!stock)
		return (NULL);
	extract_line(stock, &line);
	clean_stock(&stock);
	if (line[0] == '\0')
	{
		free_stock(stock);
		stock = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_stock(int fd, t_list **stock)
{
	char	*buf;
	int		passed;

	passed = 1;
	while (!found_newline(*stock) && passed != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		passed = (int)read(fd, buf, BUFFER_SIZE);
		if ((!(*stock) && passed == 0) || passed == -1)
		{
			free(buf);
			return ;
		}
		buf[passed] = '\0';
		add_stock(stock, buf, passed);
		free(buf);
	}
}

void	add_stock(t_list **stock, char *buf, int passed)
{
	int		i;
	t_list	*last;
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->next = NULL;
	new->content = malloc(sizeof(char) * (passed + 1));
	if (new->content == NULL)
		return ;
	i = 0;
	while (buf[i] && i < passed)
	{
		new->content[i] = buf[i];
		i++;
	}
	new->content[i] = '\0';
	if (!(*stock))
	{
		*stock = new;
		return ;
	}
	last = ft_lst_get_last(*stock);
	last->next = new;
}

void	extract_line(t_list *stock, char **line)
{
	int	i;
	int	j;

	if (!stock)
		return ;
	generate_line(line, stock);
	if (!(*line))
		return ;
	j = 0;
	while (stock)
	{
		i = 0;
		while (stock->content[i])
		{
			if (stock->content[i] == '\n')
			{
				(*line)[j++] = stock->content[i];
				break ;
			}
			(*line)[j++] = stock->content[i++];
		}
		stock = stock->next;
	}
	(*line)[j] = '\0';
}

void	clean_stock(t_list **stock)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		j;

	clean = malloc(sizeof(t_list));
	if (!stock || !clean)
		return ;
	clean->next = NULL;
	last = ft_lst_get_last(*stock);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean->content = malloc(sizeof(char) * (ft_strlen(last->content) - i) + 1);
	if (!clean->content)
		return ;
	j = 0;
	while (last->content[i])
		clean->content[j++] = last->content[i++];
	clean->content[j] = '\0';
	free_stock(*stock);
	*stock = clean;
}
