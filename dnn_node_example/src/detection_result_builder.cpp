// Construct project detection messages from one asynchronous inference result.
#include "detection_result_builder.h"

#include <cmath>
#include <utility>

namespace nl::detection {

nl_detection_msgs::msg::DetectionResult BuildResult(
    const nl_image_msgs::msg::FrameMetadata& frame,
    const std::vector<ModelDetection>& detections,
    float image_scale) {
  nl_detection_msgs::msg::DetectionResult result;
  result.frame = frame;
  for (const auto& source : detections) {
    if (!std::isfinite(source.score) || source.score < 0 || source.score > 1)
      continue;
    const auto box =
        ToImageBox(source.box, image_scale, frame.width, frame.height);
    if (!box) continue;
    nl_detection_msgs::msg::Detection detection;
    detection.node_id = frame.node_id;
    detection.camera_id = frame.camera_id;
    detection.cls_id = source.cls_id;
    detection.score = source.score;
    detection.bbox.x = box->x;
    detection.bbox.y = box->y;
    detection.bbox.w = box->w;
    detection.bbox.h = box->h;
    result.detections.push_back(std::move(detection));
  }
  return result;
}

}  // namespace nl::detection
