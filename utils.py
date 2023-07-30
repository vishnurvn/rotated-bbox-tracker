from typing import Tuple

import numpy as np


def calculate_slope(p1_array: np.ndarray, p2_array: np.ndarray):
    assert p2_array.ndim == 2 and p1_array.ndim == 2
    negate = p2_array - p1_array
    slope = negate[:, 1:2] / negate[:, 0:1]
    return slope


def calculate_intercept(p_array: np.ndarray, slope: np.ndarray):
    assert p_array.ndim == 2 and slope.ndim == 2
    intercept = p_array[:, 1:2] - p_array[:, 0:1] * slope
    return intercept


def calculate_intersect_point(
        l1_array: Tuple[np.ndarray, np.ndarray],
        l2_array: Tuple[np.ndarray, np.ndarray]
):
    m1 = calculate_slope(*l1_array)
    m2 = calculate_slope(*l2_array)
    c1 = calculate_intercept(l1_array[0], m1)
    c2 = calculate_intercept(l2_array[0], m2)
    x = (c2 - c1) / (m1 - m2)
    y = (m1 * c2 - m2 * c1) / (m1 - m2)
    return np.concatenate([x, y])
