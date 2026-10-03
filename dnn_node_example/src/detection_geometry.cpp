// Map model detection rectangles to the source image coordinate system.
#include "detection_geometry.h"

#include <algorithm>
#include <cmath>

namespace nl::detection {

std::optional<BoxXYWH> ToImageBox(BoxXYXY box,
                                  float scale,
                                  int image_width,
                                  int image_height) noexcept {
  if (image_width <= 0 || image_height <= 0 || !std::isfinite(scale) ||
      scale <= 0 || !std::isfinite(box.x1) || !std::isfinite(box.y1) ||
      !std::isfinite(box.x2) || !std::isfinite(box.y2)) {
    return std::nullopt;
  }
  const float x1 =
      std::clamp(box.x1 * scale, 0.0f, static_cast<float>(image_width));
  const float y1 =
      std::clamp(box.y1 * scale, 0.0f, static_cast<float>(image_height));
  const float x2 =
      std::clamp(box.x2 * scale, 0.0f, static_cast<float>(image_width));
  const float y2 =
      std::clamp(box.y2 * scale, 0.0f, static_cast<float>(image_height));
  if (x2 <= x1 || y2 <= y1) return std::nullopt;
  return BoxXYWH{(x1 + x2) / 2, (y1 + y2) / 2, x2 - x1, y2 - y1};
}

BoxXYXY ToXYXY(BoxXYWH box) noexcept {
  return {box.x - box.w / 2,
          box.y - box.h / 2,
          box.x + box.w / 2,
          box.y + box.h / 2};
}

CBox ToCBox(BoxXYWH box, int image_width, int image_height) noexcept {
  return {
      box.x - image_width / 2.0f, image_height / 2.0f - box.y, box.w, box.h};
}

}  // namespace nl::detection
