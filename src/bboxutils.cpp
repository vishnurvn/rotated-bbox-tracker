#include <vector>
#include <opencv2/imgproc.hpp>

#define PI 3.14159265


std::vector<cv::Point> 
get_rotated_corners(float x_center, float y_center, float width, float height, float angle) {
    std::vector<cv::Point> points;
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
        cv::Point(
            x_min * cos(angle) - y_max * sin(angle) + x_center,
            x_min * sin(angle) + y_max * cos(angle) + y_center
        )
    );

    points.push_back(
        cv::Point(
            x_max * cos(angle) - y_max * sin(angle) + x_center,
            x_max * sin(angle) + y_max * cos(angle) + y_center
        )
    );

    points.push_back(
        cv::Point(
            x_max * cos(angle) - y_min * sin(angle) + x_center,
            x_max * sin(angle) + y_min * cos(angle) + y_center
        )
    );

    points.push_back(
        cv::Point(
            x_min * cos(angle) - y_min * sin(angle) + x_center,
            x_min * sin(angle) + y_min * cos(angle) + y_center
        )
    );
    return points;
}