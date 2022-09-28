#include "../../lib/Lab3.hpp"
#include "gtest/gtest.h"

TEST(SimplePolygonConstructors, EmptyConstructor) {
    Lab3::SimplePolygon::Polygon polygon;
    ASSERT_EQ(0, polygon.getNodesNum());
    ASSERT_THROW(polygon.get(0), std::out_of_range);
}

TEST(SimplePolygonConstructors, OnePointConstructor) {
    Lab3::Point p(1.0, 1.0);
    Lab3::SimplePolygon::Polygon polygon(p);
    ASSERT_EQ(1, polygon.getNodesNum());
    const double error = 0.1;
    Lab3::Point a = polygon.get(0);
    ASSERT_NEAR(p.x, a.x, error);
    ASSERT_NEAR(p.y, a.y, error);
}

TEST(SimplePolygonConstructors, ArrayOfPointsConstructor) {
    Lab3::Point points1[] = {{1.0, 1.0},
                             {2.0, 3.0}};
    Lab3::Point points2[30];
    Lab3::Point points3[] = {{1.0, 1.0},
                             {2.0, 2.5},
                             {1.0, 1.0}};
    const double error = 0.1;
    Lab3::SimplePolygon::Polygon polygon(2, points1);
    Lab3::Point a = polygon.get(0);
    Lab3::Point b = polygon.get(1);
    ASSERT_NEAR(points1[0].x, a.x, error);
    ASSERT_NEAR(points1[0].y, a.y, error);
    ASSERT_NEAR(points1[1].x, b.x, error);
    ASSERT_NEAR(points1[1].y, b.y, error);
    ASSERT_THROW(Lab3::SimplePolygon::Polygon(30, points2), std::length_error);
    ASSERT_THROW(Lab3::SimplePolygon::Polygon(3, points3), std::logic_error);
}

TEST(SimplePolygonMethods, Getters) {
    Lab3::Point points[] = {{0.0, 0.0},
                            {0.1, 3.4},
                            {0.3, 4.6}};
    Lab3::SimplePolygon::Polygon polygon(3, points);
    const double error = 0.1;
    Lab3::Point a = polygon.get(0);
    Lab3::Point b = polygon.get(1);
    Lab3::Point c = polygon.get(2);
    ASSERT_EQ(3, polygon.getNodesNum());
    ASSERT_NEAR(points[0].x, a.x, error);
    ASSERT_NEAR(points[0].y, a.y, error);
    ASSERT_NEAR(points[1].x, b.x, error);
    ASSERT_NEAR(points[1].y, b.y, error);
    ASSERT_NEAR(points[2].x, c.x, error);
    ASSERT_NEAR(points[2].y, c.y, error);
    ASSERT_THROW(polygon.get(3), std::out_of_range);
    ASSERT_THROW(polygon.get(-3), std::out_of_range);
}

TEST(SimplePolygonMethods, Setters) {
    Lab3::Point points[] = {{0.0, 0.0},
                            {0.1, 3.4},
                            {0.3, 4.6}};
    Lab3::SimplePolygon::Polygon polygon(3, points);
    Lab3::Point p(1.0, 1.0), t(0.1, 3.4);
    polygon.set(p, 0);
    Lab3::Point a = polygon.get(0);
    const double error = 0.1;
    ASSERT_NEAR(p.x, a.x, error);
    ASSERT_NEAR(p.y, a.y, error);
    ASSERT_THROW(polygon.set(t, 0), std::logic_error);
    ASSERT_THROW(polygon.set(p, 4), std::out_of_range);
    ASSERT_THROW(polygon.set(p, -4), std::out_of_range);
}

TEST(SimplePolygonMethods, Transformations) {
    Lab3::Point points[] = {{0.0, 0.0},
                            {0.0, 1.0},
                            {1.0, 1.0}};
    Lab3::SimplePolygon::Polygon polygon(3, points);

    polygon.rotate(1);

    const double error = 0.001;
    Lab3::Point newPoints[] = {polygon.get(0),
                               polygon.get(1),
                               polygon.get(2)};

    ASSERT_NEAR(newPoints[0].x, 0.0, error);
    ASSERT_NEAR(newPoints[0].y, 0.0, error);
    ASSERT_NEAR(newPoints[1].x, -1.0, error);
    ASSERT_NEAR(newPoints[1].y, 0.0, error);
    ASSERT_NEAR(newPoints[2].x, -1.0, error);
    ASSERT_NEAR(newPoints[2].y, 1.0, error);

    polygon = Lab3::SimplePolygon::Polygon(3, points);
    polygon.move({0.0,1.0});
    newPoints[0] = polygon.get(0);
    newPoints[1] = polygon.get(1);
    newPoints[2] = polygon.get(2);

    ASSERT_NEAR(newPoints[0].x, 0.0, error);
    ASSERT_NEAR(newPoints[0].y, 1.0, error);
    ASSERT_NEAR(newPoints[1].x, 0.0, error);
    ASSERT_NEAR(newPoints[1].y, 2.0, error);
    ASSERT_NEAR(newPoints[2].x, 1.0, error);
    ASSERT_NEAR(newPoints[2].y, 2.0, error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest();
    return ::RUN_ALL_TESTS();
}