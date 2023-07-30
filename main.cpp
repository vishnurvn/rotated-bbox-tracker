#include <fstream>
#include <json/json.h>
#include <iostream>
#include <cassert>
#include <map>
#include <vector>
#include <chrono>
#include <cmath>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include "include/boxutils.hpp"


int main() {
    std::map<std::string, std::vector<std::vector<float>>> data;
    Json::Value json_data;

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    std::fstream data_file("/Users/vishnu/Documents/datasets/FRIDA/Annotations/Segment_1/Camera_1/data2.json");
    assert(data_file);
    data_file >> json_data;

    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    for (int index = 0; index < json_data.size(); index++) {
        std::vector<float> bbox;
        std::string image_id = json_data[index]["image_id"].asString();

        for (unsigned int bbox_index = 0; bbox_index < json_data[index]["bbox"].size(); bbox_index++) {
            bbox.push_back(json_data[index]["bbox"].get(bbox_index, 0).asFloat());
        }

        data[image_id].push_back(bbox);
    }
    std::chrono::steady_clock::time_point t3 = std::chrono::steady_clock::now();

    std::cout << "JSON Time: " << std::chrono::duration_cast<std::chrono::milliseconds> (t2 - t1).count() << "[ms]\n";
    std::cout << "Map Time: " << std::chrono::duration_cast<std::chrono::milliseconds> (t3 - t2).count() << "[ms]\n";

    static int fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
    cv::VideoWriter writer = cv::VideoWriter("video.mp4", fourcc, 12.0, cv::Size(2048, 2048));

    int frame_count = 0;
    for (std::pair<std::string, std::vector<std::vector<float>> > image_bbox: data) {
        cv::Mat image = cv::imread("Frames/Segment_1/Camera_1/" + image_bbox.first + ".jpg");
        std::vector<std::vector<cv::Point>> contours;
        for (std::vector<float> bbox: image_bbox.second) {
            float x_center = bbox[0];
            float y_center = bbox[1];
            float w = bbox[2];
            float h = bbox[3];
            float a = bbox[4];

            std::vector<cv::Point> contour = get_rotated_corners(x_center, y_center, w, h, a);
            contours.push_back(contour);
        }
        // std::cout << contours.size() << "\n";
        cv::drawContours(image, contours, -1, cv::Scalar(0, 255, 0), 5);
        writer.write(image);
        frame_count++;

        if (frame_count == 100) {
            break;
        }
    }
    return 0;
}