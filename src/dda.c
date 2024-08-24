#include "../cub3d.h"

double get_distance(t_data *data, double x, double y)
{
    double delta_x;
    double delta_y;

    delta_x = x - data->player.x;
    delta_y = y - data->player.y;
    return sqrt((delta_x * delta_x) + (delta_y * delta_y));
}

int is_wall(t_data *data, double x, double y)
{
    double map_x;
    double map_y;

    map_x = x / data->map->tile_size;
    map_y = y / data->map->tile_size;

    if (map_x > 0 && map_x < data->map->map_width && map_y > 0 && map_y < (data->map->map_height))
    {
        if (data->map->map_tiles[(int)map_y][(int)map_x] != '0')
            return 1;
        return 0;
    }
    return 1;
}

void clear_screen(mlx_image_t *img, int color)
{
    int x;
    int y;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            protected_ppx(img, x, y, color);
            x++;
        }
        y++;
    }
}

int is_up(double angle)
{
    return (angle > M_PI);
}

int is_right(double angle)
{
    return (angle >= (3 * M_PI / 2) || angle < M_PI / 2);
}

t_dda get_hor_inters(t_data *data, double angle)
{

    t_dda step;

    step.first.y = (floor(data->player.y / data->map->tile_size) * data->map->tile_size);
    step.check_pt.y = step.first.y;
    step.d_y = data->map->tile_size;

    if (!is_up(angle))
    {
        step.first.y += (data->map->tile_size);
        step.check_pt.y += (data->map->tile_size + 1);
    }
    else
    {
        step.d_y *= -1;
        step.check_pt.y -= 1;
    }
    step.first.x = data->player.x + (step.first.y - data->player.y) / tan(angle);
    step.check_pt.x = step.first.x;

    step.d_x = data->map->tile_size / tan(angle);
    if (!is_right(angle) && step.d_x > 0)
        step.d_x *= -1;
    if (is_right(angle) && step.d_x < 0)
        step.d_x *= -1;
    while (1)
    {
        if (is_wall(data, step.check_pt.x, step.check_pt.y))
            break;
        step.first.x += step.d_x;
        step.first.y += step.d_y;
        step.check_pt.x += step.d_x;
        step.check_pt.y += step.d_y;
    }
    step.distance = get_distance(data, step.first.x, step.first.y);
    return step;
}


t_dda get_vert_inters(t_data *data, double angle)
{
    t_dda step;

    step.first.x = (floor(data->player.x / data->map->tile_size) * data->map->tile_size) + data->map->tile_size; //
    step.check_pt.x = step.first.x;
    step.d_x = data->map->tile_size;
    if (!is_right(angle))
    {
        step.first.x -= data->map->tile_size;
        step.check_pt.x -= (data->map->tile_size + 1);
        step.d_x *= -1;
    }
    else
        step.check_pt.x += 1;
    step.first.y = data->player.y + (step.first.x - data->player.x) * tan(angle);
    step.check_pt.y = step.first.y;
    step.d_y = data->map->tile_size * tan(angle);
    if (is_up(angle) && step.d_y > 0)
        step.d_y *= -1;
    if (!is_up(angle) && step.d_y < 0)
        step.d_y *= -1;
    while (1)
    {
        
        if (is_wall(data, step.check_pt.x, step.check_pt.y))
            break;
        step.first.x += step.d_x;
        step.first.y += step.d_y;
        step.check_pt.x += step.d_x;
        step.check_pt.y += step.d_y;
    }
    step.distance = get_distance(data, step.first.x, step.first.y);
    return step;
}

void ft_dda(t_data *data, t_ray *ray)
{
    t_dda step_x;
    t_dda step_y;

    double distortion_factor;
    double x;
    double y;

    step_x = get_hor_inters(data, ray->angle);
    step_y = get_vert_inters(data, ray->angle);
    distortion_factor = cos(data->player.rotation_angle - ray->angle);
    if (step_x.distance > step_y.distance)
    {
        ray->direction = EAST;
        if (is_right(ray->angle))
            ray->direction = WEST;
        ray->distance = distortion_factor * step_y.distance;
        ray->end_x = step_y.first.x;
        ray->end_y = step_y.first.y;
        // draw_line(data, data->player.x, data->player.y, ray->end_x, ray->end_y, get_rgba(255, 0, 0, 255));
        return;
    }
    ray->direction = NORTH;
    if (is_up(ray->angle))
        ray->direction = SOUTH;
    ray->end_x = step_x.first.x;
    ray->end_y = step_x.first.y;
    ray->distance = distortion_factor * step_x.distance;
    // draw_line(data, data->player.x, data->player.y, ray->end_x, ray->end_y, get_rgba(255, 0, 0, 255));
}

void cast_rays(t_data *data)
{
    t_ray ray;
    double angle_incr;
    int i;

    i = 0;
    ray.direction = 0;
    angle_incr = FOV_ANGL / WIDTH;
    ray.angle = normalize_angle(data->player.rotation_angle - (FOV_ANGL / 2));
    while (i < WIDTH)
    {
        ft_dda(data, &ray);
        render_tex_col(data, &ray, i);
        ray.angle = normalize_angle(ray.angle + angle_incr);
        i++;
    }
}
