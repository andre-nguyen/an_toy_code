from StateSpace.StateSpace2D import StateSpace2D
from StateSpace.States import Point2D
from Tree import Tree
import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
"""
Test out the rrt algorithm
"""

def treeTraversal(node, segments):
    n = node.state
    if node.parent == None:
        segments.append([(0.0, 0.0), (n.x, n.y)])
    else:
        p = node.parent.state
        segments.append([(p.x, p.y), (n.x, n.y)])
    for n in node.children:
        treeTraversal(n, segments)

def main():
    state_space = StateSpace2D(100.0, 100.0)
    tree = Tree(state_space)
    tree.stepSize = 1
    tree.goalMaxDist = 1
    tree.goalBias = 0.2
    tree.start_state = Point2D(0.0,0.0)
    tree.goalState = Point2D(40.0,40.0)
    tree.run()
    path = []
    tree.getPath(path, tree.last_node)
    nodes = tree.nodes
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

if __name__ == '__main__':
    main()