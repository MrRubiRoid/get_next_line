#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
#endif

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"

static char    *find_new_line(int fd, char *storage)
{
    char    *read_part;
    int        bytes_read;

    bytes_read = 7;
    read_part = malloc(BUFFER_SIZE + 1);
    if (!read_part)
        return (0);
    while (ft_strchr_gnl(storage, '\n') == 0 && bytes_read > 0)
    {
        bytes_read = read(fd, read_part, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(read_part);
            if (storage)
                free(storage);
            return (NULL);
        }
        read_part[bytes_read] = '\0';
        storage = ft_strjoin_gnl(storage, read_part);
    }
    free(read_part);
    return (storage);
}

static char    *new_line(char *storage)
{
    char    *temp;
    int        pos;
    int        len;

    pos = 0;
    len = get_nl_pos(storage);
    if (storage[0] == '\0')
        return (NULL);
    if (storage[len] == '\n')
        len++;
    temp = malloc(len + 1);
    if (!temp)
        return (NULL);
    while (pos < len)
    {
        temp[pos] = storage[pos];
        pos++;
    }
    temp[pos] = '\0';
    return (temp);
}
static char    *storage_update(char *storage)
{
    char    *new_storage;
    int        start;
    int        pos;
    int        size;

    size = 0;
    if (storage[0] == '\0')
        return (free(storage), NULL);
    start = get_nl_pos(storage);
    if (storage[start] == '\n')
        start++;
    pos = start;
    while (storage[pos++] != '\0')
        size++;
    new_storage = malloc(size + 1);
    if (!new_storage)
        return (NULL);
    pos = 0;
    while (storage[start] != '\0')
        new_storage[pos++] = storage[start++];
    new_storage[pos] = '\0';
    free(storage);
    return (new_storage);
}

char    *get_next_line(int fd)
{
    static char    *storage;
    char        *ret_line;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return ("Error");
    storage = find_new_line(fd, storage);
    if (storage == NULL)
        return ("Error");
    ret_line = new_line(storage);
    storage = storage_update(storage);
    return (ret_line);
}
