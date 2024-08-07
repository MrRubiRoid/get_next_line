#include <stdlib.h>

char    *ft_strchr_gnl(const char *str, int c)
{
    if (!str)
        return (NULL);
    while (*str != '\0' && *str != (unsigned char)c)
        str++;
    if (*str == (unsigned char)c)
        return ((char *)str);
    return (0);
}

int    ft_strlen_gnl(const char *str)
{
    int    len;

    len = 0;
    while (*str != '\0')
    {
        len++;
        str++;
    }
    return (len);
}

int    get_nl_pos(char *s)
{
    int    pos;

    pos = 0;
    while (s[pos] != '\n' && s[pos] != '\0')
        pos++;
    return (pos);
}

char    *ft_strjoin_gnl(char *s1, char *s2)
{
    int        len;
    int        pos;
    int        pos2;
    char    *temp;

    pos = -1;
    pos2 = 0;
    if (!s1)
    {
        s1 = malloc(1);
        if (!s1)
            return (NULL);
        s1[0] = '\0';
    }
    len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
    temp = malloc(len + 1);
    if (!temp)
        return (NULL);
    while (s1[++pos])
        temp[pos] = s1[pos];
    while (s2[pos2])
        temp[pos++] = s2[pos2++];
    temp[pos] = '\0';
    free(s1);
    return (temp);
}
