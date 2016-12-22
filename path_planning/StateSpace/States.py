from abc import ABCMeta
import numpy as np

"""
Helper geometry classes
"""
class State:
    __metaclass__ = ABCMeta


class Point2D:
    vec = np.zeros([1,2])

    def __init__(self, x, y):
        self.vec = np.array([x, y])

    @property
    def x(self):
        return self.vec[0]

    @x.setter
    def x(self, x):
        self.vec[0] = x

    @property
    def y(self):
        return self.vec[1]

    @y.setter
    def y(self, y):
        self.vec[1] = y

    def __add__(self, other):
        return self.vec + other.vec

    def __sub__(self, other):
        return self.vec - other.vec


class Point3D:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

