/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhammouc <hhammouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:45:27 by hhammouc          #+#    #+#             */
/*   Updated: 2025/01/21 17:02:34 by hhammouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*line_set(char *line)
{
	char	*left_c;
	ssize_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0 || line[1] == 0)
		return (NULL);
	left_c = ft_substr(line, i + 1, ft_strlen(line) - i);
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
	ssize_t	toread;
	char	*tmp;

	toread = 1;
	while (toread > 0)
	{
		toread = read(fd, buffer, BUFFER_SIZE);
		if (toread == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (toread == 0)
			break ;
		buffer[toread] = 0;
		if (!stash)
			stash = ft_strdup("");
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;
	size_t		size_buf;

	size_buf = BUFFER_SIZE;
	buffer = (char *)malloc((size_buf + 1) * sizeof(char));
	if (fd < 0 || size_buf <= 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, stash, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	stash = line_set(line);
	return (line);
}

#include <stdio.h>

int main ()
{
	int fd1 = open("file1.txt", O_RDONLY);
	char *line1;
	int i = 1;

	while((line1 = get_next_line(fd1)) != NULL)
	{
		printf("%d) -> %s",i,line1);
		free(line1);
		i++;
	}
}

