import random
import numpy as np
import kdtree as KdTree
from StateSpace.States import Point2D


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
        return map.shape[1]

    @property
    def height(self):
        return map.shape[0]

    def random_state(self):
        valid = False
        while not valid:
            rand_x = random.uniform(-1, 1) * self.width / 2
            rand_y = random.uniform(-1, 1) * self.height / 2
            state = Point2D(rand_x, rand_y)
            if self.is_state_valid(state):
                valid = True
        return state

    def intermediate_state(self, source, target, step_size):
        return

    def distance(self, source, target):
        return

    def is_state_valid(self, state):
        return

    def is_transition_valid(self, source, goal):
        return