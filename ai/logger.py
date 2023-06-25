import client


fast = 0

def info(message):
    if fast == 0:
        print(f"[{client.player.player_info.uuid}][{client.player.player_info.score}] {message}")


def warn(message):
    if fast == 0:
        print(f"\033[93m[{client.player.player_info.uuid}][{client.player.player_info.score}] {message}\033[0m")


def error(message):
    if fast == 0:
        print(f"\033[91m[{client.player.player_info.uuid}][{client.player.player_info.score}] {message}\033[0m")


def success(message):
    if fast == 0:
        print(f"\033[92m[{client.player.player_info.uuid}][{client.player.player_info.score}] {message}\033[0m")
