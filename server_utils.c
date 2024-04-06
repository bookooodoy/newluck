/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:20:25 by nraymond          #+#    #+#             */
/*   Updated: 2024/04/06 14:31:26 by nraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char    *ft_realloc(char *ptr, size_t newsize)
{
        char    *newptr;

        if (ptr == 0)
                return (malloc(sizeof(ptr) * newsize + 1));
        newptr = malloc(sizeof(char) * newsize + 1);
        if (!newptr)
                return (NULL);
        ft_strncpy(newptr, ptr, newsize);
        free(ptr);
        return (newptr);
}

void    error(int pid, char *str)
{
        if (str)
                free(str);
        ft_putstr_fd("Error from server: cannot send back normal signal\n", 2);
	if (pid > 0)
		kill(pid, SIGUSR2);
        exit(EXIT_FAILURE);
}

void    print_string(t_buf *db)
{
        if (db->index > 0)
        {
                db->buffer[db->index] = '\0';
                ft_putstr_fd(db->buffer, 1);
                ft_putstr_fd("\n", 1);
                free(db->buffer);
                db->buffer = NULL;
                db->size = 0;
                db->index = 0;
        }
}

void    ft_putnbr(ssize_t pid)
{
        char    p;

        if (pid >= 10)
                ft_putnbr(pid / 10);
        p = (pid % 10) + '0';
        if (write(1, &p, 1) == -1)
                exit(EXIT_FAILURE);
}
