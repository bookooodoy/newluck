/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:22:26 by nraymond          #+#    #+#             */
/*   Updated: 2024/04/06 14:30:42 by nraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int     send_null(int pid, char *str)
{
        static int      i = 0;

        if (i++ != 8)
        {
                if (kill(pid, SIGUSR1) == -1)
                        error(0, str);
                return (0);
        }
        return (1);
}


int     check_input(int argc, char **argv)
{
        int     val;

        if (argc != 3)
                return (ft_putstr_fd("Incorrect number of arguments\n", 2), 0);
        if (!argv[1][0] || !argv[2][0])
                return (ft_putstr_fd("Empty arguments\n", 2), 0);
        val = ft_atoi(argv[1]);
        if (val <= 0)
                return (ft_putstr_fd("Error with PID\n", 2), 0);
        return (1);
}
