import numpy as np

np.random.seed(42)
points = np.random.rand(100, 2) * 100  

def dist(p1, p2):
    return np.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

def rec(xsorted, ysorted):
    n = len(xsorted)
    if n <= 3:
        min_dist = float('inf')
        closest_pair = (None, None)
        for i in range(n):
            for j in range(i + 1, n):
                d = dist(xsorted[i], xsorted[j])
                if d < min_dist:
                    min_dist = d
                    closest_pair = (xsorted[i], xsorted[j])
        return closest_pair[0], closest_pair[1], min_dist
    else:
        midpoint = xsorted[n // 2][0]
        xsorted_left = xsorted[:n // 2]
        xsorted_right = xsorted[n // 2:]
        
        ysorted_left = []
        ysorted_right = []
        for point in ysorted:
            if point[0] <= midpoint:
                ysorted_left.append(point)
            else:
                ysorted_right.append(point)
        
        (p1_left, p2_left, delta_left) = rec(xsorted_left, ysorted_left)
        (p1_right, p2_right, delta_right) = rec(xsorted_right, ysorted_right)
        (p1, p2, delta) = (p1_left, p2_left, delta_left) if delta_left < delta_right else (p1_right, p2_right, delta_right)
        
        in_band = [point for point in ysorted if midpoint - delta < point[0] < midpoint + delta]
        for i in range(len(in_band)):
            for j in range(i + 1, min(i + 7, len(in_band))):
                d = dist(in_band[i], in_band[j])
                if d < delta:
                    p1, p2, delta = in_band[i], in_band[j], d
        return p1, p2, delta

def closest(points):
    xsorted = sorted(points, key=lambda point: point[0])
    ysorted = sorted(points, key=lambda point: point[1])
    return rec(xsorted, ysorted)

p1, p2, min_distance = closest(points)

print("p1 : ",p1)
print("p2 : ", p2)
print("min_distance : ", min_distance)
