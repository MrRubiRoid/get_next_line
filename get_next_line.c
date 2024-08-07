/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbalando <nbalando@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:59:12 by nbalando          #+#    #+#             */
/*   Updated: 2024/08/07 22:10:12 by nbalando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char *ft_rewrite(char *temp)
{
	int i;
	int j;
	char *just_a_buffer;

	i = 0;
	while(temp[i] != '\n')
		i++;
	just_a_buffer = ft_calloc(BUFFER_SIZE - i + 1, sizeof(char));
	j = 0;
	while(temp[i++] != '\0')
		just_a_buffer[j] = temp[i];
	free(temp);
	return(just_a_buffer);
}

static char *ft_append (char *main_buffer, char *temp)
{
	int i;
	int j;
	char *third;

	third = ft_calloc(strlen(main_buffer) + strlen(temp) + 1, sizeof(char));
	i = 0;
	while (main_buffer[i++] != '\0')
		third[i] = main_buffer[i];
	j = 0;
	while (temp[j] != '\0' && temp[j] != '\n')
		third[i++] = temp[j++];
	temp = ft_rewrite(temp);
	return (third);
}

static char* create_line(char *main_buffer, int fd)
{
	char *temp;

	temp = calloc(BUFFER_SIZE, sizeof(char));
	if(!main_buffer)
		main_buffer = ft_calloc(1, 1);
	while(read(fd, temp, BUFFER_SIZE) >= 0)
	{
		main_buffer = ft_append(main_buffer, temp);
	}
	return (main_buffer);
}
char *get_next_line (int fd)
{
	static char* main_buffer;
	char *new_line;

	if(BUFFER_SIZE <= 0)
		return ("invalid BUFFER_SIZE");
	if(fd < 0)
		return ("nothing to read");
	main_buffer = create_line(main_buffer, fd);

	return (new_line);
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