class Light:
    def __init__(self,room_name):
        self.room_name = room_name
        self.is_on = False
    
    def turn_on(self):
        self.is_on = True

    def turn_off(self):
        self.is_on = False

    def status(self):
        state = "ON" if self.is_on else "OFF"
        return f"{self.room_name}: {state}"
    
kitchen_light = Light("Kitchen")
bedroom_light = Light("Bedroom")
porch_light = Light("Front Porch")

kitchen_light.turn_on()
bedroom_light.turn_on()
bedroom_light.turn_off()

print("\nCurrent House Status\n")
lights = [kitchen_light, bedroom_light, porch_light]
for light in lights:
    print(light.status())
