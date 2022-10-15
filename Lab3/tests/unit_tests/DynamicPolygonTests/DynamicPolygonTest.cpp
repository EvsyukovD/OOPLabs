#include "DynamicPolygon.hpp"
#include "gtest/gtest.h"

//#define _CRTDBG_MAP_ALLOC

DynamicPolygon::Polygon f(DynamicPolygon::Polygon &p) {
    DynamicPolygon::Polygon x(p);
    return x;
}

TEST(DynamicPolygonConstructors, ArrayInitConstructor) {
    Math::Point points[] = {{0, -1},
                            {0, 1}};
    DynamicPolygon::Polygon polygon(2, points);
    EXPECT_EQ(2, polygon.getNodesNum());
    const double error = 0.1;
    EXPECT_NEAR(0.0, polygon[0].x, error);
    EXPECT_NEAR(-1.0, polygon[0].y, error);
    EXPECT_NEAR(0.0, polygon[1].x, error);
    EXPECT_NEAR(1.0, polygon[1].y, error);
}

TEST(DynamicPolygonConstructors, CopyConstructor) {
    Math::Point points[] = {{0, -1},
                            {0, 1}};
    DynamicPolygon::Polygon polygon(2, points);
    DynamicPolygon::Polygon p(polygon);
    EXPECT_EQ(2, p.getNodesNum());
    const double error = 0.1;
    EXPECT_NEAR(0.0, p[0].x, error);
    EXPECT_NEAR(-1.0, p[0].y, error);
    EXPECT_NEAR(0.0, p[1].x, error);
    EXPECT_NEAR(1.0, p[1].y, error);
}

TEST(DynamicPolygonConstructors, MoveConstructor) {
    Math::Point points[] = {{0, -1},
                            {0, 1}};
    DynamicPolygon::Polygon polygon(2, points);
    DynamicPolygon::Polygon p(f(polygon));
    EXPECT_EQ(2, p.getNodesNum());
    const double error = 0.1;
    EXPECT_NEAR(0.0, p[0].x, error);
    EXPECT_NEAR(-1.0, p[0].y, error);
    EXPECT_NEAR(0.0, p[1].x, error);
    EXPECT_NEAR(1.0, p[1].y, error);
}

TEST(DynamicPolygonMethods, Add) {
    Math::Point points[] = {{0, -1},
                            {0, 1}};
    DynamicPolygon::Polygon polygon(2, points), p;
    Math::Point point1(1, 0), point2(0, -1);
    polygon.add(point1);
    p.add(point1);
    const double error = 0.1;
    EXPECT_NEAR(1.0, p[0].x, error);
    EXPECT_NEAR(0.0, p[0].y, error);
    EXPECT_NEAR(1.0, polygon[2].x, error);
    EXPECT_NEAR(0.0, polygon[2].y, error);
    EXPECT_THROW(p.add(point1), std::logic_error);
    EXPECT_THROW(polygon.add(point2), std::logic_error);
}

TEST(DynamicPolygonOperators, Input) {
    DynamicPolygon::Polygon polygon;
    const char *inputStr = "2 0.0 0.0 0.0 1.0\n";
    std::istringstream input(inputStr);
    input >> polygon;
    char *s = polygon.toString();
    EXPECT_STREQ(s, "(0.00, 0.00)(0.00, 1.00)");
    delete[] s;
}

TEST(DynamicPolygonOperators, Assignment) {
    Math::Point points[] = {{0, -1},
                            {0, 1}};
    Math::Point points2[] = {{0, 1},
                             {0, -1}};
    DynamicPolygon::Polygon polygon(2, points), p(2, points2);
    p = polygon;
    char *s1 = p.toString(),*s2 = polygon.toString();
    EXPECT_STREQ(s1,s2);
    delete[] s1;
    DynamicPolygon::Polygon p2 = f(polygon);
    s1 = p2.toString();
    EXPECT_STREQ(s1,s2);
    delete[] s1;
    delete[] s2;
}

int main(int argc, char** argv){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}