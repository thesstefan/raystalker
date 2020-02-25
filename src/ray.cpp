#include "ray.h"

Ray::Ray() {}

Ray::Ray(const vec3f& origin, const vec3f& direction) :
    origin(origin), direction(direction) {}

vec3f Ray::getOrigin() const {
    return origin;
}

vec3f Ray::getDirection() const {
    return direction;
}

vec3f Ray::pointAtParameter(float t) const {
    return origin + direction * t;
}
