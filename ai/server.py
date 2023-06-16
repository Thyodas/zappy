import socket
import json


class ZappyClient:
    def __init__(self, port, name, machine='localhost'):
        self.port = port
        self.name = name
        self.machine = machine
        self.client_socket = None

    def connect(self):
        print("Machine {} connected on port {}".format(self.machine, self.port))
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((self.machine, self.port))
        self.send(self.name)

    def send(self, message):
        self.client_socket.sendall(message.encode('utf-8'))

    def receive(self):
        data = ""
        while True:
            part = self.client_socket.recv(1024)
            if part:
                data += part.decode('utf-8')
                if data.endswith('\n'):
                    break
            else:
                break
        return data

    def close(self):
        self.client_socket.close()

    def move_forward(self):
        self.send('Forward')
        return self.receive()

    def turn_right(self):
        self.send('Right')
        return self.receive()

    def turn_left(self):
        self.send('Left')
        return self.receive()

    def look_around(self):
        self.send('Look')
        response = self.receive()
        print(f'Response: {response}')
        if response:
            tiles = json.loads(response)
            return tiles
        else:
            return None

    def broadcast(self, text):
        self.send('Broadcast {}'.format(text))
        return self.receive()


# Decision tree implementation
class DecisionNode:
    def __init__(self, condition, true_branch, false_branch):
        self.condition = condition
        self.true_branch = true_branch
        self.false_branch = false_branch

    def make_decision(self):
        if self.condition():
            return self.true_branch.make_decision()
        else:
            return self.false_branch.make_decision()


class ActionNode:
    def __init__(self, action):
        self.action = action

    def make_decision(self):
        return self.action()


def is_front_clear():
    # Get the tiles in front of the player
    tiles = client.look_around()
    # Check if the first tile is clear
    if tiles is not None:
        return 'player' not in tiles[0]
    else:
        return False


def move_forward_action():
    return client.move_forward()


def turn_right_action():
    return client.turn_right()


# Connect to the server
client = ZappyClient(port=8005, name='JEAN')
client.connect()

# Construct the decision tree
root = DecisionNode(is_front_clear, ActionNode(move_forward_action), ActionNode(turn_right_action))

# Use the decision tree in your game loop
while True:
    action = root.make_decision()
    print(action)

client.close()
