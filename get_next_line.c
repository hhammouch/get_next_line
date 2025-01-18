/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhammouc <hhammouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:45:27 by hhammouc          #+#    #+#             */
/*   Updated: 2025/01/18 19:21:13 by hhammouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*line_set(char *line)
{
	// line = "hello world\n133\0"
	char    *left_c;
	ssize_t    i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0') // hello world\n -> i = 11
        i++;
	if (line[i] == 0 || line[1] == 0)
		return (NULL);
	left_c = ft_substr(line, i + 1, ft_strlen(line) - i); // ("hello world\n133\0", 12, (15 - 11) = 4)
	if (!left_c || left_c[0] == '\0')
	{
		free(left_c);
		left_c = NULL;
	}
	line[i + 1] = 0;
	return (left_c);
}

static char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}

static char	*fill_line_buffer(int fd, char *stash, char *buffer) 
{
    // fd, stash -> (1) = null, buffer malloc 6
	ssize_t	toread;
	char	*tmp;

	toread = 1;
	while (toread > 0)
	{
		toread = read(fd, buffer, BUFFER_SIZE); // fd, hello, 6 || toread = 5
		if (toread == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (toread == 0)
			break ;
		buffer[toread] = 0; // set last character to \0
		if (!stash)
			stash = ft_strdup(""); // first time its null so we use strdup
		tmp = stash;
		stash = ft_strjoin(tmp, buffer); // "", "hello" -> stash = "hello\0"  || next read -> tmp = "hello", buffer = " worl\0"
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))  // if \n found break
			break ;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
    char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char)); // if buffer_size is 5 + 1 -> malloc 6 
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, stash, buffer); // fd, stash -> (1) = null, buffer malloc 6
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	stash = line_set(line); // first read line = "hello world\n133\0"
	return (line);
}
// int main(void)
// {
//     int fd = open("file.txt", O_RDONLY);
//     char *line;
//     int i = 1;

//     if (fd < 0)
//     {
//         printf("error");
//         return (1);
//     }
//     while((line = get_next_line(fd)) != NULL)
//     {
//         printf("%d) %s", i, line);
//         i++;
//     }
//     return (0);
// }
