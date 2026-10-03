// Image-space bounding box transformations for detector outputs.
#ifndef NL_DETECTION_GEOMETRY_H_
#define NL_DETECTION_GEOMETRY_H_

#include <optional>

namespace nl::detection {

/** 图像左上和右下角坐标，右下角为开区间边界。 */
struct BoxXYXY {
  float x1 = 0;
  float y1 = 0;
  float x2 = 0;
  float y2 = 0;
};

/** 图像坐标系中的中心点和尺寸，y 向下为正。 */
struct BoxXYWH {
  float x = 0;
  float y = 0;
  float w = 0;
  float h = 0;
};

/** 相对图像中心的脱靶量，y 向上为正。 */
struct CBox {
  float x = 0;
  float y = 0;
  float w = 0;
  float h = 0;
};

/** 将模型坐标映射到原图并裁剪，退化框返回空值。 */
[[nodiscard]] std::optional<BoxXYWH> ToImageBox(BoxXYXY model_box,
                                                float scale,
                                                int image_width,
                                                int image_height) noexcept;

/** 将中心点框转为左上和右下角坐标。 */
[[nodiscard]] BoxXYXY ToXYXY(BoxXYWH box) noexcept;

/** 将图像中心点框转为向上为正的脱靶量。 */
[[nodiscard]] CBox ToCBox(BoxXYWH box,
                          int image_width,
                          int image_height) noexcept;

}  // namespace nl::detection
#endif  // NL_DETECTION_GEOMETRY_H_
