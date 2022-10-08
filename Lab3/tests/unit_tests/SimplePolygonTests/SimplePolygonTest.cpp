#include "SimplePolygon.hpp"
#include "gtest/gtest.h"

TEST(SimplePolygonConstructors, EmptyConstructor) {
    SimplePolygon::Polygon polygon;
    ASSERT_EQ(0, polygon.getNodesNum());
    ASSERT_THROW(polygon.get(0), std::out_of_range);
}

TEST(SimplePolygonConstructors, OnePointConstructor) {
    Math::Point p(1.0, 1.0);
    SimplePolygon::Polygon polygon(p);
    ASSERT_EQ(1, polygon.getNodesNum());
    const double error = 0.1;
    Math::Point a = polygon.get(0);
    ASSERT_NEAR(p.x, a.x, error);
    ASSERT_NEAR(p.y, a.y, error);
}

TEST(SimplePolygonConstructors, ArrayOfPointsConstructor) {
    Math::Point points1[] = {{1.0, 1.0},
                             {2.0, 3.0}};
    Math::Point points2[30];
    Math::Point points3[] = {{1.0, 1.0},
                             {2.0, 2.5},
                             {1.0, 1.0}};
    const double error = 0.1;
    SimplePolygon::Polygon polygon(2, points1);
    Math::Point a = polygon.get(0);
    Math::Point b = polygon.get(1);
    ASSERT_NEAR(points1[0].x, a.x, error);
    ASSERT_NEAR(points1[0].y, a.y, error);
    ASSERT_NEAR(points1[1].x, b.x, error);
    ASSERT_NEAR(points1[1].y, b.y, error);
    ASSERT_THROW(SimplePolygon::Polygon(30, points2), std::length_error);
    ASSERT_THROW(SimplePolygon::Polygon(3, points3), std::logic_error);
}

TEST(SimplePolygonMethods, Getters) {
    Math::Point points[] = {{0.0, 0.0},
                            {0.1, 3.4},
                            {0.3, 4.6}};
    SimplePolygon::Polygon polygon(3, points);
    const double error = 0.1;
    Math::Point a = polygon.get(0);
    Math::Point b = polygon.get(1);
    Math::Point c = polygon.get(2);
    ASSERT_EQ(3, polygon.getNodesNum());
    ASSERT_NEAR(points[0].x, a.x, error);
    ASSERT_NEAR(points[0].y, a.y, error);
    ASSERT_NEAR(points[1].x, b.x, error);
    ASSERT_NEAR(points[1].y, b.y, error);
    ASSERT_NEAR(points[2].x, c.x, error);
    ASSERT_NEAR(points[2].y, c.y, error);
    ASSERT_THROW(polygon.get(3), std::out_of_range);
    ASSERT_THROW(polygon.get(-3), std::out_of_range);
    const double e = 0.001;
    Math::Point center = polygon.getGravityCenter();
    ASSERT_NEAR(center.x, 0.133, e);
    ASSERT_NEAR(center.y, 2.667, e);
}

TEST(SimplePolygonMethods, Setters) {
    Math::Point points[] = {{0.0, 0.0},
                            {0.1, 3.4},
                            {0.3, 4.6}};
    SimplePolygon::Polygon polygon(3, points);
    Math::Point p(1.0, 1.0), t(0.1, 3.4);
    polygon.set(p, 0);
    Math::Point a = polygon.get(0);
    const double error = 0.1;
    ASSERT_NEAR(p.x, a.x, error);
    ASSERT_NEAR(p.y, a.y, error);
    ASSERT_THROW(polygon.set(t, 0), std::logic_error);
    ASSERT_THROW(polygon.set(p, 4), std::out_of_range);
    ASSERT_THROW(polygon.set(p, -4), std::out_of_range);
}

TEST(SimplePolygonMethods, AddersAndReaders) {
    Math::Point points[] = {{0.0, 0.0},
                            {0.1, 3.4},
                            {0.3, 4.6}};
    Math::Point points2[20];
    for (int i = 0; i < 20; i++) {
        points2[i] = Math::Point((float) i, (float) (i + 1));
    }
    SimplePolygon::Polygon p1(3, points), p2(20, points2);
    Math::Point test1(1.2, 4.0), test2(1.0, 3.5);
    p1.add(test1);
    Math::Point g = p1.get(3);
    const double error = 0.001;
    ASSERT_NEAR(g.x, test1.x, error);
    ASSERT_NEAR(g.y, test1.y, error);
    ASSERT_THROW(p1.add(test1), std::logic_error);
    ASSERT_THROW(p2.add(test2), std::length_error);
    std::string correct = "2 0.0 0.0 1.0 1.0\n";
    std::string repeated = "2 0.0 0.0 0.0 0.0\n";
    std::string bigNum = "21 0.0 0.0 0.0 0.0\n";
    std::istringstream correctStr(correct), repeatedStr(repeated), bigNumStr(bigNum);
    SimplePolygon::Polygon p3;
    ASSERT_THROW(p1.read(repeatedStr, p3), std::logic_error);
    ASSERT_THROW(p1.read(bigNumStr, p3), std::invalid_argument);
    p1.read(correctStr, p3);
    Math::Point t0 = p3.get(0), t1 = p3.get(1);
    ASSERT_NEAR(t0.x, 0.0, error);
    ASSERT_NEAR(t0.y, 0.0, error);
    ASSERT_NEAR(t1.x, 1.0, error);
    ASSERT_NEAR(t1.y, 1.0, error);
}

TEST(SimplePolygonMethods, Transformations) {
    Math::Point points[] = {{0.0, 0.0},
                            {0.0, 1.0},
                            {1.0, 1.0}};SimplePolygon::Polygon polygon(3, points);

    polygon.rotate(1);

    const double error = 0.001;
    Math::Point newPoints[] = {polygon.get(0),
                               polygon.get(1),
                               polygon.get(2)};

    ASSERT_NEAR(newPoints[0].x, 0.0, error);
    ASSERT_NEAR(newPoints[0].y, 0.0, error);
    ASSERT_NEAR(newPoints[1].x, -1.0, error);
    ASSERT_NEAR(newPoints[1].y, 0.0, error);
    ASSERT_NEAR(newPoints[2].x, -1.0, error);
    ASSERT_NEAR(newPoints[2].y, 1.0, error);

    polygon = SimplePolygon::Polygon(3, points);
    polygon.move({0.0, 1.0});
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

TEST(SimplePolygonMethods, StringPerfomance) {
    Math::Point points[] = {{2.5, 1.0}};
    SimplePolygon::Polygon polygon(1, points);
    char *s = polygon.toString();
    ASSERT_STREQ(s, "(2.50, 1.00)");
    delete[] s;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest();
    return ::RUN_ALL_TESTS();
}