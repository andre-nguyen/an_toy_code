from StateSpace.StateSpace2D import StateSpace2D
from StateSpace.States import Point2D
from Tree import Tree
import matplotlib.pyplot as plt
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
    map = m.imread('Untitled.bmp')
    # Binarize the map and the invert it
    map[map>0] = 2
    map[map==0] = 1
    map[map==2] = 0


if __name__ == '__main__':
    main_obstacles()