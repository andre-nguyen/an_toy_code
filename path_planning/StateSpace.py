import abc
"""
Class representing the state space
"""

class StateSpace:
    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def randomState(self):
        return

    @abc.abstractmethod
    def intermediateState(self, source, target):
        return

    @abc.abstractmethod
    def distance(self, source, target):
        return

    @abc.abstractmethod
    def isStateValid(self, state):
        return

    @abc.abstractmethod
    def isTransitionValid(self, source, goal):
        return

class StateSpace2D:
    def __init__(self):
        self.x = 0

class StateSpace3D:
    def __init__(self):
        self.x = 0

StateSpace.register(StateSpace2D)
StateSpace.register(StateSpace3D)
