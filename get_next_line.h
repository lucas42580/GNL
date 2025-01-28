/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:24:32 by lpaysant          #+#    #+#             */
/*   Updated: 2025/01/07 15:24:20 by lpaysant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
char	*create_line(char *buffer, char *line);
char	*get_buffrest(char *buffer, char **buffrest, int *i);
char	*read_buffer(int fd, char **buffrest);
char	*linecheck(char *buffer, char **buffrest, int fd, int i);
char	*new_line(char **buffrest, char *buffer, int i, char *line);

#endif
