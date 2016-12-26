from StateSpace.StateSpace2D import StateSpace2D
from StateSpace.StateSpace2DObstacles import StateSpace2DObstacles, MapState
from StateSpace.States import Point2D
from Tree import Tree
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from matplotlib.collections import LineCollection
from scipy import misc as m
"""
Test out the rrt algorithm
"""

def treeTraversal(node, segments):
    n = node.state
    if node.parent is None:
        segments.append([(0.0, 0.0), (n.x, n.y)])
    else:
        p = node.parent.state
        segments.append([(p.x, p.y), (n.x, n.y)])
    for n in node.children:
        treeTraversal(n, segments)

def main():
    state_space = StateSpace2D(100.0, 100.0)
    tree = Tree(state_space)
    tree.step_size = 1
    tree.goal_max_dist = 1
    tree.goal_bias = 0.2
    tree.start_state = Point2D(0.0,0.0)
    tree.goal_state = Point2D(40.0, 40.0)
    tree.run()
    path = []
    tree.getPath(path, tree.last_node)
    segments = []
    treeTraversal(tree.nodes[0], segments)

    lc = LineCollection(segments, linestyles='solid')
    ax = plt.axes()
    ax.set_xlim(-50, 50)
    ax.set_ylim(-50, 50)
    ax.add_collection(lc)
    ax.set_title('Path')
    plt.grid(True)
    plt.show()
    plt.waitforbuttonpress()

def main_obstacles():
    map = m.imread('Untitled.bmp', flatten=True)
    # Binarize the map and the invert it
    #map = np.ones([100,100])
    map[map>0] = 2
    map[map==0] = MapState.OCCUPIED.value
    map[map==2] = MapState.FREE.value
    state_space = StateSpace2DObstacles(map)
    tree = Tree(state_space)
    tree.step_size = 2
    tree.goal_max_dist = 1
    tree.goal_bias = 0.2
    tree.start_state = Point2D(0, 0)
    tree.goal_state = Point2D(50, 50)
    result = tree.run()
    print('Found path to goal.' if result else 'Unable to find path to goal')
    path = []
    tree.getPath(path, tree.last_node)
    segments = []
    treeTraversal(tree.nodes[0], segments)

    lc = LineCollection(segments, linestyles='solid')
    ax = plt.axes()
    ax.set_xlim(0, 100)
    ax.set_ylim(0, 100)
    ax.add_collection(lc)
    ax.set_title('Path')
    plt.grid(True)
    #plt.imshow(map, cmap="gray")
    plt.show()
    plt.waitforbuttonpress()

if __name__ == '__main__':
    main_obstacles()