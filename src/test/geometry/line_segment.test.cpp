#include "../util.hpp"

#include "../../engine/geometry/line_segment.hpp"
using namespace engine::geometry;

TEST(LineSegmentTest, Constructs1DLine1) {
  LineSegment<1> line_segment(Point<1>(-4.2F), Point<1>(0.3F));

  EXPECT_EQ(line_segment.a(), Point<1>(-4.2F));
  EXPECT_EQ(line_segment.b(), Point<1>(0.3F));
}

TEST(LineSegmentTest, Constructs2DLine1) {
  LineSegment<2> line_segment(Point<2>(-4.2F, 3.2F),
                              Point<2>(0.3F, 1.1F));

  EXPECT_EQ(line_segment.a(), Point<2>(-4.2F, 3.2F));
  EXPECT_EQ(line_segment.b(), Point<2>(0.3F, 1.1F));
}

TEST(LineSegmentTest, Constructs3DLine1) {
  LineSegment<3> line_segment(Point<3>(-4.2F, 3.2F, 4.4F),
                              Point<3>(0.3F, 1.1F, 0.0F));

  EXPECT_EQ(line_segment.a(), Point<3>(-4.2F, 3.2F, 4.4F));
  EXPECT_EQ(line_segment.b(), Point<3>(0.3F, 1.1F, 0.0F));
}
