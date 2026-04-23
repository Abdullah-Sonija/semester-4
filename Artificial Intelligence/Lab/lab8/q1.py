import math

class Node:
    def __init__(self, name, value=None):
        self.name = name
        self.value = value
        self.children = []
        self.minmax_value = None

def minimax(node, depth, maximizing_player):
    if depth == 0 or not node.children:
        return node.value

    if maximizing_player:
        max_eval = -math.inf
        for child in node.children:
            eval = minimax(child, depth - 1, False)
            max_eval = max(max_eval, eval)
        node.minmax_value = max_eval
        return max_eval
    else:
        min_eval = math.inf
        for child in node.children:
            eval = minimax(child, depth - 1, True)
            min_eval = min(min_eval, eval)
        node.minmax_value = min_eval
        return min_eval

def alpha_beta(node, depth, alpha, beta, maximizing_player, pruned_nodes):
    if depth == 0 or not node.children:
        return node.value

    if maximizing_player:
        max_eval = -math.inf
        for child in node.children:
            eval = alpha_beta(child, depth - 1, alpha, beta, False, pruned_nodes)
            max_eval = max(max_eval, eval)
            alpha = max(alpha, eval)
            if beta <= alpha:
                pruned_nodes.append(child.name)
                # Prune remaining children
                break
        node.minmax_value = max_eval
        return max_eval
    else:
        min_eval = math.inf
        for child in node.children:
            eval = alpha_beta(child, depth - 1, alpha, beta, True, pruned_nodes)
            min_eval = min(min_eval, eval)
            beta = min(beta, eval)
            if beta <= alpha:
                pruned_nodes.append(child.name)
                # Prune remaining children
                break
        node.minmax_value = min_eval
        return min_eval

def build_figure_1_tree():
    """Builds the tree specified in Figure 1 of the lab tasks."""
    root = Node('A') # MIN
    b = Node('B'); c = Node('C') # MAX
    root.children = [b, c]
    d = Node('D'); e = Node('E') # MIN
    b.children = [d, e]
    f = Node('F'); g = Node('G'); h = Node('H') # MIN
    c.children = [f, g, h]
    d.children = [Node('I', 5), Node('J', 7), Node('K', 1)]
    e.children = [Node('L', 9), Node('M', 2)]
    f.children = [Node('N', 5), Node('O', 10)]
    g.children = [Node('P', 12), Node('Q', 6)]
    h.children = [Node('R', 20)]
    
    return root

if __name__ == "__main__":
    tree_minimax = build_figure_1_tree()
    result_minimax = minimax(tree_minimax, 3, False)
    print("Standard Minimax Result:")
    print(f"Optimal Value at Root (A): {result_minimax}")
    tree_ab = build_figure_1_tree()
    pruned = []
    result_ab = alpha_beta(tree_ab, 3, -math.inf, math.inf, False, pruned)
    print("Alpha-Beta Pruning Result:")
    print(f"Optimal Value at Root (A): {result_ab}")
    print(f"Nodes where pruning occurred (skipped remaining siblings): {pruned}")