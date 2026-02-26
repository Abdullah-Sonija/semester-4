h_map = {
    (6, 0): 17,  # Start A 
    (0, 11): 0,  # Goal B
    
    # Row 0
    (0, 1): 10, (0, 2): 9, (0, 3): 8, (0, 4): 7, (0, 5): 6,
    (0, 6): 5, (0, 7): 4, (0, 8): 3, (0, 9): 2, (0, 10): 1,
    
    # Row 1
    (1, 1): 11, (1, 11): 1,
    
    # Row 2
    (2, 1): 12, (2, 3): 10, (2, 4): 9, (2, 5): 8, (2, 6): 7,
    (2, 7): 6, (2, 8): 5, (2, 9): 4, (2, 11): 2,
    
    # Row 3
    (3, 1): 13, (3, 3): 11, (3, 9): 5, (3, 11): 3,
    
    # Row 4
    (4, 1): 14, (4, 2): 13, (4, 3): 12, (4, 5): 10, (4, 6): 9,
    (4, 7): 8, (4, 8): 7, (4, 9): 6, (4, 11): 4,
    
    # Row 5
    (5, 3): 13, (5, 5): 11, (5, 11): 5,
    
    # Row 6
    (6, 1): 16, (6, 2): 15, (6, 3): 14, (6, 5): 12, (6, 6): 11,
    (6, 7): 10, (6, 8): 9, (6, 9): 8, (6, 10): 7, (6, 11): 6
}

def solve_maze(start, goal, heuristics, is_astar=False):
    solution = [(start, [start], 0)]
    visited = set()

    while solution:
        if is_astar:
            solution.sort(key=lambda x: x[2] + heuristics[x[0]])
        else:
            solution.sort(key=lambda x: heuristics[x[0]])
            
        current, path, g_cost = solution.pop(0)

        if current == goal:
            return path

        if current not in visited:
            visited.add(current)
            r, c = current
            
            for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                neighbor = (r + dr, c + dc)
                
                if neighbor in heuristics and neighbor not in visited:
                    solution.append((neighbor, path + [neighbor], g_cost + 1))
                    
    return None

start_node = (6, 0)
goal_node = (0, 11)

greedy_path = solve_maze(start_node, goal_node, h_map, is_astar=False)
astar_path = solve_maze(start_node, goal_node, h_map, is_astar=True)

print(f"Greedy Path ({len(greedy_path)} steps): {greedy_path}\n")
print(f"A* Path ({len(astar_path)} steps): {astar_path}")
