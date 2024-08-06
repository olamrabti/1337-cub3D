#include "get_next_line.h"

int flag(char *str)
{
	int i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char *ft_read_buffer(int fd, char *buff, char *temp)
{
	char *del;
	int i;

	i = 1;
	while (flag(temp) == 0 && i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0)
			return (free(buff), buff = NULL, free(temp), temp = NULL, NULL);
		if (i == 0)
			break;
		buff[i] = '\0';
		if (!temp)
			temp = ft_strdup("");
		del = temp;
		temp = ft_strjoin(del, buff);
		free(del);
		del = NULL;
	}
	free(buff);
	buff = NULL;
	if (temp && temp[0] == '\0')
		return (free(temp), temp = NULL, NULL);
	return (temp);
}

char *ft_new_line(char *temp)
{
	char *result;
	int i;

	if (!temp)
		return (NULL);
	i = 0;
	while (temp[i] != '\n' && temp[i])
		i++;
	if (temp[i] == '\n')
		i++;
	result = ft_substr(temp, 0, i);
	if (!result)
		return (free(temp), temp = NULL, NULL);
	return (result);
}

char *ft_the_next_line(char *temp)
{
	char *new_buff;
	int i;

	i = 0;
	while (temp[i] != '\n' && temp[i])
		i++;
	if (temp[i] == '\n')
		i++;
	new_buff = ft_strdup(temp + i);
	if (!new_buff)
		return (free(temp), temp = NULL, NULL);
	free(temp);
	temp = NULL;
	return (new_buff);
}

char *get_next_line(int fd)
{
	static char *temp;
	char *buff;
	char *line;

	if (BUFFER_SIZE > INT_MAX || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (free(temp), temp = NULL, NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free(temp), temp = NULL, NULL);
	temp = ft_read_buffer(fd, buff, temp);
	line = ft_new_line(temp);
	if (!line)
		return (temp = NULL, NULL);
	temp = ft_the_next_line(temp);
	return (line);
}