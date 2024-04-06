/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 08:10:35 by nraymond          #+#    #+#             */
/*   Updated: 2024/04/06 13:13:48 by nraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_buf	g_message_buffer = {.buffer = NULL, .size = 0, .index = 0};

char	*ft_realloc(char *ptr, size_t newsize)
{
	char	*newptr;

	if (ptr == 0)
		return (malloc(sizeof(ptr) * newsize + 1));
	newptr = malloc(sizeof(char) * newsize + 1);
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
	kill(pid, SIGUSR2);
	exit(EXIT_FAILURE);
}

void	print_string(t_buf *db)
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

void	handler_sigusr(int signum, siginfo_t *info, void *context)
{
	static char	c = 0xFF;
	static int	bits = 0;
	static int	pid = 0;
	
	(void)context;
	if (info->si_pid)
		pid = info->si_pid;
	if (signum == SIGUSR1)
		c ^= 0x80 >> bits;
	else if (signum == SIGUSR2)
		c |= 0x80 >> bits;
	if (++bits == 8)
	{
		if (c)
		{
			if (g_message_buffer.index >= g_message_buffer.size)
			{
				if (g_message_buffer.size)
					g_message_buffer.size = g_message_buffer.size * 2;
				else
					g_message_buffer.size = 1024;
				g_message_buffer.buffer = ft_realloc(g_message_buffer.buffer, g_message_buffer.size);
				if (!g_message_buffer.buffer)
				{
					error(pid, NULL);
					return;
				}
			}
			g_message_buffer.buffer[g_message_buffer.index++] = c;
		}
		else
			print_string(&g_message_buffer);
		bits = 0;
		c = 0xFF;
	}
	if (kill(pid, SIGUSR1) == -1)
		error(pid, NULL);
}

void	ft_putnbr(ssize_t pid)
{
	char	p;

	if (pid >= 10)
		ft_putnbr(pid / 10);
	p = (pid % 10) + '0';
	if (write(1, &p, 1) == -1)
		exit(EXIT_FAILURE);
}

int	main(void)
{
	struct sigaction	sa_signal;
	sigset_t			block_mask;

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	sa_signal.sa_handler = 0;
	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_mask = block_mask;
	sa_signal.sa_sigaction = handler_sigusr;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	ft_putnbr(getpid());
	ft_putstr_fd("\n", 1);
	while (1)
		pause();
}
