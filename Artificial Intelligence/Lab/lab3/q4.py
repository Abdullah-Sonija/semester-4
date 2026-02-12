class MarsRoverUtilityAgent:
    def __init__(self):
        pass

    def calculate_utility(self, rock):
        return (rock['value'] * 2) - rock['cost']

    def choose_best_rock(self, rocks):
        best_rock = None
        highest_utility = -float('inf')  
        for name, data in rocks.items():
            score = self.calculate_utility(data)
            print(f"Rock {name}: Value {data['value']}, Cost {data['cost']} -> Utility Score: {score}")
            if score > highest_utility:
                highest_utility = score
                best_rock = name

        return best_rock

available_rocks = {
    'A': {'value': 5, 'cost': 2},
    'B': {'value': 9, 'cost': 8},
    'C': {'value': 6, 'cost': 3}
}
rover = MarsRoverUtilityAgent()
best_choice = rover.choose_best_rock(available_rocks)

print(f"Best Rock Selected: Rock {best_choice}")
