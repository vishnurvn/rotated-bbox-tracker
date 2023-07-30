#include "../include/tracker.hpp"
#include <cppunit/Test.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestCaller.h>


class TestTracker: public CppUnit::TestCase {
  private:
    Tracker *tracker;
  public:
    void setUp() {
      tracker = new Tracker(0.45);
    }

    void tearDown() {
      delete tracker;
    }

    void testFirstTrack() {
      std::vector<std::vector<std::vector<float>>> detections = {
        {
          {1, 2, 3}
        }
      };
      tracker->update_tracks(detections);
      CPPUNIT_ASSERT(tracker->get_latest_track_id() == 1);
    }
};

int main() {
  CppUnit::TestSuite suite;
  CppUnit::TestResult result;
  suite.addTest(new CppUnit::TestCaller<TestTracker> ("calculate-corner", &TestTracker::testFirstTrack));
  suite.run(&result);
  return 0;
}