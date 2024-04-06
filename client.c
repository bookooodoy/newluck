/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 08:09:49 by nraymond          #+#    #+#             */
/*   Updated: 2024/04/06 19:16:55 by nraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_error(char *str)
{
	if (str)
		free(str);
	ft_putstr_fd("Unexpected Error occured\n", 2);
	exit(EXIT_FAILURE);
}

int	ctoa(int pid, char *str)
{
	static char	*message = (void *)0;
	static int	s_pid = 0;
	static int	bits = -1;

	if (str)
		message = ft_strdup(str);
	if (!message)
		ft_error(0);
	if (pid)
		s_pid = pid;
	if ((bits / 8 < (int)ft_strlen(message)) && message[++bits / 8])
	{
		if (message[bits / 8] & (0x80 >> (bits % 8)))
		{
			if (kill(s_pid, SIGUSR2) == -1)
				ft_error(message);
		}
		else if (kill(s_pid, SIGUSR1) == -1)
			ft_error(message);
		return (0);
	}
	if (!send_null(s_pid, message))
		return (0);
	return (free(message), 1);
}

void	handler_sigusr(int signum)
{
	int	end;

	end = 0;
	if (signum == SIGUSR1)
		end = ctoa(0, 0);
	else if (signum == SIGUSR2)
	{
		ft_putstr_fd("Error from server: exiting the program\n", 2);
		exit(EXIT_FAILURE);
	}
	if (end)
		exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !check_input(argc, argv))
	{
		ft_putstr_fd("Invalid arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, handler_sigusr);
	signal(SIGUSR2, handler_sigusr);
	ctoa(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
}
