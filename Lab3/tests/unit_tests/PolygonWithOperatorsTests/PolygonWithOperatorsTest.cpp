#include "PolygonWithOperators.hpp"
#include "gtest/gtest.h"

TEST(PolygonWithOperatorsConstructors, CopyConstructor) {
    Math::Point points[] = {{0, 0},
                            {0, 1}};
    PolygonWithOperators::Polygon polygon(2, points);
    PolygonWithOperators::Polygon pol(polygon);
    Math::Point a = pol[0], b = pol[1];
    const double error = 0.1;
    EXPECT_EQ(2, pol.getNodesNum());
    EXPECT_NEAR(a.x, 0.0, error);
    EXPECT_NEAR(a.y, 0.0, error);
    EXPECT_NEAR(b.x, 0.0, error);
    EXPECT_NEAR(b.y, 1.0, error);
}

TEST(PolygonWithOperatorsOperators, IOOperators) {
    PolygonWithOperators::Polygon polygon;
    const char *inputStr = "2 0.0 0.0 0.0 1.0\n";
    std::istringstream input(inputStr);
    input >> polygon;
    char *s = polygon.toString();
    EXPECT_STREQ(s, "(0.00, 0.00)(0.00, 1.00)");
    delete[] s;
    std::ostringstream output;
    output << polygon;
    std::string str = output.str();
    EXPECT_TRUE(str == "(0.00, 0.00)(0.00, 1.00)");
}

TEST(PolygonWithOperatorsOperators, UnaryPlusAndMinus) {
    Math::Point points[] = {{0, -1},
                            {0, 1}};
    PolygonWithOperators::Polygon polygon1(2, points), polygon2(2, points);
    std::ostringstream output1, output2, output3, output4;
    output1 << polygon1++;
    output2 << ++polygon2;
    std::string s1 = output1.str(), s2 = output2.str();
    EXPECT_TRUE(s1 == "(0.00, -1.00)(0.00, 1.00)");
    EXPECT_TRUE(s2 == "(1.00, 0.00)(1.00, 2.00)");

    output3 << polygon1--;
    output4 << --polygon2;
    std::string s3 = output3.str(), s4 = output4.str();
    EXPECT_TRUE(s3 == "(1.00, 0.00)(1.00, 2.00)");
    EXPECT_TRUE(s4 == "(0.00, -1.00)(0.00, 1.00)");
}

TEST(PolygonWithOperatorsOperators, Brackets) {
    Math::Point points[] = {{0, 0},
                            {0, 1}};
    PolygonWithOperators::Polygon polygon(2, points);

    Math::Point p0 = polygon[0], p1 = polygon[1];
    const double error = 0.1;
    EXPECT_NEAR(p0.x, 0.0, error);
    EXPECT_NEAR(p0.y, 0.0, error);
    EXPECT_NEAR(p1.x, 0.0, error);
    EXPECT_NEAR(p1.y, 1.0, error);
    int i = polygon[{0.0, 0.0}], j = polygon[{0.0, 1.0}];
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 1);

    polygon(1);
    p0 = polygon[0];
    p1 = polygon[1];
    EXPECT_NEAR(p0.x, 0.0, error);
    EXPECT_NEAR(p0.y, 0.0, error);
    EXPECT_NEAR(p1.x, -1.0, error);
    EXPECT_NEAR(p1.y, 0.0, error);
    EXPECT_THROW(polygon(-1), std::invalid_argument);
}


TEST(PolygonWithOperatorsOperators, Sum) {
    Math::Point points1[] = {{0, 0},
                             {0, 1}};
    Math::Point points2[] = {{0, 0},
                             {1, 2}};
    PolygonWithOperators::Polygon polygon1(2, points1), polygon2(2, points2);
    PolygonWithOperators::Polygon polygon3 = polygon1 + polygon2;
    PolygonWithOperators::Polygon polygon4 = polygon2 + polygon1;
    PolygonWithOperators::Polygon polygon5 = polygon1 + polygon1;
    char *s = polygon3.toString();
    EXPECT_STREQ(s, "(0.00, 0.00)(0.00, 1.00)(1.00, 2.00)");
    delete[] s;
    s = polygon4.toString();
    EXPECT_STREQ(s, "(0.00, 0.00)(1.00, 2.00)(0.00, 1.00)");
    delete[] s;
    s = polygon5.toString();
    EXPECT_STREQ(s, "(0.00, 0.00)(0.00, 1.00)");
    delete[] s;
    polygon1 += polygon2;
    s = polygon1.toString();
    EXPECT_STREQ(s, "(0.00, 0.00)(0.00, 1.00)(1.00, 2.00)");
    delete[] s;
}

TEST(PolygonWithOperatorsOperators, Transformations) {
    Math::Point points1[] = {{0, 0},
                             {0, 1}};
    PolygonWithOperators::Polygon polygon1(2, points1);
    const Math::Point *points2 = (const Math::Point *) polygon1;
    const double error = 0.1;
    EXPECT_NEAR(points2[0].x, points1[0].x, error);
    EXPECT_NEAR(points2[0].y, points1[0].y, error);
    EXPECT_NEAR(points2[1].x, points1[1].x, error);
    EXPECT_NEAR(points2[1].y, points1[1].y, error);
}

TEST(PolygonWithOperatorsOperators, BoolOperators) {
    Math::Point points1[] = {{0, 0},
                             {1, 0}};
    Math::Point points2[] = {{0, 0},
                             {2, 0}};
    PolygonWithOperators::Polygon polygon1(2, points1),
            polygon2(2, points1), polygon3(2, points2),
            polygon4;
    EXPECT_TRUE(polygon1 == polygon2);
    EXPECT_TRUE(polygon1 < polygon3);
    EXPECT_TRUE(polygon3 > polygon1);
    EXPECT_TRUE(polygon4 < polygon1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
