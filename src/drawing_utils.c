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

double get_distance(t_data data, int x_wall, int y_wall, int num_pixels)
{
    // if (num_pixels < 1)
    // return 0.0;
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
    while (1)
    {
        if (is_wall(data, x1, y1))
            return get_distance(data, x1, y1, i);
        protected_ppx(data.img, x1, y1, get_rgba(255, 0, 0, 255));
        i++;
        if (x1 == x2 && y1 == y2)
            return get_distance(data, x1, y1, i);
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

int floor_division(int a, int b)
{
    if (b == 0)
        return 0;
    double result = (double)a / b;
    return (int)floor(result);
}

int is_up(double angle)
{
    return (angle >= M_PI / 2 && angle < M_PI);
}

int is_right(double angle)
{
    return (angle >= 0 && angle < M_PI / 2);
}

void ft_dda(t_data data, double ray_angle, double start_x, double start_y)
{
    double step_1; // delta_x 
    double step_2; // delta_y

    double x; // gonna be the end point where the ray hits the wall
    double y; // gonna be the end point where the ray hits the wall

    // function must get first intersections x an y.
    x = start_x;
    y = start_y;

    // TODO : Check direction and adjust params accordingly
    // the direction counts and can change sign or first intersection coordinates
        // in diffrent cases 
        
    // TODO calculate step_1 and step_2
    // option 1 : from first intersection with the first horizontal line .
        // step 1 starts from it until next horizontal intersection 
        // => from (x, y) we move to (x + step_1 , y + tile_size)

    // option 2 : from first intersection with the first vertical line .
        // step 2 starts from it until next vertical intersection
        // => from (x, y) we move to (x + tile_size , y + step_2)

    // distance is the first to hit the wall from both options.
    // x and y will automatically be calculated by the first value to hit the wall.

    // finally : draw ray.
    draw_line(data, data.player.x, data.player.y, (int)x, (int)y);
}

double get_first_x(t_data data); // TODO
double get_first_y(t_data data); // TODO

void draw_rays(t_data data)
{
    double angle;
    double ray_angle;
    double first_x;
    double first_y;

    ray_angle = FOV_ANGL / WIDTH;
    angle = normalize_angle(data.player.rotation_angle - (FOV_ANGL / 2));
    
    while (angle <= FOV_ANGL)
    {
        ft_dda(data, angle, get_first_x(data), get_first_y(data));
        angle = normalize_angle(angle + ray_angle);
    }
}
