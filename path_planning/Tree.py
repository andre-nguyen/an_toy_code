import collections
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
        if parent != None:
            parent.children.append(self)

    def depth(self):
        """
        Counts the number of ancestors
        :return: Number of ancestors
        """
        n = 0;
        p = self.parent
        while p is not None:
            n += 1
            p = p.parent
        return n

    def addChild(self, node):
        self.children.append(node)

class Tree:
    def __init__(self, state_space):
        self.step_size = 0.1
        self.max_step_size = 5.0
        self.max_iterations = 1000
        self.goal_bias = 0
        self.waypoint_bias = 0
        self.goal_max_dist = 0.1
        self.state_space = state_space
        self.nodes = []
        self.waypoints = []
        self.goal_state  = None
        random.seed()

    @property
    def start_state(self):
        return self._start_state

    @start_state.setter
    def start_state(self, start_state):
        self.reset(True)
        n = Node(None, start_state)
        self.setRoot(n)

    def setRoot(self, root):
        self.nodes.append(root)
        self.startState = root.state

    @property
    def last_node(self):
        return self.nodes[len(self.nodes)-1]

    def run(self):
        """
        Execute RRT algorithm
        :return: True if a path was found
        """
        for i in range(0, self.max_iterations):
            newNode = self.grow()
            if (newNode is not None) and (self.state_space.distance(newNode.state, self.goal_state) < self.goal_max_dist):
                return True
        return False

    def grow(self):
        """
        Pick a random state and attempt to extend the tree towards it
        :return:
        """
        r = random.random()
        if r < self.goal_bias:
            return self.extend(self.goal_state)
        elif r < (self.waypoint_bias + self.goal_bias) and (len(self.waypoints)):
            state = random.sample(self.waypoints, 1)
            return self.extend(state)
        else:
            return self.extend(self.state_space.random_state())

    def reset(self, eraseRoot = False):
        """
        Remove all tree nodes
        :param eraseRoot: Also erase the root
        """
        if len(self.nodes) > 0:
            root = self.nodes[0]
            del self.nodes[:]
            if eraseRoot:
                del root
            else:
                self.nodes.append(root)

    def nearest(self, state):
        """
        Find the node in the tree closest to the given @state
        :param state:
        :return:
        """
        bestDistance = -1.0
        best = None

        for n in self.nodes:
            distance = self.state_space.distance(n.state, state)
            if (bestDistance < 0) or (distance < bestDistance):
                bestDistance = distance
                best = n

        return best, bestDistance

    def extend(self, target, source = None):
        """
        Grow the tree in the direction of the @target
        :param target: Where you want to go
        :param source: From where you are starting
        :return: the new node, None if we couldn't extend
        """
        if source == None:
            source, distance = self.nearest(target)
            if source == None:
                return None

        intermediateState = self.state_space.intermediate_state(source.state, target,
                                                                self.step_size)
        if not self.state_space.is_transition_valid(source.state, intermediateState):
            return None

        n = Node(source, intermediateState)
        self.nodes.append(n)
        return n


    def traversePath(self, callback, destination, reverse = False):
        node = destination
        if reverse:
            while node != None:
                callback(node.state)
                node = node.parent
        else:
            ordered_nodes = []
            while node != None:
                ordered_nodes.insert(0, node)
                node = node.parent
            for n in ordered_nodes:
                callback(n.state)

    def getPath(self, list, destination, reverse = False):
        func = lambda node : list.append(node)
        self.traversePath(func, destination, reverse)





