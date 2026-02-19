# ---------------------------------------------------------
bunker_network = {
    'Entrance': ['Hallway_A', 'Hallway_B'],
    'Hallway_A': ['Storage'],
    'Hallway_B': ['Target'],
    'Storage': ['Deep_Vault'],
    'Target': [],
    'Deep_Vault': []
}

start = 'Entrance'
target = 'Target'
max_safe_depth = 2

def bunker_dls(graph,start,goal,depth_limit):
    print(f"Starting raid at {start} with oxygen limit of {depth_limit} levels.\n")
    visited = []

    def dfs(node,depth):
        if depth > depth_limit:
            print(f"Mission aborted, not enough oxygen. Oxyen finished at level {depth}.\nBacktracking.")
            return None
        
        visited.append(node)
        print(f"Exploring: {node} | level: {depth}")

        if node == goal:
            return visited
        
        for neighbor in graph.get(node, []):
            if neighbor not in visited:
                path = dfs(neighbor, depth + 1)
                if path:
                    return path
        visited.pop()
        return None
    
    result_path = dfs(start, 0)
    if result_path:
        print(f"Mission Accomplished!")
        print(f"Path Taken: {" -> ".join(result_path)}")
    else:
        print(f"Mission Failed.")
    return result_path

bunker_dls(bunker_network, start, target, max_safe_depth)
