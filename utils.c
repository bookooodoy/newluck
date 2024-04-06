/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 08:19:13 by nraymond          #+#    #+#             */
/*   Updated: 2024/04/06 12:54:23 by nraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

char	*ft_straddc_first(char c)
{
	char	*add;

	add = (char *)malloc(sizeof(char) * 2);
	if (!add)
		return (NULL);
	add[0] = c;
	add[1] = '\0';
	return (add);
}

char	*ft_straddc(char *str, char c)
{
	char	*add;
	int		i;

	if (!c)
		return (NULL);
	if (!str)
		return (ft_straddc_first(c));
	add = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!add)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i])
		add[i] = str[i];
	free(str);
	add[i++] = c;
	add[i] = '\0';
	return (add);
}

static char	*ft_strcpy(char *dst, const char *src)
{
	size_t	index;

	index = 0;
	while (src[index])
	{
		((unsigned char *)dst)[index] = ((unsigned char *)src)[index];
		index++;
	}
	dst[index] = '\0';
	return (dst);
}

char	*ft_strdup(const char *s)
{
	char	*duplicate;

	duplicate = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!(duplicate))
		return (NULL);
	duplicate = ft_strcpy(duplicate, s);
	return ((char *)duplicate);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long int	to_ret;

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

char	*ft_strncpy(char *dst, const char *src, size_t size)
{
	size_t	index;

	index = 0;
	if (size > 0)
	{
		while (src[index] && (index < (size - 1)))
		{
			((unsigned char *)dst)[index] = ((unsigned char *)src)[index];
			index++;
		}
		dst[index] = 0;
	}
	return (dst);
}

