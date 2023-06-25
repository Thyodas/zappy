import argparse
import client
import decisionTree
import time
import logger
import sys
import signal

def signal_handler(sig, frame):
    sys.exit(0)

if __name__ == "__main__":
    signal.signal(signal.SIGINT, signal_handler)
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
        try:
            action = root.make_decision()
        except Exception as e:
            logger.error(e)
        client.player.elasped_time = time.time() - client.player.last_broadcast
        remaining_time = (client.DefaultTimeLimit.REGULAR_BROADCAST.value / client.player.frequency) - client.player.elasped_time
        # if remaining_time <= 0:
        #     client.player.broadcast("I'm alive")
        #     client.player.last_broadcast = time.time()
        #     client.player.elasped_time = 0
        if len(client.player.broadcast_queue) != 0:
            message = client.player.broadcast_queue.pop(0)
            client.player.broadcast(message)
            client.player.broadcast_queue.clear()
        # for message in client.player.broadcast_queue:
        #     client.player.broadcast(message)
        # for index, mates in enumerate(client.player.teammates):
        #     if time.perf_counter() - mates.last_timestamp > (mates.last_timestamp + 1_000_000 * (client.DefaultTimeLimit.REGULAR_BROADCAST.value / client.player.frequency)) * 2:
        #         client.player.teammates.pop(index)
        logger.info(f"My team size is {client.player.team_size}")
        try:
            print(action)
        except KeyboardInterrupt:
            print("\nStopping the game...")
            client.player.close()
            break
        # except Exception as e:
        #     print(f"Error in game loop: {e}")
        #     client.player.close()
        #     break
