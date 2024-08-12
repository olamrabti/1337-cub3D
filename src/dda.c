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
    // SIZE will be changed to be flexible with all maps // TODO
    if (x >= 0 && x < data->map->map_width * SIZE && y >= 0 && y < SIZE * data->map->map_height)
    {
        if (data->map->map_tiles[y / SIZE][x / SIZE] == '1')
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
    step.first.y = floor(data->player.y / SIZE) * SIZE;
    step.d_y = SIZE;
    if (!is_up(angle))
        step.first.y += SIZE;
    else
        step.d_y *= -1;
    step.first.x = data->player.x + (step.first.y - data->player.y) / tan(angle); // removed get_alpha
    step.d_x = SIZE / tan(angle);
    if (!is_right(angle) && step.d_x > 0)
        step.d_x *= -1;
    if (is_right(angle) && step.d_x < 0)
        step.d_x *= -1;
    // while (step.first.x >= 0 && step.first.y >= 0 && !is_wall(data, step.first.x, step.first.y))
    // {
    //     step.distance = get_distance(data, step.first.x, step.first.y);
    //     step.first.x += step.d_x;
    //     step.first.y += step.d_y;
    //     protected_ppx(data->img, (int)step.first.x, (int)step.first.y, get_rgba(0, 255, 0, 255));
    // }
    return step;
}

t_dda get_vert_inters(t_data *data, double angle)
{
    t_dda step;

    step.first.x = (floor(data->player.x / SIZE) * SIZE) + SIZE; //
    step.d_x = SIZE;
    if (!is_right(angle))
        step.first.x -= SIZE;
    if (!is_right(angle))
        step.d_x *= -1;
    step.first.y = data->player.y + (step.first.x - data->player.x) * tan(angle);
    step.d_y = step.d_x * tan(angle);
    if (is_up(angle) && step.d_y > 0)
        step.d_y *= -1;
    if (!is_up(angle) && step.d_y < 0)
        step.d_y *= -1;
    // while (step.first.x >= 0 && step.first.y >= 0 && !is_wall(data, step.first.x, step.first.y))
    // {
    //     step.distance = get_distance(data, step.first.x, step.first.y);
    //     step.first.x += step.d_x;
    //     step.first.y += step.d_y;
    //     protected_ppx(data->img, (int)step.first.x, (int)step.first.y, get_rgba(255, 0, 0, 255));
    // }
    return step;
}


double ft_dda(t_data *data, double ray_angle)
{
    t_dda step_x;
    t_dda step_y;

    step_x = get_hor_inters(data, ray_angle);
    step_y = get_vert_inters(data, ray_angle); // NOTE Correct

    // printf(" h_i [ %d, %d], player [ %d, %d]\n", (int)step_x.first.x, (int)step_x.first.y, (int)data->player.x, (int)data->player.y);
    // printf(" v_i [ %d, %d], player [ %d, %d]\n", (int)step_y.start.x, (int)step_y.start.y, (int)data->player.x, (int)data->player.y);

    while (1)
    {

        step_x.first.x += step_x.d_x;
        step_x.first.y += step_x.d_y;
        
        step_y.first.x += step_y.d_x;
        step_y.first.y += step_y.d_y;
        if (is_wall(data, step_x.first.x, step_x.first.y) || is_wall(data, step_y.first.x, step_y.first.y))
            break;

        step_x.distance = get_distance(data, step_x.first.x, step_x.first.y);
        step_y.distance = get_distance(data, step_y.first.x, step_y.first.y);
    }

    // printf("distance 1 : %d, distance 2: %d \n", step_x.distance, step_y.distance);
    if (step_x.distance >= step_y.distance)
    {
        render_wall(data, step_y.distance, step_y.first.x);
        draw_line(data, data->player.x, data->player.y, step_y.first.x, step_y.first.y);
    }
    else
    {
        render_wall(data, step_x.distance, step_x.first.x);
        draw_line(data, data->player.x, data->player.y, step_x.first.x, step_x.first.y);
    }

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
    angle_incr = FOV_ANGL / WIDTH;
    ray_angle = normalize_angle(data->player.rotation_angle - (FOV_ANGL / 2)); // orig

    while (i < WIDTH)
    {
        ft_dda(data, ray_angle);
        ray_angle = normalize_angle(ray_angle + angle_incr);
        i++;
    }
}
