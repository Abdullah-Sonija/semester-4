class Green_house_environment:
    def __init__(self):
        self.beds = ['Moist', 'Dry', 'Moist', 'Moist', 'Dry', 'Moist', 'Dry', 'Moist', 'Moist']

    def get_percept(self, bed_index):
        return self.beds[bed_index]
    
    def water_bed(self, bed_index):
        self.beds[bed_index] = 'Moist'

    def display_status(self):
        print(f"\nFinal Bed Status: {self.beds}")

    
class Simple_reflex_agent:
    def __init__(self):
        pass

    def act(self, percept):
        if percept == 'Dry':
            return "Water the bed"
        else:
            return "Bed is already moist"
        
def run(agent, environment):
    for i in range(9):
        current_bed_num = i + 1
        percept = environment.get_percept(i)    
        action = agent.act(percept)
        print(f"Bed {current_bed_num}: Detected '{percept}' -> Action: {action}")
        if action == "Water the bed":
            environment.water_bed(i)
            print(f"   >> [Actuator] Bed {current_bed_num} has been watered.")
    environment.display_status()

env = Green_house_environment()
bot = Simple_reflex_agent()

run(bot, env)
