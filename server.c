/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 08:10:35 by nraymond          #+#    #+#             */
/*   Updated: 2024/04/06 14:56:30 by nraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_buf	g_message_buffer = {.buffer = NULL, .size = 0, .index = 0};

void	set_gmsg(int c, int pid)
{
	if (g_message_buffer.index >= g_message_buffer.size)
	{
		if (g_message_buffer.size)
			g_message_buffer.size = g_message_buffer.size * 2;
		else
			g_message_buffer.size = 1024;
		g_message_buffer.buffer = ft_realloc(
				g_message_buffer.buffer, g_message_buffer.size);
		if (!g_message_buffer.buffer)
		{
			error(pid, NULL);
			return ;
		}
	}
	g_message_buffer.buffer[g_message_buffer.index++] = c;
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
			set_gmsg(c, pid);
		else
			print_string(&g_message_buffer);
		bits = 0;
		c = 0xFF;
	}
	if (kill(pid, SIGUSR1) == -1)
		error(pid, NULL);
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
