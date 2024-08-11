/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbalando <nbalando@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:36:55 by nbalando          #+#    #+#             */
/*   Updated: 2024/08/11 11:44:55 by nbalando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*merge_and_free(char *content, char *chunk, int bytes_read)
{
	char	*temp;

	if (bytes_read <= 0)
	{
		release_memory(&chunk);
		if (bytes_read == -1)
		{
			release_memory(&content);
			return (NULL);
		}
	}
	else
	{
		temp = content;
		content = string_combine(temp, chunk);
		release_memory(&temp);
		release_memory(&chunk);
	}
	if (!content)
	{
		return (NULL);
	}
	return (content);
}

char	*truncate_content(char *content)
{
	char	*new_content;
	int		i;
	int		j;

	if (!content || !*content)
		return (NULL);
	i = 0;
	while (content[i] && content[i] != '\n')
		i++;
	if (!content[i])
	{
		release_memory(&content);
		return (NULL);
	}
	new_content = safe_allocate((string_length(content) - i + 1), sizeof(char));
	if (!new_content)
		return (release_memory(&content), NULL);
	i++;
	j = 0;
	while (content[i])
	{
		new_content[j++] = content[i++];
	}
	release_memory(&content);
	return (new_content);
}

char	*extract_line(char *content)
{
	char	*line;
	int		i;

	if (!content || !*content)
		return (NULL);
	i = 0;
	while (content && content[i] != '\0')
	{
		if (content[i++] == '\n')
			break ;
	}
	line = safe_allocate(i + 1, 1);
	if (!line)
	{
		return (NULL);
	}
	while (--i >= 0)
	{
		line[i] = content[i];
	}
	return (line);
}

char	*fill_content(int fd, char *content)
{
	char	*chunk;
	size_t	bytes_read;

	while (!find_char(content, '\n'))
	{
		chunk = safe_allocate(BUFFER_SIZE + 1, 1);
		if (!chunk)
		{
			return (release_memory(&content), NULL);
		}
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read == 0)
		{
			release_memory(&chunk);
			break ;
		}
		content = merge_and_free(content, chunk, bytes_read);
		if (!content)
		{
			return (NULL);
		}
	}
	return (content);
}

char	*get_next_line(int fd)
{
	static char	*content;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	content = fill_content(fd, content);
	if (!content)
	{
		return (NULL);
	}
	line = extract_line(content);
	if (line)
	{
		content = truncate_content(content);
	}
	else
	{
		release_memory(&content);
	}
	return (line);
}
