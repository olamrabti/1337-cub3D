#include "../cub3d.h"

double get_distance(t_data *data, double x, double y)
{
    double delta_x;
    double delta_y;

    delta_x = x - data->player.x;
    delta_y = y - data->player.y;
    // printf("%.2f \n", sqrt((delta_x * delta_x) + (delta_y * delta_y)));
    return sqrt((delta_x * delta_x) + (delta_y * delta_y));
}

int is_wall(t_data *data, double x, double y)
{
    double map_x;
    double map_y;

    map_x = x / data->map->tile_size;
    map_y = y / data->map->tile_size;
    // SIZE will be changed to be flexible with all maps // TODO

    // printf("map_x : %d, map_y : %d, map_w : %d, map_h: %d\n", (int)map_x, (int)map_y, data->map->map_width, data->map->map_height);
    if (map_x > 0 && map_x <= data->map->map_width && map_y > 0 && map_y <= (data->map->map_height))
    {
        // printf("map[map_y][map_x] : '%c'\n", data->map->map_tiles[(int)map_y][(int)map_x]);
        if (data->map->map_tiles[(int)map_y][(int)map_x] != '0')
            return 1;
        return 0;
    }
    return 1;
}

void clear_screen(mlx_image_t *img, int color)
{
    int x, y;
    for (y = 0; y < HEIGHT; ++y)
    {
        for (x = 0; x < WIDTH; ++x)
            protected_ppx(img, x, y, color);
    }
}

void render_wall(t_data *data, double distance, double x)
{
    int wall_height;
    int wall_top;
    int wall_bottom;
    double scale;

    scale = 8;
    if (!distance)
        distance = 1;
    // if (!distance)
    //     return;
    wall_height = ((int)(HEIGHT / distance) * scale);
    wall_top = (HEIGHT - wall_height) / 2;
    wall_bottom = (HEIGHT + wall_height) / 2;

    // printf("wall_top : %d\n", wall_top);
    while (wall_top < wall_bottom)
    {
        wall_top++;
        protected_ppx(data->img, x, wall_top, get_rgba(255, 200, 0, 255));
    }
}
int is_up(double angle)
{
    return (angle >= M_PI && angle <= 2 * M_PI);
}

int is_right(double angle)
{

    return (angle >= (3 * M_PI / 2) || angle < M_PI / 2);
}

t_dda get_hor_inters(t_data *data, double angle)
{

    t_dda step;

    step.first.y = floor(data->player.y / data->map->tile_size) * data->map->tile_size - 1; // -1 to make first point 1 pixel before the line
    step.d_y = data->map->tile_size;

    if (!is_up(angle))
        step.first.y += data->map->tile_size + 1;
    else
        step.d_y *= -1;
    step.first.x = data->player.x + (step.first.y - data->player.y) / tan(angle);

    step.distance = get_distance(data, step.first.x, step.first.y);
    step.d_x = data->map->tile_size / tan(angle);
    if (!is_right(angle) && step.d_x > 0) // tan(left angle) = - tan(right angle)
        step.d_x *= -1;
    if (is_right(angle) && step.d_x < 0)
        step.d_x *= -1;
    // protected_ppx(data->img, (int)step.first.x, (int)step.first.y, get_rgba(0, 255, 0, 255));
    while (!is_wall(data, step.first.x, step.first.y))
    {
        step.first.x += step.d_x;
        step.first.y += step.d_y;
        // protected_ppx(data->img, (int)step.first.x, (int)step.first.y, get_rgba(0, 255, 0, 255));
        step.distance = get_distance(data, step.first.x, step.first.y);
    }
    return step;
}

// NOTE  wokring here =============================

