/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:31:37 by lpaysant          #+#    #+#             */
/*   Updated: 2024/12/20 14:43:07 by lpaysant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	freetabs(char *line, char *buffer, char *buffrest)
{
	free(line);
	free(buffer);
	free(buffrest);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	int			nbread;
	int			i;
	static char	*buffrest;
	char		*temp;

	line = NULL;
	nbread = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (buffrest == NULL)
	{
		nbread = read(fd, buffer, BUFFER_SIZE);
		if (nbread <= 0)
		{
			free(buffer);
			return (NULL);
		}
	}
	else
	{
		temp = ft_strcpy(buffer, buffrest);
		if (!temp)
		{
			free(buffer);
			return (NULL);
		}
		buffer = temp;
	}
	free(buffrest);
	buffrest = NULL;
	i = 0;
	while (1)
	{
		if (buffer[i] == '\0')
		{
			if (line != NULL)
			{
				temp = ft_strjoin(line, buffer);
				if (!temp)
				{
					free(line);
					free(buffer);
					return (NULL);
				}
				free(line);
				line = temp;
			}
			else
			{
				line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
				if (!line)
				{
					free(buffer);
					return (NULL);
				}
				temp = ft_strcpy(line, buffer);
				if (!temp)
				{
					free(line);
					free(buffer);
					return (NULL);
				}
				line = temp;
			}
			nbread = read(fd, buffer, BUFFER_SIZE);
			if (nbread < 0)
			{
				freetabs(line, buffer, buffrest);
				return (NULL);
			}
			if (nbread == 0)
			{
				free(buffer);
				free(buffrest);
				return (line);
			}
			buffer[nbread] = '\0';
			i = 0;
		}
		if (buffer[i] == '\n')
		{
			if (buffer[i + 1] != '\0')
			{
				buffrest = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
				if (!buffrest)
				{
					freetabs(line, buffer, buffrest);
					return (NULL);
				}
				temp = ft_strcpy(buffrest, buffer + i + 1);
				if (!temp)
				{
					freetabs(line, buffer, buffrest);
					return (NULL);
				}
				buffrest = temp;
				i++;
				while (buffer[i])
					buffer[i++] = '\0';
			}
			if (!line)
			{
				line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
				if (!line)
				{
					freetabs(line, buffer, buffrest);
					return (NULL);
				}
				temp = ft_strcpy(line, buffer);
				if (!temp)
				{
					freetabs(line, buffer, buffrest);
					return (NULL);
				}
				line = temp;
			}
			else
			{
				temp = ft_strjoin(line, buffer);
				if (!temp)
				{
					freetabs(line, buffer, buffrest);
					return (NULL);
				}
				free(line);
				line = temp;
			}
			free(buffer);
			return (line);
		}
		i++;
	}
}

#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*next_line;

	fd = open("bigline.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while (1)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		printf("%s\n", next_line);
		free(next_line);
		next_line = NULL;
	}
	close(fd);
	return (0);
}
