import client
from enum import Enum
import utils
import logger
import time

nb_players_needed_to_elevate = {
    1: 1,
    2: 2,
    3: 2,
    4: 4,
    5: 4,
    6: 6,
    7: 6,
}

resources_for_level = {
    1: client.Resources(
        food_count=0,
        linemate_count=1,
        deraumer_count=0,
        sibur_count=0,
        phiras_count=0,
        mendiane_count=0,
        thystame_count=0
    ),
    2: client.Resources(
        food_count=0,
        linemate_count=1,
        deraumer_count=1,
        sibur_count=1,
        phiras_count=0,
        mendiane_count=0,
        thystame_count=0
    ),
    3: client.Resources(
        food_count=0,
        linemate_count=2,
        deraumer_count=0,
        sibur_count=1,
        phiras_count=2,
        mendiane_count=0,
        thystame_count=0
    ),
    4: client.Resources(
        food_count=0,
        linemate_count=1,
        deraumer_count=1,
        sibur_count=2,
        phiras_count=1,
        mendiane_count=0,
        thystame_count=0
    ),
    5: client.Resources(
        food_count=0,
        linemate_count=1,
        deraumer_count=2,
        sibur_count=1,
        phiras_count=0,
        mendiane_count=3,
        thystame_count=0
    ),
    6: client.Resources(
        food_count=0,
        linemate_count=1,
        deraumer_count=6,
        sibur_count=3,
        phiras_count=1,
        mendiane_count=0,
        thystame_count=0
    ),
    7: client.Resources(
        food_count=0,
        linemate_count=2,
        deraumer_count=2,
        sibur_count=2,
        phiras_count=2,
        mendiane_count=2,
        thystame_count=1
    ),
}


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
        try:
            return self.action()
        except Exception as e:
            print(f"Error executing action: {e}")


def is_front_clear():
    try:
        tiles = client.player.look_around()
        # inventory = client.inventory()
        if tiles:
            # Check the first tile for players
            return tiles[0].player_count == 0
        else:
            return False
    except Exception as e:
        print(f"Error checking if front is clear: {e}")
        return False


def move_forward_action():
    try:
        logger.info("Moving Forward")
        return client.player.move_forward()
    except Exception as e:
        print(f"Error moving forward: {e}")


def turn_right_action():
    try:
        logger.info("Turning right")
        return client.player.turn_right()
    except Exception as e:
        print(f"Error turning right: {e}")


def is_broadcast_on():
    return client.player.broadcast_on


def enough_food_to_elevate():
    logger.info("Checking if I have enough food to elevate")
    inventory = client.player.inventory()
    if inventory is None:
        return False
    if inventory.food_count * 126 <= client.DefaultTimeLimit.INCANTATION.value * 1.2:
        return False
    logger.info("I have enough food")
    return True


def enough_food_to_fork():
    inventory = client.player.inventory()
    if inventory is None:
        return False
    if inventory.food_count * 126 <= client.DefaultTimeLimit.FORK.value * 1.5:
        return False
    return True


def is_elevation_underway():
    return client.player.elevation_underway


def enough_player_to_elevate():
    logger.warn(f"There is {client.player.nb_players_ready} ready")
    return client.player.nb_players_ready >= nb_players_needed_to_elevate[client.player.player_info.score]


def action_elevate():
    logger.info("Elevating")
    client.player.incanting = True
    data = client.player.start_incantation()
    if data == "ko":
        logger.error("Failed to level up")
        return
    client.player.player_info.score += 1
    logger.success(f"I leveled up ! I'm now level {client.player.player_info.score }")
    client.player.broadcast_on = False
    client.player.incanting = False
    client.player.uuid_incanting = ""
    client.player.leader = False
    client.player.elevation_underway = False
    client.player.ready_to_elevate = False
    client.player.incanting = False
    client.player.nb_players_ready = 1
    client.player.already_broadcast = False
    client.player.broadcast("Cancel")


def action_broadcast_elevation_ready():
    logger.success(f"I have enough resources and food to elevate to level {client.player.player_info.score + 1}")
    if client.player.player_info.score == 1:
        client.player.leader = True
        action_set_objects_down()
        return action_elevate()
    client.player.broadcast("Help elevation")
    client.player.uuid_incanting = client.player.player_info.uuid
    client.player.leader = True
    #client.player.nb_players_ready += 1
    client.player.broadcast_on = True


