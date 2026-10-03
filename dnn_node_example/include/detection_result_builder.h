// Bind detector rectangles to their originating camera frame.
#ifndef NL_DETECTION_RESULT_BUILDER_H_
#define NL_DETECTION_RESULT_BUILDER_H_

#include <vector>

#include "detection_geometry.h"
#include "nl_detection_msgs/msg/detection_result.hpp"
#include "nl_image_msgs/msg/frame_metadata.hpp"

namespace nl::detection {

/** 解析器输出的模型坐标检测记录。 */
struct ModelDetection {
  BoxXYXY box;
  int cls_id = 0;
  float score = 0;
};

/** 将单帧模型结果变换到原图，并继承完整的源帧标识。 */
[[nodiscard]] nl_detection_msgs::msg::DetectionResult BuildResult(
    const nl_image_msgs::msg::FrameMetadata& frame,
    const std::vector<ModelDetection>& detections,
    float image_scale);

}  // namespace nl::detection
#endif  // NL_DETECTION_RESULT_BUILDER_H_
