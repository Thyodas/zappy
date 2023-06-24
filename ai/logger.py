import client


def info(message):
    print(f"[{client.player.player_info.uuid}] {message}")


def warn(message):
    print(f"\033[93m[{client.player.player_info.uuid}] {message}\033[0m")


def error(message):
    print(f"\033[91m[{client.player.player_info.uuid}] {message}\033[0m")


def success(message):
    print(f"\033[92m[{client.player.player_info.uuid}] {message}\033[0m")