t_dda get_vert_inters(t_data *data, double angle)
{
    t_dda step;

    step.first.x = (floor(data->player.x / data->map->tile_size) * data->map->tile_size) + data->map->tile_size; //
    step.d_x = data->map->tile_size;
    if (!is_right(angle))
    {
        step.first.x -= data->map->tile_size + 1;
        step.d_x *= -1;
    }
    step.first.y = data->player.y + (step.first.x - data->player.x) * tan(angle);
    step.distance = get_distance(data, step.first.x, step.first.y);
    step.d_y = data->map->tile_size * tan(angle);
    if (is_up(angle) && step.d_y > 0)
        step.d_y *= -1;
    if (!is_up(angle) && step.d_y < 0)
        step.d_y *= -1;
    // protected_ppx(data->img, (int)step.first.x, (int)step.first.y, get_rgba(255, 0, 0, 255));
    while (!is_wall(data, step.first.x, step.first.y))
    {
        step.first.x += step.d_x;
        step.first.y += step.d_y;
        // protected_ppx(data->img, (int)step.first.x, (int)step.first.y, get_rgba(255, 0, 0, 255));
        step.distance = get_distance(data, step.first.x, step.first.y);
    }
    return step;
}
// ==========================================================

double ft_dda(t_data *data, double ray_angle)
{
    t_dda step_x;
    t_dda step_y;
    int i;

    i = 0;

    step_x = get_hor_inters(data, ray_angle);
    step_y = get_vert_inters(data, ray_angle); // NOTE Correct

    // printf(" h_i [ %d, %d], player [ %d, %d]\n", (int)step_x.first.x, (int)step_x.first.y, (int)data->player.x, (int)data->player.y);
    // printf(" v_i [ %d, %d], player [ %d, %d]\n", (int)step_y.start.x, (int)step_y.start.y, (int)data->player.x, (int)data->player.y);

    // protected_ppx(data->img, step_x.first.x, step_x.first.y, get_rgba(255, 0, 0, 255));
    // protected_ppx(data->img, step_y.first.x, step_y.first.y, get_rgba(0, 255, 0, 255));
    // while (i < WIDTH / data->map->tile_size)
    // {
    //     if (is_wall(data, step_x.first.x, step_x.first.y) || is_wall(data, step_y.first.x, step_y.first.y))
    //     {
    //         step_x.distance = get_distance(data, step_x.first.x, step_x.first.y);
    //         step_y.distance = get_distance(data, step_y.first.x, step_y.first.y);
    //         protected_ppx(data->img, step_x.first.x, step_x.first.y, get_rgba(255, 0, 0, 255));
    //         protected_ppx(data->img, step_y.first.x, step_y.first.y, get_rgba(0, 255, 0, 255));
    //         break ;
    //     }
    //     step_x.first.x += step_x.d_x;
    //     step_x.first.y += step_x.d_y;
    //     step_y.first.x += step_y.d_x;
    //     step_y.first.y += step_y.d_y;
    //     i++;
    // }

    // draw_line(data, data->player.x, data->player.y, (int)data->player.x + (cos(ray_angle) * step_y.distance), (int)data->player.y + (sin(ray_angle) * step_y.distance));
    // // exit(0);
    // printf("distance H : %d, distance V : %d \n", step_x.distance, step_y.distance);
    if (step_x.distance > step_y.distance)
        protected_ppx(data->img, (int)step_y.first.x, (int)step_y.first.y, get_rgba(0, 255, 0, 255));
    else
        protected_ppx(data->img, (int)step_x.first.x, (int)step_x.first.y, get_rgba(255, 0, 0, 255));

    // printf("angle : %.2f, step1_dx: %.2f ,step1_dy: %.2f\n", ray_angle, step_x.d_x, step_x.d_y);
    // printf(" step2_dx: %.2f ,step2_dy: %.2f\n", step_y.d_x, step_y.d_y);
    return 0;

    // if (step_x.distance <= step_y.distance)
    //     return draw_line(data, data->player.x, data->player.y, (int)step_x.end.x, (int)step_x.end.y);
    // return draw_line(data, data->player.x, data->player.y, (int)step_y.end.x, (int)step_y.end.y);
}

void draw_rays(t_data *data)
{
    double ray_angle;
    double angle_incr;
    int i;

    i = 0;
    angle_incr = FOV_ANGL / (WIDTH / 2);
    ray_angle = normalize_angle(data->player.rotation_angle - (FOV_ANGL / 2)); // orig
    // ray_angle = normalize_angle(data->player.rotation_angle);
    while (i < WIDTH)
    {
        // draw_line( data, data->player.x, data->player.y, (int)data->player.x + (cos(ray_angle) * 20), (int)data->player.y + (sin(ray_angle) * 20));
        ft_dda(data, ray_angle);
        ray_angle = normalize_angle(ray_angle + angle_incr);
        i++;
    }
}
