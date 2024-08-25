#include "../cub3d.h"

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

char *ft_read_buffer(int fd, char *buff, char *temp, t_data *data)
{
	char *del;
	int i;

	i = 1;
	while (flag(temp) == 0 && i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0)
			return ( NULL);
		if (i == 0)
			break;
		buff[i] = '\0';
		if (!temp)
			temp = gc_strdup("", &data->addr);
		del = temp;
		temp = gc_strjoin(del, buff, &data->addr);
	}

	if (temp && temp[0] == '\0')
		return ( NULL);
	return (temp);
}

char *ft_new_line(char *temp, t_data *data)
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
	result = gc_substr(temp, 0, i, &data->addr);
	if (!result)
		return (NULL);
	return (result);
}

char *ft_the_next_line(char *temp, t_data *data)
{
	char *new_buff;
	int i;

	i = 0;
	while (temp[i] != '\n' && temp[i])
		i++;
	if (temp[i] == '\n')
		i++;
	new_buff = gc_strdup(temp + i, &data->addr);
	if (!new_buff)
		return (NULL);
	return (new_buff);
}

char *get_next_line(int fd, t_data *data)
{
	static char *temp;
	char *buff;
	char *line;

	if (BUFFER_SIZE > INT_MAX || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_calloc_ac(&data->addr ,BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return ( NULL);
	temp = ft_read_buffer(fd, buff, temp, data);
	line = ft_new_line(temp, data);
	if (!line)
		return (temp = NULL, NULL);
	temp = ft_the_next_line(temp, data);
	return (line);
}
