import argparse
import client
import decisionTree

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Connect to a Zappy server.", add_help=False)
    parser.add_argument('-p', '--port', type=int, required=True, help="The port number.")
    parser.add_argument('-n', '--name', required=True, help="The name of the team.")
    parser.add_argument('-h', '--host', default='localhost', help="The name of the machine; localhost by default.")
    parser.add_argument('-help', action='help', default=argparse.SUPPRESS)
    args = parser.parse_args()

    client.player = client.ZappyClient(port=args.port, name=args.name, machine=args.host)
    client.player.connect()

    root = decisionTree.init_decision_tree()

    while True:
        action = root.make_decision()
        # try:
        #     print(action)
        # except KeyboardInterrupt:
        #     print("\nStopping the game...")
        #     client.player.close()
        #     break
        # except Exception as e:
        #     print(f"Error in game loop: {e}")
        #     client.player.close()
        #     break
