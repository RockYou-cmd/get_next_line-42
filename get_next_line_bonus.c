/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:58:41 by ael-korc          #+#    #+#             */
/*   Updated: 2021/12/14 11:58:44 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_line(char	*tab)
{
	size_t	i;

	i = 0;
	if (!tab)
	{
		return (-1);
	}
	while (tab[i])
	{
		if (tab[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*readthis(int fd, char *str, char *buff)
{
	int		r;
	char	*tmp;

	if (buff == NULL)
		return (NULL);
	if (str == NULL)
		str = ft_strdup("");
	r = 1;
	while (ft_line(str) == -1)
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r > 0)
		{
			buff[r] = '\0';
			tmp = ft_strjoin(str, buff);
			if (str)
				free(str);
			str = NULL;
			str = tmp;
		}
		else
			break ;
	}
	free(buff);
	return (str);
}

char	*ft_place(char	*test)
{
	char	*line;
	int		index;
	size_t	i;

	if (ft_strlen(test) == 0)
		return (NULL);
	index = ft_line(test);
	if (index == -1)
	{
		line = ft_strdup(test);
		return (line);
	}
	line = (char *)malloc((index + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (test[i] != '\n')
	{
		line[i] = test[i];
		i++;
	}
	line[i] = '\n';
	line [i + 1] = '\0';
	return (line);
}

char	*ft_remain(char	*remain)
{
	int		len;
	int		index;
	char	*tmp;

	if (!remain)
		return (NULL);
	len = ft_strlen(remain);
	index = ft_line(remain);
	if (index != -1)
	{
		tmp = ft_substr(remain, (index + 1), (len - index - 1));
		free (remain);
		remain = tmp;
		return (remain);
	}
	free (remain);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*test[1024];
	char		*place;
	char		*buff;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	test[fd] = readthis(fd, test[fd], buff);
	place = ft_place(test[fd]);
	test[fd] = ft_remain(test[fd]);
	return (place);
}
