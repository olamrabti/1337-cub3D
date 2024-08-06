#include "../cub3d.h"

void protected_ppx(mlx_image_t *img, int x, int y, int color)
{
    if (x < WIDTH && x > 0 && y > 0 && y < HEIGHT)
        mlx_put_pixel(img, x, y, color);
}
void draw_rect(mlx_image_t *img, int x, int y, int color)
{
    int tmp_x;
    int tmp_y;

    tmp_x = x;
    tmp_y = y;

    // printf("[x: %d, y: %d]\n", tmp_x, tmp_y);
    while (tmp_x <= x + SIZE)
    {
        tmp_y = y;
        while (tmp_y <= y + SIZE)
        {
            if (color == 1 && (tmp_y % SIZE) && (tmp_x % SIZE))
                protected_ppx(img, tmp_x, tmp_y, get_rgba(255, 255, 255, 255));
            else
                protected_ppx(img, tmp_x, tmp_y, get_rgba(0, 0, 0, 255));
            tmp_y++;
        }
        tmp_x++;
    }
}

void draw_circle(mlx_image_t *img, int x_center, int y_center)
{
    int radius = 2;
    int x, y;

    for (y = 0; y <= radius; y++)
    {
        for (x = 0; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                protected_ppx(img, x_center + x, y_center + y, get_rgba(255, 0, 0, 255));
                protected_ppx(img, x_center - x, y_center + y, get_rgba(255, 0, 0, 255));
                protected_ppx(img, x_center + x, y_center - y, get_rgba(255, 0, 0, 255));
                protected_ppx(img, x_center - x, y_center - y, get_rgba(255, 0, 0, 255));
            }
        }
    }
}

double get_distance(t_data data, int x_wall, int y_wall)
{
    double total_distance = 0.0;
    int dx = x_wall - data.player.x;
    int dy = y_wall - data.player.y;
    total_distance += sqrt(dx * dx + dy * dy);
    return total_distance;
}

double draw_line(t_data data, int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;
    int i;
    i = 0;
    while (!is_wall(data, x2, y2))
    {
        if (is_wall(data, x1, y1))
            return get_distance(data, x1, y1);
        protected_ppx(data.img, x1, y1, get_rgba(255, 0, 0, 255));
        i++;
        if (x1 == x2 && y1 == y2)
            return get_distance(data, x1, y1);
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y1 += sy;
        }
    }
    return 0;
}

