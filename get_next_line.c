/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:13:02 by arodgers          #+#    #+#             */
/*   Updated: 2023/12/29 17:07:14 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_list(t_list **list, t_list *clean_node, char *new_line)
{
	t_list	*temp;

	if (NULL == *list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->cont);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (clean_node && clean_node->cont[0])
		*list = clean_node;
	else
	{
		free(new_line);
		free(clean_node);
	}
}

void	add_to_node(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_lstlast(*list);
	new_node = malloc(sizeof(t_list));
	if (NULL == new_node)
	{
		free(buffer);
		free_list(list, NULL, NULL);
		return ;
	}
	if (NULL == last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->cont = buffer;
	new_node->next = NULL;
}

int	clean_list(t_list **list)
{
	t_clean	cln;

	cln.new_node = malloc(sizeof(t_list));
	if (NULL == cln.new_node)
		return (1);
	cln.new_line = malloc(BUFFER_SIZE + 1);
	if (NULL == cln.new_line)
	{
		free(cln.new_node);
		return (1);
	}
	cln.last = ft_lstlast(*list);
	cln.i = 0;
	cln.j = 0;
	while (cln.last->cont[cln.i] != '\n' && cln.last->cont[cln.i] != '\0')
		cln.i++;
	while (cln.last->cont[cln.i] != '\0' && cln.last->cont[cln.i++])
		cln.new_line[cln.j++] = cln.last->cont[cln.i];
	cln.new_line[cln.j] = '\0';
	cln.new_node->cont = cln.new_line;
	cln.new_node->next = NULL;
	free_list(list, cln.new_node, cln.new_line);
	return (0);
}

void	create_list(t_list **list, int fd)
{
	char	*buffer;
	int		chars_read;

	while (!find_newline(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (NULL == buffer)
		{
			free_list(list, NULL, NULL);
			return ;
		}
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read <= 0)
		{
			free(buffer);
			if (chars_read < 0)
				free_list(list, NULL, NULL);
			return ;
		}
		buffer[chars_read] = '\0';
		add_to_node(list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, &next_line, 0) < 0)
	{
		if (list)
			free_list(&list, NULL, NULL);
		return (NULL);
	}
	create_list(&list, fd);
	if (NULL == list)
		return (NULL);
	next_line = fetch_line(list);
	if (!next_line || clean_list(&list))
	{
		free_list(&list, NULL, NULL);
		free(next_line);
		return (NULL);
	}
	return (next_line);
}
