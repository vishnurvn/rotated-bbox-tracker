#include "../include/boxutils.hpp"
#include <cppunit/Test.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestCaller.h>
#include <vector>


class TestBoxUtilsCorners: public CppUnit::TestCase {
  public:
    void testRotate() {
      float x_center = 50;
      float y_center = 50;
      float height = 20;
      float width = 10;
      float angle = 90;
      std::vector<std::vector<float>> actual_corners = get_rotated_corners(x_center, y_center, width, height, angle);
      std::vector<std::vector<float>> expected_corners = {
        {40, 45}, {40, 55}, {60, 55}, {60, 45}
      };
      CPPUNIT_ASSERT(actual_corners == expected_corners);
    }
};


class TestBoxUtilsIoURect: public CppUnit::TestCase {
  public:
    void testSameBox() {
      std::vector<float> box1 = {50, 50, 20, 10};
      float actual_iou = calculate_iou(box1, box1);
      CPPUNIT_ASSERT(actual_iou == 1.0);
    }
};

int main() {
  CppUnit::TestSuite suite;
  CppUnit::TestResult result;
  suite.addTest(new CppUnit::TestCaller<TestBoxUtilsCorners> ("calculate-corner", &TestBoxUtilsCorners::testRotate));
  suite.addTest(new CppUnit::TestCaller<TestBoxUtilsIoURect> ("calculate-corner", &TestBoxUtilsIoURect::testSameBox));
  suite.run(&result);
  return 0;
}