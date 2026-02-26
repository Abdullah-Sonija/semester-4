def greedy_search(adj_list, h_values, start_node, goal_node):
    tree = [(start_node, [start_node])]
    visited_nodes = set()

    while tree:
        tree.sort(key=lambda x: h_values[x[0]])
        current_node, current_path = tree.pop(0)

        if current_node == goal_node:
            return current_path

        if current_node not in visited_nodes:
            visited_nodes.add(current_node)
            for child in adj_list.get(current_node, []):
                if child not in visited_nodes:
                    tree.append((child, current_path + [child]))
    return None

tree_structure = {
    'S': ['A', 'B'],
    'A': ['C', 'D'],
    'B': ['E', 'F'],
    'E': ['H'],
    'F': ['I', 'G']
}

heuristics_table = {
    'A': 12, 'B': 4, 'C': 7, 'D': 3, 'E': 8, 
    'F': 2, 'H': 4, 'I': 9, 'S': 13, 'G': 0
}

result_path = greedy_search(tree_structure, heuristics_table, 'S', 'H')
print(f"Path: {result_path}")
