import argparse
import socket
import json
from dataclasses import dataclass


@dataclass
class PlayerInfo:
    team: str = "Overflow"
    positionX: int = 0
    positionY: int = 0
    score: int = 0


def formatBroadCastMessage(playerInfo: PlayerInfo, message: str) -> str:
    struct = {
        "playerInfo": playerInfo,
        "message": message
    }
    return f'Broadcast {json.dumps(struct)}\n'


class ZappyClient:
    def __init__(self, port, name, machine='localhost'):
        self.port = port
        self.name = name
        self.machine = machine
        self.client_socket = None
        self.player_info: PlayerInfo = PlayerInfo()

    def connect(self):
        try:
            print("Machine {} connected on port {}".format(self.machine, self.port))
            self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.client_socket.connect((self.machine, self.port))
            self.receive()
            self.send(self.name + "\n")
        except Exception as e:
            print(f"Error connecting to the server: {e}")
            exit(1)

    def send(self, message):
        try:
            self.client_socket.sendall(message.encode('ascii'))
        except Exception as e:
            print(f"Error sending message: {e}")
            print("Message: " + message)
            exit(1)

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
        return response.strip()

    def broadcast(self, text):
        self.send(formatBroadCastMessage(self.player_info, text))
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
        tiles_str = client.look_around()
        if tiles_str is not None:
            # Parse the string into a list
            tiles = tiles_str.strip('][').split(', ')
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


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Connect to a Zappy server.", add_help=False)
    parser.add_argument('-p', '--port', type=int, required=True, help="The port number.")
    parser.add_argument('-n', '--name', required=True, help="The name of the team.")
    parser.add_argument('-h', '--host', default='localhost', help="The name of the machine; localhost by default.")
    parser.add_argument('-help', action='help', default=argparse.SUPPRESS)
    args = parser.parse_args()

    client = ZappyClient(port=args.port, name=args.name, machine=args.host)
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
