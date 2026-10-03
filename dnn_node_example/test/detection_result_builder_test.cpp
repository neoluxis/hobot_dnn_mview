// Verify asynchronous camera results keep the metadata of their own frames.
#include "detection_result_builder.h"

#include "gtest/gtest.h"

namespace nl::detection {
namespace {

TEST(ResultTest, KeepsFrameIdentityWhenResultsCompleteOutOfOrder) {
  nl_image_msgs::msg::FrameMetadata first;
  first.node_id = "node1";
  first.camera_id = "vi0";
  first.frame_index = 7;
  first.header.stamp.sec = 100;
  first.width = 640;
  first.height = 480;
  auto second = first;
  second.camera_id = "ir0";
  second.frame_index = 7;
  // 两路相机即使时间戳与序号相同，也必须保留各自的相机 ID。
  const std::vector<ModelDetection> model{{{10, 20, 30, 40}, 5, 0.9f}};
  const auto second_result = BuildResult(second, model, 2);
  const auto first_result = BuildResult(first, model, 1);
  ASSERT_EQ(second_result.detections.size(), 1);
  EXPECT_EQ(second_result.frame.camera_id, "ir0");
  EXPECT_EQ(second_result.frame.frame_index, 7u);
  EXPECT_EQ(second_result.detections[0].camera_id, "ir0");
  EXPECT_EQ(second_result.detections[0].cls_id, 5);
  EXPECT_FLOAT_EQ(second_result.detections[0].bbox.x, 40);
  EXPECT_EQ(first_result.frame.camera_id, "vi0");
  EXPECT_EQ(first_result.frame.frame_index, 7u);
  EXPECT_FLOAT_EQ(first_result.detections[0].bbox.x, 20);
}

TEST(ResultTest, EmitsSourceIdentityForEmptyDetection) {
  nl_image_msgs::msg::FrameMetadata frame;
  frame.node_id = "node1";
  frame.camera_id = "vi1";
  frame.frame_index = 42;
  frame.width = 640;
  frame.height = 480;
  const auto result = BuildResult(frame, {}, 1);
  EXPECT_EQ(result.frame.frame_index, 42u);
  EXPECT_TRUE(result.detections.empty());
}

}  // namespace
}  // namespace nl::detection
