import numpy as np

from utils import (
    calculate_intersect_point, calculate_slope, calculate_intercept,
)


def test_calculate_intersect_point():
    l1 = (np.array([[0, 0]]), np.array([[1, 1]]))
    l2 = (np.array([[0, 1]]), np.array([[1, 0]]))
    intersect_points = calculate_intersect_point(l1, l2)
    target = np.array([[0.5], [0.5]])
    assert np.array_equal(intersect_points, target)


def test_calculate_slope():
    p1 = np.array([[0, 0], [0, 0], [1, 0]])
    p2 = np.array([[1, 1], [2, 2], [0, 1]])
    slope = calculate_slope(p1, p2)
    target = np.array([[1.0], [1.0], [-1.0]])
    assert np.array_equal(slope, target)


def test_calculate_intercept():
    point = np.array([[0.0, 0.0], [1.0, 1.0], [2.0, 2.0]])
    slope = np.array([[0.0], [0.0], [0.0]])
    intercepts = calculate_intercept(point, slope)
    target = np.array([[0.0], [1.0], [2.0]])
    assert np.array_equal(intercepts, target)
