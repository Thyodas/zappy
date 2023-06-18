import socket
import json


class ZappyClient:
    def __init__(self, port, name, machine='localhost'):
        self.port = port
        self.name = name
        self.machine = machine
        self.client_socket = None

    def connect(self):
        try:
            print("Machine {} connected on port {}".format(self.machine, self.port))
            self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.client_socket.connect((self.machine, self.port))
            self.receive()
            self.send(self.name + "\n")
        except Exception as e:
            print(f"Error connecting to the server: {e}")

    def send(self, message):
        try:
            self.client_socket.sendall(message.encode('ascii'))
        except Exception as e:
            print(f"Error sending message: {e}")

    def receive(self):
        data = ""
        try:
            while True:
                part = self.client_socket.recv(1024)
                if part:
                    data += part.decode('ascii')
                    if data.endswith('\n'):
                        break
                else:
                    break
        except Exception as e:
            print(f"Error receiving data: {e}")
        return data

    def close(self):
        try:
            self.client_socket.close()
        except Exception as e:
            print(f"Error closing the socket: {e}")

    def move_forward(self):
        self.send('Forward\n')
        return self.receive()

    def turn_right(self):
        self.send('Right\n')
        return self.receive()

    def turn_left(self):
        self.send('Left\n')
        return self.receive()

    def look_around(self):
        self.send('Look\n')
        response = self.receive()
        print(f'Response: {response}')
        if response:
            try:
                tiles = json.loads(response)
                return tiles
            except json.JSONDecodeError as e:
                print(f"Error decoding JSON response : {str(e)}")
                return None
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
        try:
            if self.condition():
                return self.true_branch.make_decision()
            else:
                return self.false_branch.make_decision()
        except Exception as e:
            print(f"Error making decision: {e}")


class ActionNode:
    def __init__(self, action):
        self.action = action

    def make_decision(self):
        try:
            return self.action()
        except Exception as e:
            print(f"Error executing action: {e}")


def is_front_clear():
    try:
        tiles = client.look_around()
        if tiles is not None:
            return 'player' not in tiles[0]
        else:
            return False
    except Exception as e:
        print(f"Error checking if front is clear: {e}")
        return False


def move_forward_action():
    try:
        return client.move_forward()
    except Exception as e:
        print(f"Error moving forward: {e}")


def turn_right_action():
    try:
        return client.turn_right()
    except Exception as e:
        print(f"Error turning right: {e}")


client = ZappyClient(port=8005, name='JEAN')
client.connect()

root = DecisionNode(is_front_clear, ActionNode(move_forward_action), ActionNode(turn_right_action))

while True:
    try:
        action = root.make_decision()
        print(action)
    except KeyboardInterrupt:
        print("\nStopping the game...")
        client.close()
        break
    except Exception as e:
        print(f"Error in game loop: {e}")
        client.close()
        break