def action_look_for_food():
    logger.info("I'm looking for food")
    tiles = client.player.look_around()
    go_index = -1
    for index, tile in enumerate(tiles):
        if tile.resources.food_count > 0:
            go_index = index
            logger.info(f"Found food at index {go_index}!")
            break
    if go_index == 0:
        client.player.take_object("food")
    if go_index == -1:
        client.player.move_forward()
    direction = utils.fill_action_queue(go_index, client.player.player_info.score)
    client.player.move_forward()
    if direction == 1:
        client.player.turn_right()
        client.player.move_forward()
    if direction == -1:
        client.player.turn_left()
        client.player.move_forward()


def action_win():
    print("GG!")


def action_fork():
    logger.info("I'm reproducing")
    nb_connections = 0
    try:
        nb_connections = int(client.player.get_team_slots())
    except Exception as e:
        nb_connections = int(client.player.receive(client.DefaultTimeLimit.CONNECT_NBR.value, ""))
    if nb_connections == 0:
        data = client.player.add_slot()
        if data == "ko":
            logger.error("Failed to reproduce")
            return data
    client.player.fork()
    #data = client.player.fork_player()
    # if data == "ko":
    #     logger.error("Failed to reproduce")
    #     return "Failed to reproduce"
    # client.player.already_reproduced = True
    logger.success("Reproduced sucessfully")
    client.player.already_reproduced = True
    return "Reproduced sucessfully"

def is_level_8():
    return client.player.player_info.score == 8

def received_hello():
    if client.player.player_info.score >= 2:
        client.player.received_hello = True
    return client.player.received_hello

def action_wait():
    logger.info("Waiting...")
    return

def is_team_full():
    # nb_connections = 0
    # try:
    #     nb_connections = int(client.player.get_team_slots())
    # except Exception as e:
    #     nb_connections = int(client.player.receive())
    # logger.info(f"Got {nb_connections} slots")
    if client.player.already_reproduced:
        return True
    return client.player.team_size >= 6
    #return nb_connections == 0


def is_elevation_ready():
    return client.player.ready_to_elevate


def enough_resources_on_tile():
    logger.info("Checking if there is enough ressources on the tile")
    tiles = client.player.look_around()
    if tiles[0].resources.food_count > 0:
        client.player.take_object("food ")
    resources = resources_for_level[client.player.player_info.score]
    if resources.linemate_count > tiles[0].resources.linemate_count:
        return False
    if resources.mendiane_count > tiles[0].resources.mendiane_count:
        return False
    if resources.phiras_count > tiles[0].resources.phiras_count:
        return False
    if resources.sibur_count > tiles[0].resources.sibur_count:
        return False
    if resources.thystame_count > tiles[0].resources.thystame_count:
        return False
    if resources.deraumer_count > tiles[0].resources.deraumer_count:
        return False
    logger.info("There is enough ressources")
    return True


def enough_resources_to_elevate():
    if client.player.already_broadcast:
        return True
    inventory = client.player.inventory()
    if inventory is None:
        return False
    resources = resources_for_level[client.player.player_info.score]
    if resources.linemate_count > inventory.linemate_count:
        return False
    if resources.mendiane_count > inventory.mendiane_count:
        return False
    if resources.phiras_count > inventory.phiras_count:
        return False
    if resources.sibur_count > inventory.sibur_count:
        return False
    if resources.thystame_count > inventory.thystame_count:
        return False
    if resources.deraumer_count > inventory.deraumer_count:
        return False
    return True


def action_look_for_food_and_cancel_broad():
    logger.error("I'm cancelling the elevation because i don't have enough food")
    client.player.broadcast_on = False
    client.player.leader = False
    client.player.nb_players_ready = 1
    client.player.ready_to_elevate = False
    client.player.broadcast("Cancel")
    action_look_for_food()


def look_for_linemate():
    logger.info("I'm looking for linemate")
    tiles = client.player.look_around()
    go_index = -1
    for index, tile in enumerate(tiles):
        if tile.resources.linemate_count > 0:
            go_index = index
            logger.info(f"Found linemate at index {go_index}!")
            break
    if go_index == 0:
        client.player.take_object("linemate")
        if tiles[0].resources.food_count > 0:
            client.player.take_object("food")
        return
    if go_index == -1:
        client.player.move_forward()
        return
    direction = utils.fill_action_queue(go_index, client.player.player_info.score)
    client.player.move_forward()
    if direction == 1:
        client.player.turn_right()
        client.player.move_forward()
    if direction == -1:
        client.player.turn_left()
        client.player.move_forward()


