#include <vector>
#include <map>
#include <set>
#include "boxutils.hpp"


class Tracker {
  private:
    float iou_threshold;
    int latest_track_id = 0;
    std::set<int> track_ids;
    std::set<int>::iterator it;
    std::unordered_map<int, std::vector<std::vector<float>>> tracks;

  public:
    Tracker(float iou_thresh) {
      iou_threshold = iou_thresh;
    }

    int get_latest_track_id () {
      return latest_track_id;
    }

    void update_tracks(std::vector<std::vector<std::vector<float>>> detections) {
      if (tracks.empty()) {
        for (std::vector<std::vector<float>> det: detections) {
          tracks.insert({latest_track_id, det});
          track_ids.insert(latest_track_id);
          latest_track_id++;
        }
      } else {
        for (it = track_ids.begin(); it != track_ids.end(); it++) {
          std::vector<std::vector<float>> prev_detection = tracks.at(*it);

          int max = 0;
          std::vector<std::vector<float>> track_detection;
          for (std::vector<std::vector<float>> det: detections) {
            int iou_score = calculate_iou(prev_detection, det);
            if (iou_score > max) {
              track_detection = det;
            } 
          }
          if (max > iou_threshold) {
            tracks[*it] = track_detection;
          } else {
            track_ids.erase(*it);
          }
        }
      }
    }
};