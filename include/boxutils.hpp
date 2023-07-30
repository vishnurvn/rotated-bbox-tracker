#include <vector>
#include <cmath>

#define PI 3.14159265

std::vector<std::vector<float>>
get_rotated_corners(float x_center, float y_center, float width, float height, float angle) {
  std::vector<std::vector<float>> points;
  /*
  (x_min, y_max)    (x_max, y_max)
          +------------+
          +            +
          + (x_c, y_c) +
          +            +
          +------------+
  (x_min, y_min)    (x_max, y_min)
  */
  float x_min = -width / 2;
  float x_max = width / 2;
  float y_min = -height / 2;
  float y_max = +height / 2;
  angle = angle / 180 * PI;

  points.push_back(
      {x_min * cos(angle) - y_max * sin(angle) + x_center,
       x_min * sin(angle) + y_max * cos(angle) + y_center});

  points.push_back(
      {x_max * cos(angle) - y_max * sin(angle) + x_center,
       x_max * sin(angle) + y_max * cos(angle) + y_center});

  points.push_back(
      {x_max * cos(angle) - y_min * sin(angle) + x_center,
       x_max * sin(angle) + y_min * cos(angle) + y_center});

  points.push_back(
      {x_min * cos(angle) - y_min * sin(angle) + x_center,
       x_min * sin(angle) + y_min * cos(angle) + y_center});
  return points;
}

float calculate_iou(std::vector<std::vector<float>> box1, std::vector<std::vector<float>> box2){
  return 0;
}

float calculate_iou(std::vector<float> box1, std::vector<float> box2){
  // x, y, w, h
  float x1 = box1[0] - box1[2] / 2;
  float x2 = box1[0] + box1[2] / 2;

  float y1 = box1[1] - box1[3] / 2;
  float y2 = box1[1] + box1[3] / 2;

  float x3 = box2[0] - box2[2] / 2;
  float x4 = box2[0] + box2[2] / 2;

  float y3 = box2[1] - box2[3] / 2;
  float y4 = box2[1] + box2[3] / 2;

  float length = std::min(x2, x4) - std::max(x1, x3);
  float breadth = std::min(y2, y4) - std::max(y1, y3);

  float intersection = length * breadth;
  float union_ = box1[2] * box1[3] + box2[2] * box2[3] - intersection;
  return intersection / union_;
}