#include "doctest.h"
#include "vec3.h"

#include <limits>

TEST_CASE( "vec3 constructors and component access" ) {
    SUBCASE( "vec3f (float)" ) {
        SUBCASE( "default constructor" ) {
            const vec3f vec;

            CHECK( vec.x() == 0.0f );
            CHECK( vec.y() == 0.0f );
            CHECK( vec.z() == 0.0f );

            CHECK( vec[0] == 0.0f );
            CHECK( vec[1] == 0.0f );
            CHECK( vec[2] == 0.0f );
        }

        SUBCASE( "constructor with components" ) {
            const vec3f vec(123.2, 213.2, 123213.2);

            CHECK( vec.x() == 123.2f );
            CHECK( vec.y() == 213.2f );
            CHECK( vec.z() == 123213.2f );

            CHECK( vec[0] == 123.2f );
            CHECK( vec[1] == 213.2f );
            CHECK( vec[2] == 123213.2f );
        }

        SUBCASE( "copy constructor" ) {
            const vec3f vec_1(213, 132, 31);
            const vec3f vec_2(vec_1);

            CHECK ( vec_1 == vec_2 );
        }
    }

    SUBCASE( "color (unsigned char)" ) {
        SUBCASE( "default constructor" ) {
            const color col;

            CHECK( col.x() == 0 );
            CHECK( col.y() == 0 );
            CHECK( col.z() == 0 );

            CHECK( col[0] == 0 );
            CHECK( col[1] == 0 );
            CHECK( col[2] == 0 );
        }

        SUBCASE( "constructor with components" ) {
            const color col(255, 255, 128);

            CHECK( col.x() == 255 );
            CHECK( col.y() == 255 );
            CHECK( col.z() == 128 );

            CHECK( col[0] == 255 );
            CHECK( col[1] == 255 );
            CHECK( col[2] == 128 );
        }

        SUBCASE( "copy constructor" ) {
            const vec3f vec_1(213, 132, 31);
            const vec3f vec_2(vec_1);

            CHECK ( vec_1 == vec_2 );
        }
    }

    SUBCASE( "[] out of bounds access" ) {
        SUBCASE( "negative index" ) {
            const vec3f vec(12321, 12321, 1941);
            bool thrown = false;

            try {
                vec[-1];
            } catch (const std::out_of_range& exception) {
                thrown = true;
            }

            CHECK( thrown == true );
        }

        SUBCASE( "bigger than 2" ) {
            const color col(123, 123, 232);
            bool thrown = false;

            try {
                col[3];
            } catch (const std::out_of_range& exception) {
                thrown = true;
            }

            CHECK( thrown == true );
        }
    }
}

