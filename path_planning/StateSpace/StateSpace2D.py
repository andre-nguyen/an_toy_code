import random
import numpy as np
from StateSpace import States



class StateSpace2D:
    """
    Empty continuous 2D plane
    """
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.width2 = width/2
        self.height2 = height/2
        random.seed()

    def random_state(self):
        """
        Generate a valid random state
        :return:
        """
        randx = random.uniform(-1,1) * self.width2
        randy = random.uniform(-1,1) * self.height2
        return States.Point2D(randx, randy)

    def intermediate_state(self, source, target, step_size):
        """
        Find an intermediate state a @step_size away from source to target
        :param source: Source state
        :param target: Target state
        :param step_size: Size of the step to take towards target
        :return: The intermediate state
        """
        delta = target - source
        delta /= np.linalg.norm(delta)
        state = source.vec + delta * step_size
        return States.Point2D(state[0], state[1])

    def distance(self, source, target):
        return np.linalg.norm(target - source)

    def is_state_valid(self, state):
        if ((state.x >= -self.width2) and (state.x <= self.width2) and
                (state.y >= -self.height2) and (state.y <= self.height2)):
            return True
        return False

    def is_transition_valid(self, source, goal):
        return True