int is_wall(t_data data, int x, int y)
{

    // printf("map : %c", data.map[y / SIZE][x / SIZE]);
    // printf("x /size : %d, y / size : %d\n", x /SIZE, y/SIZE );
    if (y < 0 || x < 0 || y - (SIZE / 2) > (data.lines * SIZE) || x - (SIZE / 2) > (ft_strlen(data.map[y / SIZE]) * SIZE))
        return 0;
    if (data.map[y / SIZE][x / SIZE] == '1')
        return 1;
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

// void render_wall(t_data data, int distance , int x)
// {
//     int wall_height;
//     int wall_top;
//     int wall_bottom;
//     double scale;

//     scale = 2;
//     if (!distance)
//         distance = 1;
//     wall_height = ((int)(HEIGHT / distance) * scale);
//     wall_top = (HEIGHT - wall_height) / 2;
//     wall_bottom = (HEIGHT + wall_height) / 2;

//     // printf("wall_top : %d\n", wall_top);
//     while (wall_top < wall_bottom)
//     {
//         wall_top++;
//         protected_ppx(data.img, x , wall_top, get_rgba(255, 200, 0, 255));
//     }
// }

// void draw_rays(t_data data)
// {
//     double angle;
//     double corrected_distance;
//     int distance;
//     int x;
//     double ray_angle;

//     angle = data.player.rotation_angle - (M_PI / 6);
//     while (angle <= data.player.rotation_angle + (M_PI / 6))
//     {
//         ray_angle = angle - data.player.rotation_angle;
//         distance = draw_line(data, data.player.x, data.player.y, data.player.x + cos(angle) * WIDTH, data.player.y + sin(angle) * HEIGHT);
//         corrected_distance = distance * cos(ray_angle);
//         x = (angle - (data.player.rotation_angle - (M_PI / 6))) / (M_PI / 3) * WIDTH;
//         render_wall(data, corrected_distance, x);
//         angle += (M_PI / 3) / WIDTH;
//     }
// }

double normalize_angle(double angle)
{
    double normalized = fmod(angle, 2 * M_PI);
    if (normalized < 0)
        normalized += 2 * M_PI;
    return normalized;
}

int is_up(double angle)
{
    return (angle > M_PI);
}

int is_right(double angle)
{
    return (angle >= (3 * M_PI / 2) || angle <= M_PI / 2);
}

t_dda get_hor_inters(t_data data, double angle)
{
    t_dda step;

    step.start.y = floor(data.player.y / SIZE) * SIZE; // first horizontal intersection
    if (!is_up(angle))
        step.start.y += SIZE;
    step.start.x = data.player.x + (data.player.y - step.start.y) / tan(angle); // first horizontal intersection
    protected_ppx(data.img, step.start.x, step.start.y, get_rgba(255, 255, 255, 255));
    // delta after start
    step.d_y = SIZE;
    if (is_up(angle))
        step.d_y *= -1;
    step.d_x = (step.start.y - step.d_y) / tan(angle);
    if (!is_right(angle))
        step.d_x *= -1;

    step.end.x = step.start.x + step.d_x;
    step.end.y = step.start.y + step.d_y;
    protected_ppx(data.img, step.end.x, step.end.y, get_rgba(255, 255, 255, 255));
    step.distance = 0;
    return step;
}

t_dda get_vert_inters(t_data data, double angle)
{
    t_dda step;

    step.start.x = (floor(data.player.x / SIZE) * SIZE) + SIZE; // 
    step.start.y = data.player.y + (step.start.x - data.player.x) * tan(angle); //

    if (!is_right(angle))
        step.start.x -= SIZE;
    protected_ppx(data.img, (int)step.start.y, (int)step.start.x, get_rgba(255, 255, 255, 255));
    step.d_x = SIZE;
    step.d_y = step.d_x * tan(angle);

    if (!is_right(angle))
        step.d_x *= -1;
    if (is_up(angle))
        step.d_y *= -1;
    printf("vi_dx: %.2f", step.d_x);
    printf(" , vi_dy: %.2f\n", step.d_y);
    // printf(" , vi_dy: %.2f\n", step.d_y);
    step.end.x = step.start.x + step.d_x;
    step.end.y = step.start.y + step.d_y;
    step.distance = 0;

    return step;
}

double ft_dda(t_data data, double tmp_angle)
{
    t_dda step_x;
    t_dda step_y;

    step_x = get_hor_inters(data, tmp_angle);

    // step_y = get_vert_inters(data, tmp_angle);
    step_x.distance = get_distance(data, step_x.start.x, step_x.start.y);
    // step_y.distance = get_distance(data, step_y.start.x, step_y.start.y);

    

    // printf("distance 1 : %d, distance 2: %d \n", step_x.distance, step_y.distance);

    // draw_line(data, data.player.x, data.player.y, (data.player.x + cos(normalize_angle(data.player.rotation_angle + tmp_angle)) *step_y.distance), (data.player.y + sin(normalize_angle(data.player.rotation_angle + tmp_angle)) * step_y.distance));
    // draw_line(data, data.player.x, data.player.y, (data.player.x + cos(normalize_angle(data.player.rotation_angle + tmp_angle)) *step_y.distance), (data.player.y + sin(normalize_angle(data.player.rotation_angle + tmp_angle)) * step_y.distance));

    // while (!is_wall(data, step_x.end.x, step_x.end.y) && !is_wall(data, step_y.end.x, step_y.end.y))
    // {
    //     // protected_ppx(data.img, (int)step_x.end.y, (int)step_x.end.x, get_rgba(0, 255, 40, 0));
    //     // protected_ppx(data.img, (int)step_y.end.y, (int)step_y.end.x, get_rgba(0, 80, 0, 0));
    //     step_x.end.x += step_x.d_x;
    //     step_x.end.y += step_x.d_y;
    //     step_y.end.x += step_y.d_x;
    //     step_y.end.y += step_y.d_y;
    //     step_x.distance = get_distance(data, step_x.end.x, step_x.end.y);
    //     step_y.distance = get_distance(data, step_y.end.x, step_y.end.y);
    // }
    // if (step_x.distance < WIDTH)
    //     draw_line(data, data.player.x, data.player.y, step_x.end.x, step_x.end.y);
    // if (step_y.distance < HEIGHT)
    //     draw_line(data, data.player.x, data.player.y, step_y.end.x, step_y.end.y);
    // printf("angle : %.2f, step1_dx: %.2f ,step1_dy: %.2f", tmp_angle, step_x.d_x, step_x.d_y);
    // printf(" step2_dx: %.2f ,step2_dy: %.2f\n", step_y.d_x, step_y.d_y);
    return 0;

    // if (step_x.distance <= step_y.distance)
    //     return draw_line(data, data.player.x, data.player.y, (int)step_x.end.x, (int)step_x.end.y);
    // return draw_line(data, data.player.x, data.player.y, (int)step_y.end.x, (int)step_y.end.y);
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

void draw_rays(t_data data)
{
    double alpha;
    double ray_angle;
    double angle_incr;
    int i;

    i = 0;
    angle_incr = FOV_ANGL / WIDTH;
    // ray_angle = normalize_angle(data.player.rotation_angle - (FOV_ANGL / 2)); // orig
    ray_angle = normalize_angle(data.player.rotation_angle);

    printf("rot_angle :%.3f \n", data.player.rotation_angle);

    while (i < 1)
    {
        alpha = get_alpha(ray_angle); // FIXME angle is not well calculated
        draw_line(data, data.player.x, data.player.y, data.player.x + cos(data.player.rotation_angle) * 1000,
              data.player.y + sin(data.player.rotation_angle) * 1000);

        if (is_up(alpha))
            printf("angle is up , ");
        else
            printf("angle is down, ");
        if (is_right(alpha))
            printf("and right\n");
        else
            printf("and left\n");
        // printf("players angle :%.3f \n", normalize_angle(data.player.rotation_angle));
        // printf("ray angle :%.3f \n", normalize_angle(ray_angle));
        // printf("alpha :%.3f \n", alpha);
        ft_dda(data, alpha);
        // draw_line(data, data.player.x, data.player.y, (data.player.x + cos(normalize_angle(data.player.rotation_angle + alpha)) * 20), (data.player.y + sin(normalize_angle(data.player.rotation_angle + alpha)) * 20));
        // alpha = normalize_angle(alpha + angle_incr);
        i++;
    }
}
