#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <raylib.h>
#include "ray.hpp"

TEST_CASE("Basic Vector2 extension tests", "[unit],[Vector2]") {
    SECTION("Vector2 basic operations") {
        REQUIRE(Vector2{20.0f, 20.0f} == Vector2{10.0f, 10.f} + Vector2{10.0f, 10.f});
        REQUIRE(Vector2{1010.0f, -990.0f} == Vector2{1000.0f, -1000.f} + Vector2{10.0f, 10.f});
        auto c = Vector2{1000.0f, -1000.f} + Vector2{-1000.0f, 1000.f};
        REQUIRE(Vector2{0.0f, 0.0f} == c);
    }
}

TEST_CASE("Basic Vector2Set tests", "[unit][Vector2]") {
    SECTION("Lazy basic test") {
        Vector2Set set{};
        REQUIRE(set.size() == 0);

        set.emplace(Vector2{0.0f, 0.0f});
        REQUIRE(set.size() == 1);

        set.emplace(Vector2{0.0f, 0.0f});
        set.emplace(Vector2{0.0f, 0.0f});
        set.emplace(Vector2{0.0f, 0.0f});
        REQUIRE(set.size() == 1);

        for (std::size_t i = 0; i < 2; ++i) {
            for (std::size_t y = 0; y < 50; ++y) {
                for (std::size_t x = 0; x < 50; ++x) {
                    set.emplace(Vector2{
                        static_cast<float>(x),
                        static_cast<float>(y)
                    });
                }
            }
        }
        REQUIRE(set.size() == 50 * 50);

        set.clear();
        REQUIRE(set.size() == 0);
        REQUIRE(set.empty());
    }
}