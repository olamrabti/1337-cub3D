#include "../cub3d.h"

void get_map_lines(t_data *data, char *filename)
{
    int fd;
    char *line;

    fd = open(filename, O_RDONLY);
    while(1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        add_addr(&data->addr, new_addr(line));
        line = ft_strtrim(line, "\n");
        if (ft_strlen(line))
            data->lines++;
        free(line);
    }
    close(fd);
}

int fill_map(t_data *data, char *filename)
{ 
    int fd;
    int i;
    char *line;

    fd = open(filename, O_RDONLY);
    i = 0;
    while(i < data->lines)
    {
        line = get_next_line(fd);
        if (!line)
            return 1;
        add_addr(&data->addr, new_addr(line));
        line = ft_strtrim(line, "\n");
        if (ft_strlen(line))
        {
        	add_addr(&data->addr, new_addr(line));
            data->map[i] = line;
            i++;
        }
    }
    close(fd);
    return 0;
}

void parse_map(t_data *data, char *filename)
{   
    data->lines = 0;
    get_map_lines(data, filename);
    if (data->lines)
        data->map = ft_calloc_ac(&data->addr, data->lines + 1, sizeof(char *));
    // printf("rows : %d, lines : %d\n", data->rows, data->lines);
    if (!data->map)
        return ;
    data->map[data->lines] = NULL;
    fill_map(data, filename);
}