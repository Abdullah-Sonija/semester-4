import math

def alpha_beta_defense(tree):
    print(f"Original Tree (Unsorted): {tree}")
    sorted_tree = sorted(tree, key=lambda branch: min(branch), reverse=True)
    print(f"Dynamically Sorted Tree   : {sorted_tree}\n")
    pruned_count = [0] # List used to pass by reference and count pruned leaves

    def minimax(node, depth, alpha, beta, is_max):
        if isinstance(node, int):
            return node

        if is_max:
            max_eval = -math.inf
            for child in node:
                eval = minimax(child, depth - 1, alpha, beta, False)
                max_eval = max(max_eval, eval)
                alpha = max(alpha, eval)
                if beta <= alpha:
                    # Cutoff occurred
                    break
            return max_eval
        else:
            min_eval = math.inf
            for i, child in enumerate(node):
                eval = minimax(child, depth - 1, alpha, beta, True)
                min_eval = min(min_eval, eval)
                beta = min(beta, eval)
                if beta <= alpha:
                    # Cutoff occurred: Prune remaining siblings in this sublist
                    pruned_count[0] += len(node) - 1 - i
                    print(f"-> Pruning occurred in sublist {node}! Skipping remaining elements.")
                    break
            return min_eval

    # Tree depth is 2 (Root -> Sublists -> Leaves). Root is MAX.
    optimal_score = minimax(sorted_tree, 2, -math.inf, math.inf, True)
    print(f"\nTotal leaf nodes strictly pruned: {pruned_count[0]}")
    return optimal_score

if __name__ == "__main__":
    # [Cyber Attack, Signal Jamming, Market Crash]
    game_tree = [[10, 5, 2], [8, 4, 3], [20, 15, 9]]
    result = alpha_beta_defense(game_tree)
    print(f"Optimal Defense Score for Financial AI: {result}")