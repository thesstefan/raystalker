#include "doctest.h"
#include "vec3.h"

TEST_CASE( "vec3 constructor" ) {
    vec3f vec(1, 2, 3);

    CHECK( vec.x() == 1);
}

TEST_CASE( "vec3 operator+=" ) {
    vec3f vec1(1, 2, 3);
    vec3f vec2(5, 6, 7);

    vec3f vec3 = vec1 + vec2;

    CHECK( vec3.x() == 6 );
    CHECK( vec3.y() == 8 );
    CHECK( vec3.z() == 10 );
}
