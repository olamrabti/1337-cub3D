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

    map_x = x / TILE_SIZE;
    map_y = y / TILE_SIZE;

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

    step.next.y = (floor(data->player.y / TILE_SIZE) * TILE_SIZE);
    step.check_pt.y = step.next.y;
    step.d_y = TILE_SIZE;

    if (!is_up(angle))
    {
        step.next.y += (TILE_SIZE);
        step.check_pt.y += (TILE_SIZE + 1);
    }
    else
    {
        step.d_y *= -1;
        step.check_pt.y -= 1;
    }
    step.next.x = data->player.x + (step.next.y - data->player.y) / tan(angle);
    step.check_pt.x = step.next.x;

    step.d_x = TILE_SIZE / tan(angle);
    if (!is_right(angle) && step.d_x > 0)
        step.d_x *= -1;
    if (is_right(angle) && step.d_x < 0)
        step.d_x *= -1;
    while (1)
    {
        if (is_wall(data, step.check_pt.x, step.check_pt.y))
            break;
        step.next.x += step.d_x;
        step.next.y += step.d_y;
        step.check_pt.x += step.d_x;
        step.check_pt.y += step.d_y;
    }
    step.distance = get_distance(data, step.next.x, step.next.y);
    return step;
}


t_dda get_vert_inters(t_data *data, double angle)
{
    t_dda step;

    step.next.x = (floor(data->player.x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE; //
    step.check_pt.x = step.next.x;
    step.d_x = TILE_SIZE;
    if (!is_right(angle))
    {
        step.next.x -= TILE_SIZE;
        step.check_pt.x -= (TILE_SIZE + 1);
        step.d_x *= -1;
    }
    else
        step.check_pt.x += 1;
    step.next.y = data->player.y + (step.next.x - data->player.x) * tan(angle);
    step.check_pt.y = step.next.y;
    step.d_y = TILE_SIZE * tan(angle);
    if (is_up(angle) && step.d_y > 0)
        step.d_y *= -1;
    if (!is_up(angle) && step.d_y < 0)
        step.d_y *= -1;
    while (1)
    {
        
        if (is_wall(data, step.check_pt.x, step.check_pt.y))
            break;
        step.next.x += step.d_x;
        step.next.y += step.d_y;
        step.check_pt.x += step.d_x;
        step.check_pt.y += step.d_y;
    }
    step.distance = get_distance(data, step.next.x, step.next.y);
    return step;
}

void ft_dda(t_data *data, t_ray *ray)
{
    t_dda step_x;
    t_dda step_y;

    double distortion_factor;

    step_x = get_hor_inters(data, ray->angle);
    step_y = get_vert_inters(data, ray->angle);
    distortion_factor = cos(data->player.rotation_angle - ray->angle);
    if (step_x.distance > step_y.distance)
    {
        ray->direction = EAST;
        if (is_right(ray->angle))
            ray->direction = WEST;
        ray->distance = distortion_factor * step_y.distance;
        ray->end_x = step_y.next.x;
        ray->end_y = step_y.next.y;
        // draw_line(data, data->player.x, data->player.y, ray->end_x, ray->end_y, get_rgba(255, 0, 0, 255));
        return;
    }
    ray->direction = NORTH;
    if (is_up(ray->angle))
        ray->direction = SOUTH;
    ray->end_x = step_x.next.x;
    ray->end_y = step_x.next.y;
    ray->distance = distortion_factor * step_x.distance;
    // draw_line(data, data->player.x, data->player.y, ray->end_x, ray->end_y, get_rgba(255, 0, 0, 255));
}

void cast_rays(t_data *data)
{
    t_ray ray;
    double angle_incr;
    int i;
    int j;

    i = 0;
    j = 0;
    ray.direction = 0;
    angle_incr = FOV_ANGL / WIDTH;
    ray.angle = normalize_angle(data->player.rotation_angle - (FOV_ANGL / 2));
    data->player.close_to_wall = 0;
    data->player.animation_area = 0;
    while (i < WIDTH)
    {
        ft_dda(data, &ray);
        if (i == WIDTH / 2)
            data->player.animation_area += ray.distance;
        // if (i == 0 || i == WIDTH / 2 || i == WIDTH - 1)
        //     data->player.animation_area += ray.distance;
        if (ray.distance < 10)
        {
            data->player.close_to_wall += ray.distance;
            j++;
        }
        render_tex_col(data, &ray, i);
        ray.angle = normalize_angle(ray.angle + angle_incr);
        i++;
    }
    // data->player.animation_area /= 3;
    
}
