/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:44:55 by jmendez           #+#    #+#             */
/*   Updated: 2022/11/29 15:32:58 by jmendez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	found_newline(t_list *stock)
{
	int		i;
	t_list	*current;

	if (!stock)
		return (0);
	current = ft_lst_get_last(stock);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*ft_lst_get_last(t_list *stock)
{
	t_list	*current;

	current = stock;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	generate_line(char **line, t_list *stock)
{
	int	i;
	int	len;

	len = 0;
	while (stock)
	{
		i = 0;
		while (stock->content[i])
		{
			if (stock->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stock = stock->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return ;
}

void	free_stock(t_list *stock)
{
	t_list	*current;
	t_list	*next;

	current = stock;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	howmuch;

	howmuch = 0;
	while (*str++)
		howmuch++;
	return (howmuch);
}
