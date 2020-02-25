#pragma once

#include "vec3.h"

class Ray {
    private:
        vec3f origin;
        vec3f direction;

    public:
        Ray();
        Ray(const vec3f& origin, const vec3f& direction);

        vec3f getOrigin() const;
        vec3f getDirection() const;

        vec3f pointAtParameter(float t) const;
};
