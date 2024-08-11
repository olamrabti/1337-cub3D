#include "../cub3d.h"

double get_distance(t_data *data, double x, double y)
{
    double delta_x;
    double delta_y;

    delta_x = x - data->player.x;
    delta_y = y - data->player.y;

    return sqrt(delta_x * delta_x + delta_y * delta_y);
}

int is_wall(t_data *data, int x, int y)
{
    int map_x;
    int map_y;

    map_y = y / (data->map->map_width);
    map_x = x / ft_strlen(data->map->map_tiles[map_y]); // FIXME

    printf("map_x : %d, map_y: %d\n", map_x, map_y);
    printf("x : %d, y: %d\n", x, y);

    if (map_x >= 0 && map_x < data->map->map_height && map_y >= 0 && map_y < ft_strlen(data->map->map_tiles[y / data->map->map_height]))
    {
        if (data->map->map_tiles[map_x][map_y] == 1) // FIXME
            return 1;
    }
    // printf("map addr : %p\n", data->map);
    return 0;
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

void render_wall(t_data *data, int distance, int x)
{
    int wall_height;
    int wall_top;
    int wall_bottom;
    double scale;

    scale = 2;
    // if (!distance)
    //     distance = 1;
    if (!distance)
        return;
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
    return (angle > M_PI);
}

int is_right(double angle)
{
    return (angle >= (3 * M_PI / 2) || angle <= M_PI / 2);
}

double get_alpha(double ray_angle)
{
    if (is_right(ray_angle) && is_up(ray_angle))
        return (2 * M_PI) - ray_angle;
    if (!is_right(ray_angle) && is_up(ray_angle))
        return ray_angle - M_PI;
    if (is_right(ray_angle) && !is_up(ray_angle))
        return ray_angle;
    if (!is_right(ray_angle) && !is_up(ray_angle))
        return M_PI - ray_angle;
    return 0;
}

t_dda get_hor_inters(t_data *data, double angle)
{
    t_dda step;

    step.start.y = floor(data->player.y / SIZE) * SIZE;
    if (!is_up(angle))
        step.start.y += SIZE;
    step.d_x = 0;
    if (tan(get_alpha(angle)) > 1e-6)
        step.d_x = fabs(step.start.y - data->player.y) / tan(get_alpha(angle));
    if (!is_right(angle))
        step.d_x *= -1;
    step.start.x = data->player.x + step.d_x;

    step.end.y = step.start.y - SIZE;
    if (!is_up(angle))
        step.end.y += 2 * SIZE;
    step.d_x = 0;
    if (tan(get_alpha(angle)) > 1e-6)
        step.d_x = SIZE / tan(get_alpha(angle));
    if (!is_right(angle))
        step.d_x *= -1;
    step.end.x = step.start.x + step.d_x;

    if (step.end.x < 0)
        step.end.x = 0;

    step.d_y = step.end.y - step.start.y;
    step.distance = sqrt(pow(step.end.x - step.start.x, 2) + pow(step.end.y - step.start.y, 2));
    return step;
}

t_dda get_vert_inters(t_data *data, double angle)
{
    t_dda step;

    step.start.x = (floor(data->player.x / SIZE) * SIZE) + SIZE; //
    if (!is_right(angle))
        step.start.x -= SIZE;
    step.start.y = data->player.y + (step.start.x - data->player.x) * tan(angle);

    step.d_x = SIZE;
    if (!is_right(angle))
        step.d_x *= -1;
    step.d_y = step.d_x * tan(angle);
    step.end.x = step.start.x + step.d_x;
    step.end.y = step.start.y + step.d_y;

    if (step.end.x < 0)
        step.end.x = 0;
    if (step.end.y < 0)
        step.end.y = 0;
    step.distance = sqrt(pow(step.end.x - step.start.x, 2) + pow(step.end.y - step.start.y, 2));

    return step;
}

double ft_dda(t_data *data, double tmp_angle)
{
    t_dda step_x;
    t_dda step_y;
    int i;

    i = 0;
    step_x = get_hor_inters(data, tmp_angle);
    step_y = get_vert_inters(data, tmp_angle);

    // printf(" h_i [ %d, %d], player [ %d, %d]\n", (int)step_x.start.x, (int)step_x.start.y, (int)data->player.x, (int)data->player.y);
    // printf(" v_i [ %d, %d], player [ %d, %d]\n", (int)step_y.start.x, (int)step_y.start.y, (int)data->player.x, (int)data->player.y);

    while (i < WIDTH / SIZE)
    {
        if (step_x.end.x < 0 || step_x.end.x >= WIDTH || step_x.end.y < 0 || step_x.end.y >= HEIGHT ||
            step_y.end.x < 0 || step_y.end.x >= WIDTH || step_y.end.y < 0 || step_y.end.y >= HEIGHT)
            break;
        step_x.distance = get_distance(data, step_x.end.x, step_x.end.y);
        step_y.distance = get_distance(data, step_y.end.x, step_y.end.y);

        step_x.end.x += step_x.d_x;
        step_x.end.y += step_x.d_y;

        step_y.end.x += step_y.d_x;
        step_y.end.y += step_y.d_y;
        i++;
    }
    // printf("distance 1 : %d, distance 2: %d \n", step_x.distance, step_y.distance);

    if (step_x.distance >= step_y.distance)
    {
        render_wall(data, step_y.distance, step_y.end.x);
        draw_line(data, data->player.x, data->player.y, step_y.end.x, step_y.end.y);
    }
    else
    {
        render_wall(data, step_x.distance, step_x.end.x);
        draw_line(data, data->player.x, data->player.y, step_x.end.x, step_x.end.y);
    }

    // printf("angle : %.2f, step1_dx: %.2f ,step1_dy: %.2f", tmp_angle, step_x.d_x, step_x.d_y);
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
    angle_incr = FOV_ANGL / WIDTH;
    ray_angle = normalize_angle(data->player.rotation_angle - (FOV_ANGL / 2)); // orig
    while (i < WIDTH)
    {
        ft_dda(data, ray_angle);
        ray_angle = normalize_angle(ray_angle + angle_incr);
        i++;
    }
}
