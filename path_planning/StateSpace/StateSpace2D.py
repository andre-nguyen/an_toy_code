import random
import numpy as np
from StateSpace import States



class StateSpace2D:
    """
    Empty 2D plane
    """
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.width2 = width/2
        self.height2 = height/2
        random.seed()

    def randomState(self):
        randx = random.uniform(-1,1) * self.width2
        randy = random.uniform(-1,1) * self.height2
        return States.Point2D(randx, randy)

    def intermediateState(self, source, target, step_size):
        delta = target - source
        delta /= np.linalg.norm(delta)
        state = source.vec + delta * step_size
        return States.Point2D(state[0], state[1])

    def distance(self, source, target):
        return np.linalg.norm(target - source)

    def isStateValid(self, state):
        if ((state.x >= -self.width2) and (state.x <= self.width2) and
                (state.y >= -self.height2) and (state.y <= self.height2)):
            return True
        return False

    def isTransitionValid(self, source, goal):
        return True