def look_for_deraumer():
    logger.info("I'm looking for deraumer")
    tiles = client.player.look_around()
    go_index = -1
    for index, tile in enumerate(tiles):
        if tile.resources.deraumer_count > 0:
            go_index = index
            logger.info(f"Found deraumer at index {go_index}!")
            break
    if go_index == 0:
        client.player.take_object("deraumere")
        if tiles[0].resources.food_count > 0:
            client.player.take_object("food")
        return
    if go_index == -1:
        client.player.move_forward()
        return
    direction = utils.fill_action_queue(go_index, client.player.player_info.score)
    client.player.move_forward()
    if direction == 1:
        client.player.turn_right()
        client.player.move_forward()
    if direction == -1:
        client.player.turn_left()
        client.player.move_forward()


def look_for_mendiane():
    logger.info("I'm looking for mendiane")
    tiles = client.player.look_around()
    go_index = -1
    for index, tile in enumerate(tiles):
        if tile.resources.mendiane_count > 0:
            go_index = index
            logger.info(f"Found mendiane at index {go_index}!")
            break
    if go_index == 0:
        client.player.take_object("mendiane")
        if tiles[0].resources.food_count > 0:
            client.player.take_object("food")
        return
    if go_index == -1:
        client.player.move_forward()
        return
    direction = utils.fill_action_queue(go_index, client.player.player_info.score)
    client.player.move_forward()
    if direction == 1:
        client.player.turn_right()
        client.player.move_forward()
    if direction == -1:
        client.player.turn_left()
        client.player.move_forward()


def look_for_phiras():
    logger.info("I'm looking for phiras")
    tiles = client.player.look_around()
    go_index = -1
    for index, tile in enumerate(tiles):
        if tile.resources.phiras_count > 0:
            go_index = index
            logger.info(f"Found phiras at index {go_index}!")
            break
    if go_index == 0:
        client.player.take_object("phiras")
        if tiles[0].resources.food_count > 0:
            client.player.take_object("food")
        return
    if go_index == -1:
        client.player.move_forward()
        return
    direction = utils.fill_action_queue(go_index, client.player.player_info.score)
    client.player.move_forward()
    if direction == 1:
        client.player.turn_right()
        client.player.move_forward()
    if direction == -1:
        client.player.turn_left()
        client.player.move_forward()


def look_for_sibur():
    logger.info("I'm looking for sibur")
    tiles = client.player.look_around()
    go_index = -1
    for index, tile in enumerate(tiles):
        if tile.resources.sibur_count > 0:
            go_index = index
            logger.info(f"Found sibur at index {go_index}!")
            break
    if go_index == 0:
        client.player.take_object("sibur")
        if tiles[0].resources.food_count > 0:
            client.player.take_object("food")
        return
    if go_index == -1:
        client.player.move_forward()
        return
    direction = utils.fill_action_queue(go_index, client.player.player_info.score)
    client.player.move_forward()
    if direction == 1:
        client.player.turn_right()
        client.player.move_forward()
    if direction == -1:
        client.player.turn_left()
        client.player.move_forward()


def look_for_thystame():
    logger.info("I'm looking for thystame")
    tiles = client.player.look_around()
    go_index = -1
    for index, tile in enumerate(tiles):
        if tile.resources.thystame_count > 0:
            go_index = index
            logger.info(f"Found thystame at index {go_index}!")
            break
    if go_index == 0:
        client.player.take_object("thystame")
        if tiles[0].resources.food_count > 0:
            client.player.take_object("food")
        return
    if go_index == -1:
        client.player.move_forward()
        return
    direction = utils.fill_action_queue(go_index, client.player.player_info.score)
    client.player.move_forward()
    if direction == 1:
        client.player.turn_right()
        client.player.move_forward()
    if direction == -1:
        client.player.turn_left()
        client.player.move_forward()


def action_look_for_resources_to_elevate():
    logger.info("I'm looking for resources")
    inventory = client.player.inventory()
    if inventory is None:
        look_for_linemate()
    resources = resources_for_level[client.player.player_info.score]
    if resources.linemate_count > inventory.linemate_count:
        look_for_linemate()
        return
    if resources.mendiane_count > inventory.mendiane_count:
        look_for_mendiane()
        return
    if resources.phiras_count > inventory.phiras_count:
        look_for_phiras()
        return
    if resources.sibur_count > inventory.sibur_count:
        look_for_sibur()
        return
    if resources.thystame_count > inventory.thystame_count:
        look_for_thystame()
        return
    if resources.deraumer_count > inventory.deraumer_count:
        look_for_deraumer()
        return


def is_on_the_tile():
    return client.player.broadcastDirection == 0


def already_broadcasted():
    return client.player.already_broadcast


