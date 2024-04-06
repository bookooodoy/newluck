/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 08:19:13 by nraymond          #+#    #+#             */
/*   Updated: 2024/04/06 15:56:19 by nraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

char	*ft_strncpy(char *dst, const char *src, size_t size)
{
	size_t	index;

	index = 0;
	if (!src)
	{
		while (index < size)
			dst[index++] = 0;
		return (dst);
	}
	if (size > 0)
	{
		while (src[index] && (index < (size - 1)))
		{
			dst[index] = src[index];
			index++;
		}
		while (index < size - 1)
			dst[index++] = 0;
	}
	dst[index] = 0;
	return (dst);
}
