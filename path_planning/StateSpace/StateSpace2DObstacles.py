import random
from enum import Enum
import numpy as np
import kdtree as KdTree
from StateSpace.States import Point2D


class MapState(Enum):
    FREE = 0
    OCCUPIED = 1
    UNKNOWN = 2

class StateSpace2DObstacles:
    """
    Discrete 2D plane with obstacles
    """
    def __init__(self, map = np.zeros([100, 100])):
        """
        Constructor with a map
        :param map: By default it will be an empty 100x100 grid if no map is provided
        """
        self.map = map
        self.kdtree = KdTree.create(dimensions=2)
        random.seed()

    @property
    def width(self):
        return self.map.shape[1]

    @property
    def height(self):
        return self.map.shape[0]

    def random_state(self):
  #      valid = False
 #       while not valid:
        rand_x = int(random.uniform(0, 1) * self.width)
        rand_y = int(random.uniform(0, 1) * self.height)
        state = Point2D(rand_x, rand_y)
#            if self.is_state_valid(state):
#                valid = True
        return state

    def intermediate_state(self, source, target, step_size):
        delta = target - source
        delta = delta / np.linalg.norm(delta)
        #np.true_divide(delta, np.linalg.norm(delta), delta, casting='unsafe')
        state = source.vec + delta * step_size
        state = state.astype(int)
        return Point2D(state[0], state[1])

    def distance(self, source, target):
        return np.linalg.norm(target - source)

    def is_state_valid(self, state):
        in_bounds = False
        if ((state.x >= 0) and (state.x <= self.width) and
                (state.y >= 0) and (state.y <= self.height)):
            in_bounds = True
        else:
            return False

        safe = False
        if self.map[state.x][state.y] == int(MapState.FREE.value):
            safe = True

        return (safe and in_bounds)

    def is_transition_valid(self, source, goal):
        """
        Checks for collisions when transitioning from source to goal
        in a straight line using Bressenham line rasterization
        https://en.wikipedia.org/wiki/Bresenham's_line_algorithm
        :param source: Source state (Point2D)
        :param goal: Goal state (Point2D)
        :return: True or False
        """
        if (not self.is_state_valid(source)) or (not self.is_state_valid(goal)):
            return False
        x0, y0 = int(source.x), int(source.y)
        x1, y1 = int(goal.x), int(goal.y)

        dx = abs(x0 - x1)
        dy = abs(y0 - y1)
        if dx != 0.0: # not a vertical line
            derr = abs(dy/dx)
            err  = derr - 0.5
            y = source.y
            for x in range(x0, x1):
                # check collision
                if self.map[x][y] != int(MapState.FREE.value):
                    return False
                err += derr
                if err >= 0.5:
                    y += 1
                    err -= 1.0
            # Yay no collision found!
            return True
        else:
            # is a vertical line, ezpz
            for y in range(y0, y1):
                if self.map[x0][y] != int(MapState.FREE.value):
                    return False
            return True