TEST_CASE( "vec3 operators" ) {
    SUBCASE( "vec3f (float)" ) {
        SUBCASE( "equality and inequality" ) {
            vec3f vec_1(100, 200, 300);
            vec3f vec_2(100, 200, 300);

            CHECK ( vec_1 == vec_2 );
            CHECK ( !(vec_1 != vec_2) );
        }

        SUBCASE( "assignment" ) {
            vec3f vec_1(100, 200, 300);
            vec3f vec_2(500, 600, 700);

            vec_1 = vec_2;

            CHECK ( vec_1 == vec_2 );
        }

        SUBCASE( "addition" ) {
            SUBCASE( "operator+()" ) {
                vec3f vec_1(100, 200, 300);
                vec3f vec_2(50, 30, 10);

                CHECK( vec_1 + vec_2 == vec3f(150, 230, 310) );
                CHECK( vec_2 + vec_1 == vec3f(150, 230, 310) );
            } 

            SUBCASE( "operator+=(vec3f)" ) {
                vec3f vec_1(100, 200, 300);
                vec3f vec_2(50, 30, 10);

                vec_1 += vec_2;

                CHECK( vec_1.x() == 150 );
                CHECK( vec_1.y() == 230 );
                CHECK( vec_1.z() == 310 );
            }
        }

        SUBCASE( "subtraction" ) {
            SUBCASE( "operator-()" ) {
                vec3f vec_1(100, 200, 200);
                vec3f vec_2(50, 30, 10);

                CHECK( (vec_1 - vec_2).x() == 50 );
                CHECK( (vec_1 - vec_2).y() == 170 );
                CHECK( (vec_1 - vec_2).z() == 190 );
            } 

            SUBCASE( "operator-=(vec3f)" ) {
                vec3f vec_1(100, 200, 300);
                vec3f vec_2(50, 30, 10);

                vec_1 -= vec_2;

                CHECK( vec_1.x() == 50 );
                CHECK( vec_1.y() == 170 );
                CHECK( vec_1.z() == 290 );
            }
        }

        SUBCASE( "multiplication" ) {
            SUBCASE( "by vector" ) {
                SUBCASE( "operator*(vec3f)" ) {
                    vec3f vec_1(100, 200, 300);
                    vec3f vec_2(50, 30, 10);

                    CHECK( (vec_1 * vec_2).x() == 5000 );
                    CHECK( (vec_1 * vec_2).y() == 6000 );
                    CHECK( (vec_1 * vec_2).z() == 3000 );
                } 

                SUBCASE( "operator*=(vec3f)" ) {
                    vec3f vec_1(100, 200, 300);
                    vec3f vec_2(50, 30, 10);

                    vec_1 *= vec_2;

                    CHECK( vec_1.x() == 5000 );
                    CHECK( vec_1.y() == 6000 );
                    CHECK( vec_1.z() == 3000 );
                }
            }

            SUBCASE( "by value" ) {
                SUBCASE( "operator*(float)" ) {
                    vec3f vec(100, 200, 300);
                    float val = 2.5;

                    CHECK( (vec * val).x() == 250 );
                    CHECK( (vec * val).y() == 500 );
                    CHECK( (vec * val).z() == 750 );
                } 

               SUBCASE( "operator*=(float)" ) {
                    vec3f vec(100, 200, 300);
                    float val = 2.5;
                    
                    vec *= val;

                    CHECK( vec.x() == 250 );
                    CHECK( vec.y() == 500 );
                    CHECK( vec.z() == 750 );
                } 
            }
        }

        SUBCASE( "division" ) {
            SUBCASE( "by vector" ) {
                SUBCASE( "operator/(vec3f)" ) {
                    vec3f vec_1(100, 200, 300);
                    vec3f vec_2(50, 40, 10);

                    CHECK( (vec_1 / vec_2).x() == 2 );
                    CHECK( (vec_1 / vec_2).y() == 5 );
                    CHECK( (vec_1 / vec_2).z() == 30 );
                } 

                SUBCASE( "operator/=(vec3f)" ) {
                    vec3f vec_1(100, 200, 300);
                    vec3f vec_2(50, 40, 10);

                    vec_1 /= vec_2;

                    CHECK( vec_1.x() == 2 );
                    CHECK( vec_1.y() == 5 );
                    CHECK( vec_1.z() == 30 );
                }
            }

            SUBCASE( "by value" ) {
                SUBCASE( "operator/(float)" ) {
                    vec3f vec(50, 20, 30);
                    float val = 2;

                    CHECK( (vec / val).x() == 25 );
                    CHECK( (vec / val).y() == 10 );
                    CHECK( (vec / val).z() == 15 );
                } 

               SUBCASE( "operator/=(float)" ) {
                    vec3f vec(100, 200, 300);
                    float val = 2.5;
                    
                    vec /= val;

                    CHECK( vec.x() == 40 );
                    CHECK( vec.y() == 80 );
                    CHECK( vec.z() == 120 );
                } 
            }
        }
    }

    SUBCASE( "color (unsigned char) " ) {
        SUBCASE( "equality and inequality" ) {
            color col_1(100, 200, 50);
            color col_2(100, 200, 50);

            CHECK ( col_1 == col_2 );
            CHECK ( !(col_1 != col_2) );
        }

        SUBCASE( "assignment" ) {
            vec3f vec_1(100, 200, 10);
            vec3f vec_2(50, 60, 70);

            vec_1 = vec_2;

            CHECK ( vec_1 == vec_2 );
        }

        SUBCASE( "addition" ) {
            SUBCASE( "operator+()" ) {
                color col_1(100, 200, 50);
                color col_2(50, 30, 10);

                CHECK( col_1 + col_2 == color(150, 230, 60) );
                CHECK( col_2 + col_1 == color(150, 230, 60) );
            } 

            SUBCASE( "operator+=(color)" ) {
                color col_1(100, 200, 50);
                color col_2(50, 30, 10);

                col_1 += col_2;

                CHECK( col_1.x() == 150 );
                CHECK( col_1.y() == 230 );
                CHECK( col_1.z() == 60 );
            }
        }

        SUBCASE( "subtraction" ) {
            SUBCASE( "operator-()" ) {
                color col_1(100, 200, 200);
                color col_2(50, 30, 10);

                CHECK( (col_1 - col_2).x() == 50 );
                CHECK( (col_1 - col_2).y() == 170 );
                CHECK( (col_1 - col_2).z() == 190 );
            } 

            SUBCASE( "operator-=(color)" ) {
                color col_1(100, 200, 200);
                color col_2(50, 30, 10);

                col_1 -= col_2;

                CHECK( col_1.x() == 50 );
                CHECK( col_1.y() == 170 );
                CHECK( col_1.z() == 190 );
            }
        }

        SUBCASE( "multiplication" ) {
            SUBCASE( "by vector" ) {
                SUBCASE( "operator*(color)" ) {
                    color col_1(100, 100, 100);
                    color col_2(1, 2, 2);

                    CHECK( (col_1 * col_2).x() == 100 );
                    CHECK( (col_1 * col_2).y() == 200 );
                    CHECK( (col_1 * col_2).z() == 200 );
                } 

                SUBCASE( "operator*=(color)" ) {
                    color col_1(100, 100, 100);
                    color col_2(1, 2, 2);

                    col_1 *= col_2;

                    CHECK( col_1.x() == 100 );
                    CHECK( col_1.y() == 200 );
                    CHECK( col_1.z() == 200 );
                }
            }
            
            SUBCASE( "by value" ) {
                SUBCASE( "operator*(unsigned char)" ) {
                    color col(15, 20, 10);
                    unsigned char val = 5;

                    CHECK( (col * val).x() == 75 );
                    CHECK( (col * val).y() == 100 );
                    CHECK( (col * val).z() == 50 );
                } 

               SUBCASE( "operator*=(unsigned char)" ) {
                    color col(10, 20, 30);
                    unsigned char val = 5;
                    
                    col *= val;

                    CHECK( col.x() == 50 );
                    CHECK( col.y() == 100 );
                    CHECK( col.z() == 150 );
                } 
            }
        }

        SUBCASE( "division" ) {
            SUBCASE( "by vector" ) {
                SUBCASE( "operator/(color)" ) {
                    color col_1(100, 200, 200);
                    color col_2(50, 40, 10);

                    CHECK( (col_1 / col_2).x() == 2 );
                    CHECK( (col_1 / col_2).y() == 5 );
                    CHECK( (col_1 / col_2).z() == 20 );
                } 

                SUBCASE( "operator/=(color)" ) {
                    color col_1(100, 200, 200);
                    color col_2(50, 40, 10);

                    col_1 /= col_2;

                    CHECK( col_1.x() == 2 );
                    CHECK( col_1.y() == 5 );
                    CHECK( col_1.z() == 20 );
                }
            }

            SUBCASE( "by value" ) {
                SUBCASE( "operator/(unsigned char)" ) {
                    color col(50, 20, 30);
                    unsigned char val = 2;

                    CHECK( (col / val).x() == 25 );
                    CHECK( (col / val).y() == 10 );
                    CHECK( (col / val).z() == 15 );
                } 

               SUBCASE( "operator/=(unsigned char)" ) {
                    color col(50, 20, 30);
                    unsigned char val = 2;
                    
                    col /= val;

                    CHECK( col.x() == 25 );
                    CHECK( col.y() == 10 );
                    CHECK( col.z() == 15 );
                } 
            }
        }
    }
}

