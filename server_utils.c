/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:20:25 by nraymond          #+#    #+#             */
/*   Updated: 2024/04/06 16:28:23 by nraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_realloc(char *ptr, size_t newsize)
{
	char	*newptr;

	if (ptr == NULL)
		return (ft_calloc(sizeof(char), newsize + 1));
	if (!newsize)
		return (ptr);
	newptr = ft_calloc(sizeof(char), newsize + 1);
	if (!newptr)
		return (NULL);
	ft_strncpy(newptr, ptr, newsize);
	free(ptr);
	return (newptr);
}

void	error(int pid, char *str)
{
	if (str)
		free(str);
	ft_putstr_fd("Error from server: cannot send back normal signal\n", 2);
	if (pid > 0)
		kill(pid, SIGUSR2);
	exit(EXIT_FAILURE);
}

void	print_string(t_buf *db)
{
	if (db->index > 0)
	{
		if (db->buffer)
		{
			db->buffer[db->index] = 0;
			if (ft_putstr_fd(db->buffer, 1) == -1
				|| ft_putstr_fd("\n", 1) == -1)
			{
				free(db->buffer);
				exit(EXIT_FAILURE);
				return ;
			}
		}
		free(db->buffer);
		db->buffer = NULL;
		db->size = 0;
		db->index = 0;
	}
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			index;

	p = s;
	index = 0;
	while (index < n)
		p[index++] = '\0';
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tab;

	if ((nmemb == 0) || (size == 0))
		return (malloc(0));
	else if ((nmemb * size) / size != nmemb)
		return ((void *)0);
	tab = malloc(size * nmemb);
	if (!tab)
		return (NULL);
	ft_bzero(tab, (nmemb * size));
	return ((void *)tab);
}
