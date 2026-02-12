import random

class LearningBasedAgent:
    def __init__(self, actions):
        self.Q = {}
        self.actions = actions
        self.alpha = 0.1      # Learning rate
        self.gamma = 0.9      # Discount factor
        self.epsilon = 0.2    # Exploration rate

    def get_Q_value(self, state, action):
        return self.Q.get((state, action), 0.0)

    def select_action(self, state):
        if random.uniform(0, 1) < self.epsilon:
            return random.choice(self.actions)
        else:
            return max(self.actions, key=lambda a: self.get_Q_value(state, a))

    def learn(self, state, action, reward, next_state):
        old_Q = self.get_Q_value(state, action)
        best_future_Q = max([self.get_Q_value(next_state, a) for a in self.actions])
        
        self.Q[(state, action)] = old_Q + self.alpha * (reward + self.gamma * best_future_Q - old_Q)

    def act(self, state):
        action = self.select_action(state)
        return action

class MouseEnvironment:
    def __init__(self):
        self.state = 'Start'

    def get_percept(self):
        return self.state

    def perform_action(self, action):
        if action == 'Go to Cheese':
            self.state = 'Cheese'
            return 10
        elif action == 'Go to Trap':
            self.state = 'Trap'
            return -10
        elif action == 'Go to Empty':
            self.state = 'Empty'
            return -1
        return 0

    def reset_to_start(self):
        self.state = 'Start'

def run(agent, environment, steps):
    for step in range(steps):
        percept = environment.get_percept()
        action = agent.act(percept)
        reward = environment.perform_action(action)
        print(f"Trial {step + 1}: Started at 'Start' -> Action: {action} -> Landed on '{environment.state}', Reward: {reward}")
        next_percept = 'Start' 
        agent.learn(percept, action, reward, next_percept)
        environment.reset_to_start()

actions = ['Go to Empty', 'Go to Cheese', 'Go to Trap']

mouse_agent = LearningBasedAgent(actions)
track_env = MouseEnvironment()

run(mouse_agent, track_env, 10)
