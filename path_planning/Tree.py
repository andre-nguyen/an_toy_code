import random
"""
Tree class and what is needed to get it working
"""

class Node:
    """
    State of class Point2D or Point3D
    Parent of class Node
    """
    def __init__(self, parent, state):
        self.parent = parent
        self.state = state
        self.children = []

    def depth(self):
        n = 0;
        p = self.parent
        while p is not None:
            n += 1
            p = p.parent
        return n

    def addChild(self, node):
        self.children.append(node)

class Tree:
    def __init__(self, stateSpace):
        self.stepSize = 0.1
        self.maxStepSize = 5.0
        self.maxIterations = 1000
        self.goalBias = 0
        self.waypointBias = 0
        self.goalMaxDist = 0.1
        self.stateSpace = stateSpace
        self.nodes = []
        self.waypoints = []
        self.startState = None
        self.goalState  = None
        random.seed()


    def setRoot(self, root):
        self.nodes.append(root)

    def run(self):
        for i in range(0,self.maxIterations):
            newNode = self.grow()
            if (newNode is not None) and (self.stateSpace.distance(newNode.state, self.goalState)):
                return True
        return False

    def grow(self):
        r = random.random()
        if r < self.goalBias:
            return self.extend(self.goalState)
        elif r < (self.waypointBias + self.goalBias) and (len(self.waypoints)):
            state = random.sample(self.waypoints, 1)
            return self.extend(state)
        else:
            return self.extend(self.stateSpace.randomState())
        return

    def reset(self, eraseRoot = False):
        if len(self.nodes) > 0:
            root = self.nodes.index(0)
            del self.nodes[:]
            if eraseRoot:
                del root
            else:
                self.nodes.append(root)
        return

    def nearest(self):
        return

    def extend(self):
        return

    def getPath(self):
        return


