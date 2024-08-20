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

    step.first.y = (floor(data->player.y / data->map->tile_size) * data->map->tile_size); // -1 to make first point 1 pixel before the line
    step.check_pt.y = step.first.y;                                                       // 1 pixel closer, if we hit the wall at chack pt we must stop and take the first's coordinates
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
    step.check_pt.x = data->player.x + (step.first.y - data->player.y) / tan(angle);

    step.distance = get_distance(data, step.first.x, step.first.y);
    step.d_x = data->map->tile_size / tan(angle);
    if (!is_right(angle) && step.d_x > 0) // tan(left angle) = - tan(right angle)
        step.d_x *= -1;
    if (is_right(angle) && step.d_x < 0)
        step.d_x *= -1;
    while (1)
    {
        step.distance = get_distance(data, step.first.x, step.first.y);
        if (is_wall(data, step.check_pt.x, step.check_pt.y))
            break;
        step.first.x += step.d_x;
        step.first.y += step.d_y;
        step.check_pt.x += step.d_x;
        step.check_pt.y += step.d_y;
    }
    // protected_ppx(data->img, (int)step.check_pt.x, (int)step.check_pt.y, get_rgba(255, 0, 0, 255));
    // protected_ppx(data->img, (int)step.first.x, (int)step.first.y, get_rgba(0, 255, 0, 255));
    return step;
}

// NOTE  wokring here =============================

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
    step.check_pt.y = data->player.y + (step.first.x - data->player.x) * tan(angle);
    step.distance = get_distance(data, step.first.x, step.first.y);
    step.d_y = data->map->tile_size * tan(angle);
    if (is_up(angle) && step.d_y > 0)
        step.d_y *= -1;
    if (!is_up(angle) && step.d_y < 0)
        step.d_y *= -1;
    // protected_ppx(data->img, (int)step.first.x, (int)step.first.y, get_rgba(255, 0, 0, 255));
    while (1)
    {
        step.distance = get_distance(data, step.first.x, step.first.y);
        if (is_wall(data, step.check_pt.x, step.check_pt.y))
            break;
        step.first.x += step.d_x;
        step.first.y += step.d_y;
        step.check_pt.x += step.d_x;
        step.check_pt.y += step.d_y;
        step.distance = get_distance(data, step.first.x, step.first.y);
        // protected_ppx(data->img, (int)step.first.x, (int)step.first.y, get_rgba(255, 0, 0, 255));
    }

    return step;
}
// ==========================================================

double ft_dda(t_data *data, double ray_angle, int *direction)
{
    t_dda step_x;
    t_dda step_y;

    double distortion_factor;
    double x;
    double y;

    int i;

    i = 0;

    step_x = get_hor_inters(data, ray_angle);
    step_y = get_vert_inters(data, ray_angle);
    distortion_factor = cos(data->player.rotation_angle - ray_angle);
    if (step_x.distance > step_y.distance) // know when to take or equal
    {
        *direction = VERTI;
        draw_line(data, data->player.x, data->player.y, data->player.x + (cos(ray_angle) * step_y.distance), data->player.y + (sin(ray_angle) * step_y.distance), 1);
        // printf("distance : %.4f\n", step_y.distance);
        // return step_y.distance;
        return distortion_factor * step_y.distance;
    }
    *direction = HORI;
    draw_line(data, data->player.x, data->player.y, data->player.x + (cos(ray_angle) * step_x.distance), data->player.y + (sin(ray_angle) * step_x.distance), 2);
    // printf("distance : %.4f\n", step_x.distance);
    // return step_x.distance;
    return distortion_factor * step_x.distance;
}

void cast_rays(t_data *data)
{
    double ray_angle;
    double angle_incr;
    double distance;
    int direction;
    int i;

    i = 0;
    direction = 0;
    angle_incr = FOV_ANGL / WIDTH;
    ray_angle = normalize_angle(data->player.rotation_angle - (FOV_ANGL / 2)); // orig
    // ray_angle = normalize_angle(data->player.rotation_angle);
    while (i < WIDTH)
    {
        distance = ft_dda(data, ray_angle, &direction);
        render_wall(data, distance, i, direction);
        ray_angle = normalize_angle(ray_angle + angle_incr);
        i++;
    }
}
