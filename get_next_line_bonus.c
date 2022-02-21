/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherkao <zcherkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:50:44 by zcherkao          #+#    #+#             */
/*   Updated: 2021/12/07 11:54:32 by zcherkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *buffers)
{
	int		i;
	char	buff[BUFFER_SIZE + 1];

	i = 1;
	while (!ft_strchr (buffers, '\n') && i)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
			return (0);
		buff[i] = '\0';
		buffers = ft_strjoin(buffers, buff);
	}
	return (buffers);
}

char	*ft_firstline(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc (sizeof(char) * (i + 1));
	if (!line)
		return (0);
	i = -1;
	while (str[++i] && str[i] != '\n')
		line[i] = str[i];
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_secondline(char *buffers)
{
	int		i;
	char	*line;
	int		j;
	int		len;

	i = 0;
	while (buffers[i] && buffers[i] != '\n')
		i++;
	if (buffers[i] == '\0')
	{
		free (buffers);
		return (0);
	}
	len = (ft_strlen(buffers) - i);
	line = malloc (sizeof(char) * (len + 1));
	if (!line)
		return (0);
	i++;
	j = 0;
	while (buffers[i])
		line[j++] = buffers[i++];
	line[j] = '\0';
	free (buffers);
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*str[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = ft_read (fd, str[fd]);
	if (!str[fd])
		return (0);
	line = ft_firstline (str[fd]);
	str[fd] = ft_secondline (str[fd]);
	return (line);
}

/*int main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	char *line;

		int fd = open(argv[1],O_CREAT|O_RDONLY);
		line  = get_next_line(fd);
		
	while(line)
	{
		printf("%s", line);
		free(line);
		line  = get_next_line(fd);
	}
	
	fd = open(argv[2],O_CREAT|O_RDONLY);
		line  = get_next_line(fd);
		
	while(line)
	{
		printf("%s", line);
		free(line);
		line  = get_next_line(fd);
		
}*/