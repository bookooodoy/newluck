/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 08:11:04 by nraymond          #+#    #+#             */
/*   Updated: 2024/04/06 14:29:05 by nraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define MAX_BUFFER_SIZE 1024
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef	struct	s_buf
{
	char	*buffer;
	size_t	size;
	size_t	index;
}				t_buf;

//server
char    *ft_realloc(char *ptr, size_t newsize);
void    error(int pid, char *str);
void    print_string(t_buf *db);
void    ft_putnbr(ssize_t pid);

//client
int     send_null(int pid, char *str);
int     check_input(int argc, char **argv);
void	ft_error(char *str);

// utils
int     ft_putstr_fd(char *s, int fd);
size_t  ft_strlen(const char *s);
char    *ft_straddc_first(char c);
char    *ft_straddc(char *str, char c);
int	ft_atoi(const char *nptr);
char	*ft_strdup(const char *s);
char	*ft_strncpy(char *dst, const char *src, size_t size);

#endif
