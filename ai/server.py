import argparse
import os
import socket
import json
import sys
from dataclasses import dataclass, field


@dataclass
class Ressources:
    FoodCount: int = 0
    LinemateCount: int = 0
    SiburCount: int = 0
    PhirasCount: int = 0
    MendianeCount: int = 0
    ThystameCount: int = 0


@dataclass
class PlayerInfo:
    team: str = "Overflow"
    positionX: int = 0
    positionY: int = 0
    score: int = 0
    inventory: dict = field(default_factory=dict)


@dataclass
class Tile:
    PlayerCount: int = 0
    Ressources: Ressources = field(default_factory=Ressources)


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

    def get_team_slots(self):
        self.send('Connect_nbr\n')
        return self.receive().strip()

    def fork_player(self):
        self.send('Fork\n')
        response = self.receive()
        if response.strip() == "ok":
            pid = os.fork()
            if pid == 0:
                os.execv(sys.executable, ['python'] + sys.argv)
        return response

    def eject_players(self):
        self.send('Eject\n')
        return self.receive()

    def take_object(self, object_name):
        self.send(f'Take {object_name}\n')
        return self.receive()

    def set_object(self, object_name):
        self.send(f'Set {object_name}\n')
        return self.receive()

    def start_incantation(self):
        self.send('Incantation\n')
        return self.receive()

    # Store the inventory in the player_info + return it
    def inventory(self):
        try:
            self.send('Inventory\n')

            response = self.receive()

            response = response.strip('][')
            response = ' '.join(response.split())
            items = response.split(',')

            inventory: Ressources = Ressources()
            for item in items:
                item = item.strip()
                key_value = item.split(' ')

                key = key_value[0]
                value = int(key_value[1])

                if key == 'food':
                    inventory.FoodCount = value
                elif key == 'linemate':
                    inventory.LinemateCount = value
                elif key == 'deraumere':
                    inventory.DeraumerCount = value
                elif key == 'sibur':
                    inventory.SiburCount = value
                elif key == 'mendiane':
                    inventory.MendianeCount = value
                elif key == 'phiras':
                    inventory.PhirasCount = value
                elif key == 'thystame':
                    inventory.ThystameCount = value

            print("Inventory: " + str(inventory))
            self.player_info.inventory = inventory
            return inventory
        except Exception as e:
            print(f"Error getting inventory: {e}")

    def turn_left(self):
        self.send('Left\n')
        return self.receive()

    def look_around(self):
        try:
            self.send('Look\n')
            response = self.receive()

            response = response.strip('][')
            response = ' '.join(response.split())
            tiles = response.split(',')

            tilesList: Tile = []

            for tile_info in tiles:
                tile_info = tile_info.strip()
                items = tile_info.split(' ')

                tile = Tile()
                for item in items:
                    if item == 'player':
                        tile.PlayerCount += 1
                    elif item == 'food':
                        tile.Ressources.FoodCount += 1
                    elif item == 'linemate':
                        tile.Ressources.LinemateCount += 1
                    elif item == 'deraumere':
                        tile.Ressources.DeraumerCount += 1
                    elif item == 'sibur':
                        tile.Ressources.SiburCount += 1
                    elif item == 'mendiane':
                        tile.Ressources.MendianeCount += 1
                    elif item == 'phiras':
                        tile.Ressources.PhirasCount += 1
                    elif item == 'thystame':
                        tile.Ressources.ThystameCount += 1

                tilesList.append(tile)

            return tilesList
        except Exception as e:
            print(f"Error looking around: {e}")

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
        tiles = client.look_around()
        # inventory = client.inventory()
        if tiles:
            # Check the first tile for players
            return tiles[0].PlayerCount == 0
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