def action_set_objects_down():
    logger.info("I'm putting object down")
    client.player.set_object("linemate")
    if client.player.player_info.score == 2 or client.player.player_info.score >= 4:
        client.player.set_object("deraumere")
    if client.player.player_info.score >= 2:
        client.player.set_object("sibur")
    if client.player.player_info.score == 5 or client.player.player_info.score == 7:
        client.player.set_object("mendiane")
    if client.player.player_info.score == 3 or client.player.player_info.score == 4 or client.player.player_info.score >= 6:
        client.player.set_object("phiras")
    if client.player.player_info.score == 7:
        client.player.set_object("thystame")
    logger.success("I'm now waiting for the elevation")
    if not client.player.leader:
        client.player.receive(300, "Elevation")
        logger.success("Elevation underway...")
        client.player.receive(300, "Current")
        client.player.player_info.score += 1
        logger.success(f"I leveled up ! I'm now level {client.player.player_info.score }")
        client.player.broadcast_on = False
        client.player.incanting = False
        client.player.uuid_incanting = ""
        client.player.leader = False
        client.player.elevation_underway = False
        client.player.ready_to_elevate = False
        client.player.incanting = False
        client.player.nb_players_ready = 1
        client.player.already_broadcast = False


def move_toward_broadcast():
    logger.success(f"I'm moving toward broadcast with direction {client.player.broadcastDirection}")
    if client.player.broadcastDirection == -1:
        logger.warn("Waiting for updated direction...")
        return
    if client.player.broadcastDirection == 1 or client.player.broadcastDirection == 2 or client.player.broadcastDirection == 8:
        client.player.move_forward()
    if client.player.broadcastDirection == 4 or client.player.broadcastDirection == 5 or client.player.broadcastDirection == 6:
        client.player.turn_right()
        client.player.turn_right()
        client.player.move_forward()
    if client.player.broadcastDirection == 7:
        client.player.turn_right()
        client.player.move_forward()
    if client.player.broadcastDirection == 3:
        client.player.turn_left()
        client.player.move_forward()
    client.player.broadcastDirection = -1


def tell_leader_ready():
    logger.success("I'm ready to help my leader")
    client.player.broadcast("I'm here")
    client.player.already_broadcast = True


def action_tell_others_to_elevate():
    logger.success("I'm telling others to put their objects down")
    client.player.broadcast("Ready")
    client.player.ready_to_elevate = True
    action_set_objects_down()

def wait():
    logger.info("I'm waiting...")


def init_decision_tree():
    leaf_enough_players = DecisionNode(enough_player_to_elevate, ActionNode(action_tell_others_to_elevate), ActionNode(action_broadcast_elevation_ready))
    leaf_enough_resources_on_tile = DecisionNode(enough_resources_on_tile, ActionNode(action_elevate), leaf_enough_players)
    leaf_enough_food_to_elevate_solo = DecisionNode(enough_food_to_elevate, leaf_enough_resources_on_tile, ActionNode(action_look_for_food_and_cancel_broad))

    leaf_enough_food_to_fork = DecisionNode(enough_food_to_fork, ActionNode(action_fork), ActionNode(action_look_for_food))

    leaf_enough_resources_to_start_elevate = DecisionNode(enough_resources_to_elevate, ActionNode(action_broadcast_elevation_ready), ActionNode(action_look_for_resources_to_elevate))
    leaf_enough_food_to_start_elevate = DecisionNode(enough_food_to_elevate, leaf_enough_resources_to_start_elevate, ActionNode(action_look_for_food))
    leaf_connect_nbr = DecisionNode(is_team_full, leaf_enough_food_to_start_elevate, leaf_enough_food_to_fork)
    leaf_is_lvl8 = DecisionNode(is_level_8, ActionNode(wait), leaf_connect_nbr)

    leaf_elevation_ready = DecisionNode(is_elevation_ready, ActionNode(action_set_objects_down), ActionNode(wait))
    leaf_already_broadcasted = DecisionNode(already_broadcasted, leaf_elevation_ready, ActionNode(tell_leader_ready))
    leaf_on_the_tile_to_elevate = DecisionNode(is_on_the_tile, leaf_already_broadcasted, ActionNode(move_toward_broadcast))
    leaf_enough_resources_to_help_elevate = DecisionNode(enough_resources_to_elevate, leaf_on_the_tile_to_elevate, ActionNode(action_look_for_resources_to_elevate))
    leaf_enough_food_to_help_elevate = DecisionNode(enough_food_to_elevate, leaf_enough_resources_to_help_elevate, ActionNode(action_look_for_food))
    leaf_elevation_underway = DecisionNode(is_elevation_underway, leaf_enough_food_to_help_elevate, leaf_is_lvl8)

    root = DecisionNode(is_broadcast_on, leaf_enough_food_to_elevate_solo, leaf_elevation_underway)
    waitingNode = DecisionNode(received_hello, root, leaf_enough_food_to_start_elevate)
    return waitingNode
