/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:37:05 by nbalando          #+#    #+#             */
/*   Updated: 2024/08/11 19:04:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	release_memory(char **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

size_t	string_length(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
	{
		return (0);
	}
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

void	*safe_allocate(size_t count, size_t size)
{
	unsigned char	*mem;
	size_t			total;

	if (count && SIZE_MAX / count < size)
		return (NULL);
	total = (count * size) - 1;
	mem = malloc(count * size);
	if (!mem)
		return (0);
	while (total + 1 > 0)
	{
		mem[total] = 0;
		total--;
	}
	return ((void *)mem);
}

char	*find_char(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
	{
		return ((char *)str);
	}
	return (NULL);
}

char	*string_combine(const char *s1, const char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	result = malloc(string_length(s1) + string_length(s2) + 1);
	if (!result)
		return (0);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while (s2 && s2[i])
	{
		result[j + i] = s2[i];
		i++;
	}
	result[j + i] = 0;
	return (result);
}
