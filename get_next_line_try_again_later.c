/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbalando <nbalando@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:59:37 by nbalando          #+#    #+#             */
/*   Updated: 2024/08/06 22:55:03 by nbalando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static void	ft_free_string_array(char **string_array)
{
	free(*string_array);
	*string_array = NULL;
}

char *ft_rewrite(char *str)
{
	int i;
	int j;
	char *temp = ft_calloc(BUFFER_SIZE, sizeof(char));

	i = 0;
	while(str[i] != '\n')
		i++;
	j = 0;
	while(str[i] != '\0')
	{
		temp[j] = str[i];
		i++;
		j++;
	}
	ft_bzero(str, i);
	i = 0;
	while(temp[i])
	{
		str[i] = temp[i];
		i++;
	}
	return(str);
}
static char *ft_append (char *first, char *second)
{
	if(!first)
		return(second);
	printf("I am here, however i shouldnt\n");
	int i;
	int j;

	i = 0;
	j = 0;
	while(first[i])
		i++;
	while (second[j] != '\0' && second[i] != '\n')
		first[i++] = second[j++];
	ft_rewrite(second);
	return (first);
}

	// char *temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	// char *result = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	// int a = read(fd, temp, BUFFER_SIZE);
	// // main_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	// while(a > 0)
	// {
	// 	main_buffer = ft_append(main_buffer, temp); // the problem is here
	// 	if (ft_strchr(temp,'\n'))
	// 	{
	// 		result = main_buffer;
	// 		ft_free_string_array(&main_buffer);
	// 		main_buffer = temp;
	// 		break;
	// 	}
	// }

char *get_next_line(int fd)
{
	static char *main_buffer;
	char *result;

	// protrection
	if (fd > 4000 || BUFFER_SIZE <= 0)
		return NULL;
	// if new line already exists than dont read again, extract it and return
	if (ft_strchr(main_buffer, '\n'))
	{
		result = exctract_till_new_line(main_buffer);
		main_buffer = exctract_after_new_line(main_buffer);
		return result;
	}
	// if new line doesnt exist than read untill face a NL or read fails or malloc fails or file is read compl
	while (!ft_strchr(main_buffer, '\n'))
	{
		// everytime it appends to main_buffer read chars
		int status = read_one_more_time(&main_buffer);
		if (status < 0)
			return (ft_free_string_array(&main_buffer), NULL);
		if (status == 0)
			break;
	}
	// if new line already exists than dont read again, extract it and return
	if (ft_strchr(main_buffer, '\n'))
	{
		result = exctract_till_new_line(main_buffer);
		main_buffer = exctract_after_new_line(main_buffer);
	}
	return(result);
}

int main (void)
{
	char *line;
	int fd;

	fd = open("text.txt", O_RDWR);
	printf("fd = %d\n", fd);
	line = get_next_line(fd);
	printf("line %s", line);
	return(0);
}