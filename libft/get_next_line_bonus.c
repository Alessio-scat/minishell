/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:01:48 by ascatama          #+#    #+#             */
/*   Updated: 2023/02/09 14:18:46 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_clean_stash(char *stash)
{
	size_t	i;
	size_t	j;
	char	*str;
	int		len;

	i = 0;
	len = ft_strlen_gnl(stash);
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (len - i) + 1);
	if (!str)
		return (NULL);
	j = 0;
	while (stash[i++] != '\0')
	{
		str[j++] = stash[i];
	}
	str[j] = '\0';
	free(stash);
	return (str);
}

static char	*ft_extrac_line(char *stash)
{
	size_t	i;
	char	*str;

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash[i] != '\0')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		str[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		str[i] = stash[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_read_and_stash(int fd, char *stash)
{
	char	*buff;
	int		bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (ft_search(stash) == 0 && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			free(stash);
			return (NULL);
		}
		buff[bytes] = '\0';
		stash = ft_strjoin_gnl(stash, buff);
	}
	free(buff);
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash[fd] = ft_read_and_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_extrac_line(stash[fd]);
	stash[fd] = ft_clean_stash(stash[fd]);
	if (line[0] == '\0' || line[0] == '\n')
	{
		free(stash[fd]);
		stash[fd] = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
