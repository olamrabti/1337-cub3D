#include "../cub3d.h"

void get_lines_infos(int *infos, char *filename)
{
    int fd;
    int n;
    char *line;

    fd = open(filename, O_RDONLY);
    while(1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        printf("len : %ld\n", ft_strlen(line));
        printf("line : %s\n", line);
        if (ft_strlen(line) > infos[1])
            infos[1] = ft_strlen(line);
        n++;
        free(line);
    }
    close(fd);
    infos[0] = n;
}

int fill_map(t_addr *addr, char **tmp, int *infos, char *filename)
{ 
    int fd;
    int i;
    int j;
    char *line;

    fd = open(filename, O_RDONLY);
    i = 0;
    j = 0;
    while(i < infos[0])
    {
        tmp[i] = ft_calloc_ac(&addr, infos[1], sizeof(char));
        if (!tmp[i])
            return 1;
        line = get_next_line(fd);
        if (!line)
            return 1;
        j = ft_strlen(line);
        // if (j == 1) // fiha nl skip it
        // you can neglect the rest of the len !!
        ft_strcpy(tmp[i], line);
        while (j < infos[1])
        {
            tmp[i][j] = '0';
            j++;
        }
        i++;
    }
    return 0;
}

char **parse_map(t_addr *addr, char *filename)
{   
    char **tmp;
    static int infos[2];

    get_lines_infos(infos, filename);
    if (infos[0])
        tmp = ft_calloc_ac(&addr, infos[0], sizeof(char *));
    if (!tmp)
        return NULL;
    // if (fill_map(addr, tmp, infos, filename))
    //     return NULL;
    return tmp;
}