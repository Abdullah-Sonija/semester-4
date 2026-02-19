stadium_grid = {
    'Main_Box': ['Zone_A', 'Zone_B'],
    'Zone_A': ['Switch_1', 'Switch_2'],
    'Zone_B': ['Breaker_101'],
    'Switch_1': [],
    'Switch_2': [],
    'Breaker_101': []
}

start = 'Main_Box'
target = 'Breaker_101'
max_depth = 2

def dls_grid_search(node, goal, current_depth, limit, path, graph):
    
    path.append(node)
    if node == goal:
        return True
        
    if current_depth >= limit:
        return False
        
    for neighbor in graph.get(node, []):
        if neighbor not in path:
            if dls_grid_search(neighbor, goal, current_depth + 1, limit, path, graph):
                return True
                
    # Backtrack
    path.pop()
    return False

def ids_cyber_defense(graph, start, goal, max_depth):
    
    for depth_limit in range(max_depth + 1):
        print(f"Checking Depth {depth_limit}")
        path_taken = []
        
        if dls_grid_search(start, goal, 0, depth_limit, path_taken, graph):
            print(f"LIGHTS ON! '{goal}' isolated and bypassed at Depth {depth_limit}")
            print(f"Path: {' -> '.join(path_taken)}")
            return True
            
        print("-> Fault not found at this depth.")
        
    print("Fault not found within grid limits.")
    return False

ids_cyber_defense(stadium_grid, start, target, max_depth)
