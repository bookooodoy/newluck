/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 08:09:49 by nraymond          #+#    #+#             */
/*   Updated: 2024/04/06 13:15:59 by nraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error(char *str)
{
	if (str)
		free(str);
	ft_putstr_fd("Unexpected Error occured\n", 2);
	exit(EXIT_FAILURE);
}

int	send_null(int pid, char *str)
{
	static int	i = 0;

	if (i++ != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			error(str);
		return (0);
	}
	return (1);
}

int	send_bit(int pid, char *str)
{
	static char	*message = 0;
	static int	s_pid = 0;
	static int	bits = -1;

	if (str)
		message = ft_strdup(str);
	if (!message)
		error(0);
	if (pid)
		s_pid = pid;
	if (bits / 8 < (int)ft_strlen(message))
	{
		if (message[++bits / 8])
		{
			if (message[bits / 8] & (0x80 >> (bits % 8)))
			{
				if (kill(s_pid, SIGUSR2) == -1)
					error(message);
			}
			else if (kill(s_pid, SIGUSR1) == -1)
				error(message);
			return (0);
		}
	}
	if (!send_null(s_pid, message))
		return (0);
	free(message);
	return (1);
}

void	handler_sigusr(int signum)
{
	int	end;

	end = 0;
	if (signum == SIGUSR1)
		end = send_bit(0, 0);
	else if (signum == SIGUSR2)
	{
		ft_putstr_fd("Error from server: exiting the program\n", 2);
		exit(EXIT_FAILURE);
	}
	if (end)
	{
		ft_putstr_fd("Server sent signal back: message received\n", 2);
		exit(EXIT_SUCCESS);
	}
}

int	check_input(int argc, char **argv)
{
	int	val;

	if (argc != 3)
		return (ft_putstr_fd("Incorrect number of arguments\n", 2), 0);
	if (!argv[1][0] || !argv[2][0])
		return (ft_putstr_fd("Empty arguments\n", 2), 0);
	val = ft_atoi(argv[1]);
	if (val <= 0)
		return (ft_putstr_fd("Error with PID\n", 2), 0);
	return (1);
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
	send_bit(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
}
