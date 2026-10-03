// Verify model boxes map to source images and center-offset coordinates.
#include "detection_geometry.h"

#include "gtest/gtest.h"

namespace nl::detection {
namespace {

TEST(GeometryTest, RestoresScaledBoxAndClipsToImage) {
  auto box = ToImageBox({-5, 10, 320, 300}, 2.0f, 640, 480);
  ASSERT_TRUE(box);
  EXPECT_FLOAT_EQ(box->x, 320);
  EXPECT_FLOAT_EQ(box->y, 250);
  EXPECT_FLOAT_EQ(box->w, 640);
  EXPECT_FLOAT_EQ(box->h, 460);
  const auto corners = ToXYXY(*box);
  EXPECT_FLOAT_EQ(corners.x1, 0);
  EXPECT_FLOAT_EQ(corners.y2, 480);
}

TEST(GeometryTest, RejectsInvalidBoxesAndUsesUpwardCenterOffset) {
  EXPECT_FALSE(ToImageBox({10, 10, 10, 20}, 1, 640, 480));
  EXPECT_FALSE(ToImageBox({10, 10, 20, 20}, 0, 640, 480));
  const auto offset = ToCBox({420, 140, 80, 40}, 640, 480);
  EXPECT_FLOAT_EQ(offset.x, 100);
  EXPECT_FLOAT_EQ(offset.y, 100);
}

}  // namespace
}  // namespace nl::detection