TEST_CASE( "vec3 dot & cross") {
    SUBCASE( "vec3f (float)" ) {
        SUBCASE( "dot" ) {
            vec3f vec_1(2, 3, 4);
            vec3f vec_2(0.5, 0.5, 0.5);

            CHECK( dot(vec_1, vec_2) == 4.5 );
            CHECK( dot(vec_2, vec_1) == 4.5 );
        }

        SUBCASE( "cross" ) {
            vec3f vec_1(2, 3, 4);
            vec3f vec_2(0.5, 2, 3);

            CHECK ( cross(vec_1, vec_2).x() == 1 );
            CHECK ( cross(vec_1, vec_2).y() == -4 );
            CHECK ( cross(vec_1, vec_2).z() == 2.5 );

        }
    }

    SUBCASE( "color (unsigned char)" ) {
        SUBCASE( "dot" ) {
            color col_1(2, 3, 4);
            color col_2(2, 3, 4);

            CHECK( dot(col_1, col_2) == 29 );
            CHECK( dot(col_2, col_1) == 29 );
        }

        SUBCASE( "cross" ) {
            color col_1(2, 3, 4);
            color col_2(1, 2, 3);

            CHECK ( cross(col_1, col_2).x() == 1 );
            CHECK ( cross(col_1, col_2).y() == 254 );
            CHECK ( cross(col_1, col_2).z() == 1 );
        }
    }
}

TEST_CASE( "vec3 length" ) {
    SUBCASE( "normal" ) {
        vec3f vec(3, 4, 5);

        CHECK( vec.length() == sqrt(50) );
    }

    SUBCASE( "squared" ) {
        vec3f vec(4, 5, 6);

        CHECK( vec.squared_length() == 77 );
    }
}

TEST_CASE( "vec3 normalize & getNormalized" ) {
    SUBCASE( "normalize" ) {
        vec3f vec(2, 3, 6);

        vec.normalize();

        CHECK ( vec.x() == 2 / 7.f );
        CHECK ( vec.y() == 3 / 7.f);
        CHECK ( vec.z() == 6 / 7.f );
    }

    SUBCASE( "getNormalized" ) {
        vec3f vec_1(2, 3, 6);

        vec3f vec_2 = vec_1.getNormalized();

        CHECK ( vec_2.x() == 2 / 7.f );
        CHECK ( vec_2.y() == 3 / 7.f);
        CHECK ( vec_2.z() == 6 / 7.f );
    }
}

TEST_CASE( "vec3 convert" ) {
    SUBCASE( "float -> int") {
        vec3f vec_1(123.123, 12321.3123, 123213.1);

        vec3_<int> vec_2 = vec3_convert<float, int>(vec_1);

        CHECK ( vec_2 == vec3_<int>(123, 12321, 123213) );
    }
}
