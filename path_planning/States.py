from abc import ABCMeta

"""
Helper geometry classes
"""
class State:
    __metaclass__ = ABCMeta


class Point2D:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Point3D:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

