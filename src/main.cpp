#include "vec3.h"
#include "ray.h"

#include <fstream>

color get_color(const Ray& ray) {
    vec3f direction = ray.getDirection().getNormalized();

    float t = 0.5 * (direction.y() + 1.0);

    vec3f color_ = (1.0 - t) * vec3f(1.0, 1.0, 1.0) + t * vec3f(0.5, 0.7, 1.0);

    return convert<float, unsigned char>(color_);
}


int main() {
    std::ofstream out("image.ppm");

    size_t width = 400;
    size_t height = 300;

    out << "P3" << '\n';
    out << width << " " << height << '\n';
    out << "255" << '\n';

    vec3f lower_left(-2.0, -1.0, 1.0);
    vec3f horizontal(4.0, 0.0, 0.0);
    vec3f vertical(0.0, 2.0, 0.0);
    vec3f origin(0.0, 0.0, 0.0);

    for (size_t y = height - 1; y >= 0; y--)
        for (size_t x = 0; x < width; x++) {
           float u = float(x) / float(width); 
           float v = float(y) / float(height);

           Ray ray(origin, lower_left + u * horizontal + v * vertical);

           color ray_color = get_color(ray);

           out << ray_color[0] << ' ' 
               << ray_color[1] << ' ' 
               << ray_color[2] << '\n';
        }

    return 0;
}
