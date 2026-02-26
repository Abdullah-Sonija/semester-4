def a_star_algorithm(graph_data, h_map, start, destination):
    open_list = [(start, [start], 0)]
    closed_list = {}

    while open_list:
        open_list.sort(key=lambda x: x[2] + h_map[x[0]])
        node, path, cost = open_list.pop(0)

        if node == destination:
            return path, cost

        if node in closed_list and closed_list[node] <= cost:
            continue
        closed_list[node] = cost

        for neighbor, weight in graph_data.get(node, {}).items():
            open_list.append((neighbor, path + [neighbor], cost + weight))
    return None

graph_connections = {
    'S': {'A': 1, 'G': 10},
    'A': {'B': 2, 'C': 1},
    'B': {'D': 5},
    'C': {'D': 3, 'G': 4},
    'D': {'G': 0}
}

node_heuristics = {'S': 5, 'A': 3, 'B': 4, 'C': 2, 'D': 6, 'G': 0}

final_path, total_cost = a_star_algorithm(graph_connections, node_heuristics, 'S', 'D')
print(f"Path: {final_path}, Total Cost: {total_cost}")
