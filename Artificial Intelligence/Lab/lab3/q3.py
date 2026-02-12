class NeighborhoodEnvironment:
    def __init__(self):
        self.houses = ['Blue House', 'Green House', 'Red House', 'Yellow House', 'White House']

    def get_percept(self, location_index):
        if location_index < len(self.houses):
            return self.houses[location_index]
        return "End of Neighborhood"

class GoalBasedDrone:
    def __init__(self):
        self.goal = 'Red House' 

    def act(self, percept):
        if percept == self.goal:
            return "Land and Drop-off"
        else:
            return "Continue Search"

def run(drone, neighborhood):
    for i in range(5):
        current_house = neighborhood.get_percept(i)
        action = drone.act(current_house)
        print(f"Scanning Location {i+1}: {current_house}")
        if action == "Land and Drop-off":
            print(f" GOAL MATCHED! Action: {action}")
            print("\nMission Successful. Returning to Base.")
            break 
        else:
            print(f" Goal not met. Action: {action}")

env = NeighborhoodEnvironment()
agent = GoalBasedDrone()

run(agent, env)
