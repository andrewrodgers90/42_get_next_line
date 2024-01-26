/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:00:23 by arodgers          #+#    #+#             */
/*   Updated: 2023/12/29 18:28:10 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (NULL == lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	find_newline(t_list *list)
{
	int	i;

	if (NULL == list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->cont[i] && i < BUFFER_SIZE)
		{
			if (list->cont[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	copy_chars(t_list *list, char *str)
{
	int	i;
	int	k;

	if (NULL == list)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->cont[i])
		{
			if (list->cont[i] == '\n')
			{
				//str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k] = list->cont[i];
			k++;
			i++;
		}
		list = list->next;
	}
	str[k] = '\0';
}

int	get_len(t_list *list)
{
	int	len;
	int	i;

	if (NULL == list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->cont[i])
		{
			if (list->cont[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

char	*fetch_line(t_list *list)
{
	char	*next_line;
	int		len;

	if (NULL == list)
		return (NULL);
	len = get_len(list);
	next_line = malloc(len + 1);
	if (NULL == next_line)
		return (NULL);
	copy_chars(list, next_line);
	return (next_line);
}
