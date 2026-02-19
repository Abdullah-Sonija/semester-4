import heapq

space_network = {
    'Earth': {'Moon_Base': 10, 'Orbital_Platform': 5},
    'Orbital_Platform': {'Moon_Base': 2, 'Mars': 60},
    'Moon_Base': {'Mars': 50},
    'Mars': {}
}

start = 'Earth'
destination = 'Mars'

def ucs(graph,start,goal):
    print(f"Initiating: {start} -> {goal}\n")
    frontier = [(0, start, [start])]
    visited = set()

    while frontier:
        current_cost, current_node, current_path = heapq.heappop(frontier)
        if current_node == goal:
            print(f"Succes: {goal} reached.")
            return current_path, current_cost
        if current_node in visited:
            continue
        print(f"tracking at: {current_node:<18} | fuel spent: {current_cost}")
        visited.add(current_node)
        if current_node in graph:
            for neighbor, fuel_cost in graph[current_node].items():
                new_cost = current_cost + fuel_cost
                new_path = list(current_path)
                new_path.append(neighbor)
                heapq.heappush(frontier, (new_cost, neighbor, new_path))

    return None, float("inf")

optimal_path, total_fuel = ucs(space_network,start,destination)

print(f"Total Fuel Cost: {total_fuel} units")
print(f"Optimal Path: {" -> ".join(optimal_path)}")
