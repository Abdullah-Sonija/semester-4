airspace_network = {
    'Tehran': ['Baghdad', 'Istanbul'],
    'Baghdad': ['Cairo'],
    'Istanbul': ['Berlin'],
    'Cairo': ['Washington'],
    'Berlin': ['Washington'],
    'Washington': []
}

start_city = 'Tehran'
goal_city = 'Washington'

def drone(airspace,start,goal):
    print(f"starting Mission: {start} -> {goal}\n")
    queue = [(start,[start])]
    visited = set()

    while queue:
        current_city, current_path = queue.pop()
        print(f"Drone checking: {current_city}")
        if current_city == goal:
            print(f"Mission Success: {goal} reached.")
            return current_path
        
        if current_city not in visited:
            visited.add(current_city)

            for neighbor in airspace.get(current_city,[]):
                if neighbor not in visited:
                    new_path = list(current_path)
                    new_path.append(neighbor)
                    queue.append((neighbor,new_path))

    return f"Mission Failed: No possible route to {goal}."

route = drone(airspace_network,start_city,goal_city)

print(f"optimal flight path: {' -> '.join(route)}")
print(f"total stops taken: {len(route) - 2}") # (-2) to exclude the start and goal state counting
