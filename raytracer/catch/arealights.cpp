#include "catch.hpp"
#include "worlds.h"
#include "point.h"
#include "engine.h"
#include "equal.h"

using namespace Raytracer::Engine;

TEST_CASE("is_shadow tests for occlusion between two points")
{
    const World w = Worlds::default_world();
    const Point light_position{-10, -10, -10};

    const std::vector<std::tuple<Point, bool>> data{
        {Point{-10, -10, 10}, false},
        {Point{10, 10, 10}, true},
        {Point{-20, -20, -20}, false},
        {Point{-5, -5, -5}, false}
    };

    for (const auto& [point, result]: data) {
        const auto r = is_shadowed(w, light_position, point);
        REQUIRE(r == result);
    }

}

TEST_CASE("Point lights evaluate the light intensity at a given point")
{
    const World w = Worlds::default_world();
    const Light light = w.lights.front();

    const std::vector<std::tuple<Point, float>> data{
        {Point{0, 1.0001, 0}, 1.0},
        {Point{-1.0001, 0, 0}, 1.0},
        {Point{0, 0, -1.0001}, 1.0},
        {Point{0, 0, 1.0001}, 0.0},
        {Point{1.0001, 0, 0}, 0.0},
        {Point{0, -1.0001, 0}, 0.0},
        {Point{0, 0, 0}, 0.0}
    };

    for (const auto& [point, result]: data) {
        const float intensity = intensity_at(light, point, w);
        REQUIRE(intensity == result);
    }
}

TEST_CASE("lighting() uses light intensity to attenuate color")
{
    World w = Worlds::default_world();
    w.lights.clear();
    w.lights.push_back(PointLight(Point{0, 0, -10}, Color{1, 1, 1}));

    w.shapes.front()->material.ambient = 0.1;
    w.shapes.front()->material.diffuse = 0.9;
    w.shapes.front()->material.specular = 0;
    w.shapes.front()->material.color = Color{1, 1, 1};

    const Point pt{0, 0, -1};
    const Vector eyev{0, 0, -1};
    const Vector normalv{0, 0, -1};

    auto res = lighting(w.shapes.front()->material, w.shapes.front().get(), w.lights.front(), pt, eyev, normalv, 1.0);
    REQUIRE(res == Color{1.0, 1.0, 1.0});

    res = lighting(w.shapes.front()->material, w.shapes.front().get(), w.lights.front(), pt, eyev, normalv, 0.5);
    REQUIRE(res == Color{0.55, 0.55, 0.55});

    res = lighting(w.shapes.front()->material, w.shapes.front().get(), w.lights.front(), pt, eyev, normalv, 0.0);
    REQUIRE(res == Color{0.1, 0.1, 0.1});
}