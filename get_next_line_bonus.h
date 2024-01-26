/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:17:45 by arodgers          #+#    #+#             */
/*   Updated: 2023/11/01 13:18:02 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_list
{
	char			*cont;
	struct s_list	*next;
}	t_list;

typedef struct s_clean
{
	t_list	*new_node;
	t_list	*last;
	char	*new_line;
	int		i;
	int		j;
}	t_clean;

char	*get_next_line(int fd);
char	*fetch_line(t_list *list);

int		find_newline(t_list *list);
int		get_len(t_list *lst);

t_list	*ft_lstlast(t_list *lst);

void	add_to_node(t_list **list, char *buffer);
int		clean_list(t_list **list);
void	create_list(t_list **list, int fd);
void	copy_chars(t_list *list, char *str);
void	free_list(t_list **list, t_list *clean_node, char *new_line);

#endif
