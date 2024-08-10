/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:59:12 by nbalando          #+#    #+#             */
/*   Updated: 2024/08/10 21:00:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*ft_append_and_free(char *buf1, char *buf2)
{
	char	*buf3;
	int		i;
	int		j;

	if (!buf1)
	{
		buf1 = ft_calloc(1, sizeof(char));
		if (!buf1 || buf1[0] != '\0')
			return (0);
	}
	buf3 = ft_calloc(strlen(buf1) + strlen(buf2) + 1, sizeof(char));
	if (!buf3)
		return (0);
	i = 0;
	while (buf1[i] != '\0')
	{
		buf3[i] = buf1[i];
		i++;
	}
	j = 0;
	while (buf2[j] != '\0')
		buf3[i++] = buf2[j++];
	free(buf1);
	return (buf3);
}

static int	len_till_nl(const char *buf1)
{
	int	len;

	len = 0;
	while (buf1[len] != '\0' && buf1[len] != '\n')
		len++;
	return (len);
}

static char	*before_nl(char *buf1)
{
	int		len;
	int		i;
	char	*temp;

	len = len_till_nl(buf1);
	temp = ft_calloc(len + 1, sizeof(char));
	i = 0;
	while (buf1[i] != '\0' && buf1[i] != '\n')
	{
		temp[i] = buf1[i];
		i++;
	}
	return (temp);
}

static char	*after_nl(char *buf1)
{
	int		len;
	int		i;
	char	*temp;

	len = len_till_nl(buf1) + 1;
	temp = ft_calloc(strlen(buf1) - len + 1, sizeof(char));
	if	(!temp)
		return (NULL);
	i = 0;
	while (buf1[len] != '\0')
		temp[i++] = buf1[len++];
	free(buf1);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*buf1;
	char		*buf2;
	char		*result;

	// buf1 = NULL;
	result = NULL;
	if (BUFFER_SIZE <= 0)
		return ("invalid BUFFER_SIZE");
	if (fd < 0)
		return ("invalid fd");
	buf2 = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (!(ft_strchr(buf1, '\n')) && (read(fd, buf2, BUFFER_SIZE)) > 0)
	{
		buf1 = ft_append_and_free(buf1, buf2);
		if (ft_strchr(buf1, '\n'))
		{
			result = before_nl(buf1);
			buf1 = after_nl(buf1);
			printf("in the loop :%s|\n", buf1);
			return (result);
		}
	}
	free(buf2);
	return (result);
}
int main (void)
{
	char *line;
	int fd;

	fd = open("text.txt", O_RDWR);
	while ((line = get_next_line(fd)))
		printf("%s\n", line);
	printf("HAPPY END");
	return(0);
}
