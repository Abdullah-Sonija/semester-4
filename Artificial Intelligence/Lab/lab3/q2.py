class SecureFacilityEnvironment:
    def __init__(self):
        self.rooms = {
            'A': {'status': 'Open', 'item': None},
            'B': {'status': 'Open', 'item': 'Keycard'},
            'C': {'status': 'Open', 'item': None},
            'D': {'status': 'Locked', 'item': 'Vault Content'}
        }

    def get_percept(self, room_name):
        return self.rooms[room_name]

class SecurityRobotAgent:
    def __init__(self):
        self.has_keycard = False  

    def update_model(self, percept):
        if percept['item'] == 'Keycard':
            self.has_keycard = True
            print(" Keycard acquired!")

    def act(self, room_name, percept):
        self.update_model(percept)

        if room_name == 'D':
            if self.has_keycard:
                return "Access Granted: Entering Vault"
            else:
                return "Access Denied: Keycard Required"
        elif percept['item'] == 'Keycard':
            return "Picked up Keycard"
        else:
            return "Patrolling... Area Secure"

def run():
    facility = SecureFacilityEnvironment()
    robot = SecurityRobotAgent()
    patrol_path = ['A', 'C', 'D', 'B', 'D']
    for room in patrol_path:
        print(f"\nApproaching Room {room}")
        percept = facility.get_percept(room)
        action = robot.act(room, percept)
        print(f"   Status: {percept['status']}")
        print(f"   Action: {action}")
    print("\nPatrol Complete")

run()
