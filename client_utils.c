/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:22:26 by nraymond          #+#    #+#             */
/*   Updated: 2024/04/06 15:06:49 by nraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_null(int pid, char *str)
{
	static int	i = 0;

	if (i++ != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			error(0, str);
		return (0);
	}
	return (1);
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

int	ft_atoi(const char *nptr)
{
	long int	to_ret;
	int			i;
	int			sign;

	to_ret = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while ((nptr[i] >= 48 && nptr[i] <= 57))
	{
		to_ret = (10 * to_ret) + (nptr[i] - '0');
		if (to_ret * sign > 2147483647 || to_ret * sign < -2147483648)
			return (0);
		i++;
	}
	return ((int)to_ret * sign);
}

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	if (fd <= 0)
		return (0);
	while (s[++i])
	{
		if (write(fd, &s[i], 1) == -1)
			return (0);
	}
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
