def beam_search(graph, start, goal, k):
    queue = [([start], 0)]
    
    while queue:
        next_queue = []
        all_at_goal = True
        
        for path, cost in queue:
            node = path[-1]
            if node == goal:
                next_queue.append((path, cost))
                continue
                
            all_at_goal = False
            if node in graph:
                for neighbor, weight in graph[node].items():
                    next_queue.append((path + [neighbor], cost + weight))
                    
        if all_at_goal:
            break
            
        next_queue.sort(key=lambda x: x[1])
        queue = next_queue[:k]
        
    return queue[0] if queue else ([], float('inf'))

graph = {
    'S': {'A': 2, 'B': 5, 'C': 4},
    'A': {'D': 7, 'E': 3},
    'B': {'F': 6},
    'C': {'G': 2},
    'D': {'T': 4},
    'E': {'T': 6},
    'F': {'T': 5},
    'G': {'T': 3}
}

for k in [1, 2, 3]:
    path, cost = beam_search(graph, 'S', 'T', k)
    print(f"k={k}: Path {' -> '.join(path)} with total cost {cost}")
