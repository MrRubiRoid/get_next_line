/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:44:05 by nbalando          #+#    #+#             */
/*   Updated: 2024/08/11 06:46:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	if (!s)
	{
		s = ft_calloc(1, sizeof(char));
		if (!s)
			return (0);
	}
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	else
		return (NULL);
}

void	*ft_memset(void *array, int c, size_t n)
{
	unsigned char	*buffer;

	buffer = (unsigned char *)array;
	while (n--)
		*buffer++ = (unsigned char)c;
	return (array);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memory;
	size_t	nbytes;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	nbytes = nmemb * size;
	memory = malloc(nbytes);
	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, nbytes);
	return (memory);
}
char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
size_t	ft_strlen(const char *c)
{
	int len;

	len = 0;
	while (c[len] != '\0')
	{
		len++;
	}
	return (len);
}
