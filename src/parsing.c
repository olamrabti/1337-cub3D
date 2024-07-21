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
        if (ft_strlen(line) >= infos[1])
        {
            if (ft_strchr(line, '\n'))
                infos[1] = ft_strlen(line) - 1;
            else
                infos[1] = ft_strlen(line);
        }
        // printf("len : %d\n", infos[1]);
        // printf("line : %s\n", line);
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
    char *line;

    fd = open(filename, O_RDONLY);
    i = 0;
    while(i < infos[0])
    {
        tmp[i] = ft_calloc_ac(&addr, infos[1], sizeof(char));
        line = get_next_line(fd);
        if (!line)
            return 1;
        tmp[i] = ft_strtrim(line, "\n");
	    printf("tmp [%d] : %s\n",i, tmp[i]);
        free(line);
        if (tmp[i][0])
            i++;
    }
    close(fd);
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
    fill_map(addr, tmp, infos, filename);
    return tmp;
}