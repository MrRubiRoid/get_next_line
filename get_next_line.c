/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:59:12 by nbalando          #+#    #+#             */
/*   Updated: 2024/08/11 07:05:50 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	buf3 = ft_calloc(ft_strlen(buf1) + ft_strlen(buf2) + 1, sizeof(char));
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

static char	*before_nl(char *buf1)
{
	int		len;
	char	*temp;

	if (!*buf1) // check if the pointer itself is null
		return (NULL);
	len = 0;
	while (buf1[len] != '\0')
	{
		if (buf1[len++] == '\n')
			break;
	}
	temp = ft_calloc(len + 1, sizeof(char));
	while (--len >= 0)
		temp[len] = buf1[len];
		
	return (temp);
}

static char	*after_nl(char *buf1)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (buf1[i] != '\0' && buf1[i] != '\n')
		i++;
	temp = ft_calloc(ft_strlen(buf1) - i + 1, sizeof(char));
	if	(!temp)
		return (NULL);
	j = 0;
	while (buf1[++i] != '\0')
	{
		temp[j] = buf1[i];
		j++;
	}
	free(buf1);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*buf1;
	char		*buf2;
	char		*result;
	int			read_size;

	result = NULL;
	if (BUFFER_SIZE <= 0)
		return ("invalid BUFFER_SIZE");
	if (fd < 0)
		return ("invalid fd");
	buf2 = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (!ft_strchr(buf1, '\n'))
	{
		read_size = read(fd, buf2, BUFFER_SIZE);
		if (read_size == 0)
			break;
		buf1 = ft_append_and_free(buf1, buf2);
	}
	result = before_nl(buf1);
	buf1 = after_nl(buf1);
	free(buf2);
	return (result);
}

// int main (void)
// {
// 	char *line;
// 	int fd;

// 	fd = open("text.txt", O_RDWR);
// 	printf("fd = %d\n", fd);
// 	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
// 	while ((line = get_next_line(fd)))
// 		printf("%s", line);
// 	printf("HAPPY END");
// 	return(0);
// }
