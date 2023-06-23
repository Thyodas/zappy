import client
from enum import Enum
import utils

nbPlayersNeededToElevate = {
    1: 1,
    2: 2,
    3: 2,
    4: 4,
    5: 4,
    6: 6,
    7: 6,
}

ressourcesForLevel = {
    1: client.Ressources(
        FoodCount=0,
        LinemateCount=1,
        SiburCount=0,
        PhirasCount=0,
        MendianeCount=0,
        ThystameCount=0
    ),
    2: client.Ressources(
        FoodCount=0,
        LinemateCount=1,
        SiburCount=1,
        PhirasCount=0,
        MendianeCount=0,
        ThystameCount=0
    ),
    3: client.Ressources(
        FoodCount=0,
        LinemateCount=2,
        SiburCount=1,
        PhirasCount=2,
        MendianeCount=0,
        ThystameCount=0
    ),
    4: client.Ressources(
        FoodCount=0,
        LinemateCount=1,
        SiburCount=2,
        PhirasCount=1,
        MendianeCount=0,
        ThystameCount=0
    ),
    5: client.Ressources(
        FoodCount=0,
        LinemateCount=1,
        SiburCount=1,
        PhirasCount=0,
        MendianeCount=3,
        ThystameCount=0
    ),
    6: client.Ressources(
        FoodCount=0,
        LinemateCount=1,
        SiburCount=3,
        PhirasCount=1,
        MendianeCount=0,
        ThystameCount=0
    ),
    7: client.Ressources(
        FoodCount=0,
        LinemateCount=2,
        SiburCount=2,
        PhirasCount=2,
        MendianeCount=2,
        ThystameCount=1
    ),
}


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
        tiles = client.player.look_around()
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
        return client.player.move_forward()
    except Exception as e:
        print(f"Error moving forward: {e}")


def turn_right_action():
    try:
        return client.player.turn_right()
    except Exception as e:
        print(f"Error turning right: {e}")

def is_broadcast_on():
    return client.player.broadcast_on

def enough_food_to_elevate():
    inventory = client.player.inventory()
    if inventory.FoodCount * 126 <= client.DefaultTimeLimit.INCANTATION / client.player.frequence:
        return False
    return True

def enough_food_to_fork():
    inventory = client.player.inventory()
    if inventory.FoodCount * 126 <= client.DefaultTimeLimit.FORK / client.player.frequence:
        return False
    return True

def is_elevation_underway():
    return client.player.elevation_underway

def enough_player_to_elevate():
    return client.player.nbPlayersReady >= nbPlayersNeededToElevate[client.player.player_info.score]

def action_elevate():
    client.player.incanting = True
    data = client.player.start_incantation()
    if data == "ko":
        return
    client.player.player_info.score += 1
    client.player.broadcast_on = False
    client.player.incanting = False

def action_broadcast_elevation_ready():
    client.player.broadcast(f"Help elevation {client.player.player_info.score}")
    client.player.leader = True

def action_look_for_food():
    tiles = client.player.look_around()
    goIndex = 0
    for index, tile in enumerate(tiles):
        if tile.FoodCount > 0:
            goIndex = index
            break
    if goIndex == 0:
        client.player.take_object("food")
    direction = utils.fillActionQueue(goIndex, client.player.player_info.score)
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
    client.player.fork_player()

def is_level_8():
    return (client.player.player_info.score == 8)

def is_team_full():
    nbConnections = int(client.player.get_team_slots())
    return nbConnections == 0

def is_elevation_ready():
    return client.player.ready_to_elevate

def enough_ressources_on_tile():
    tiles = client.player.look_around()
    ressources = ressourcesForLevel[client.player.player_info.score]
    if ressources.LinemateCount > tiles[0].Ressources.LinemateCount:
        return False
    if ressources.MendianeCount > tiles[0].Ressources.MendianeCount:
        return False
    if ressources.PhirasCount > tiles[0].Ressources.PhirasCount:
        return False
    if ressources.SiburCount > tiles[0].Ressources.SiburCount:
        return False
    if ressources.ThystameCount > tiles[0].Ressources.ThystameCount:
        return False
    return True

def enough_ressources_to_elevate():
    inventory = client.player.inventory()
    ressources = ressourcesForLevel[client.player.player_info.score]
    if ressources.LinemateCount > inventory.LinemateCount:
        return False
    if ressources.MendianeCount > inventory.MendianeCount:
        return False
    if ressources.PhirasCount > inventory.PhirasCount:
        return False
    if ressources.SiburCount > inventory.SiburCount:
        return False
    if ressources.ThystameCount > inventory.ThystameCount:
        return False
    return True

def action_look_for_food_and_cancel_broad():
    client.player.broadcast_on = False
    client.player.leader = False
    client.player.nbPlayersReady = 0
    client.player.ready_to_elevate = False
    client.player.broadcast("Cancel")
    action_look_for_food()

def look_for_linemate():
    tiles = client.player.look_around()
    goIndex = 0
    for index, tile in enumerate(tiles):
        if tile.LinemateCount > 0:
            goIndex = index
            break
    if goIndex == 0:
        client.player.take_object("linemate")
    direction = utils.fillActionQueue(goIndex, client.player.player_info.score)
    client.player.move_forward()
    if direction == 1:
        client.player.turn_right()
        client.player.move_forward()
    if direction == -1:
        client.player.turn_left()
        client.player.move_forward()

def look_for_mendiane():
    tiles = client.player.look_around()
    goIndex = 0
    for index, tile in enumerate(tiles):
        if tile.MendianeCount > 0:
            goIndex = index
            break
    if goIndex == 0:
        client.player.take_object("mendiane")
    direction = utils.fillActionQueue(goIndex, client.player.player_info.score)
    client.player.move_forward()
    if direction == 1:
        client.player.turn_right()
        client.player.move_forward()
    if direction == -1:
        client.player.turn_left()
        client.player.move_forward()

def look_for_phiras():
    tiles = client.player.look_around()
    goIndex = 0
    for index, tile in enumerate(tiles):
        if tile.PhirasCount > 0:
            goIndex = index
            break
    if goIndex == 0:
        client.player.take_object("phiras")
    direction = utils.fillActionQueue(goIndex, client.player.player_info.score)
    client.player.move_forward()
    if direction == 1:
        client.player.turn_right()
        client.player.move_forward()
    if direction == -1:
        client.player.turn_left()
        client.player.move_forward()

def look_for_sibur():
    tiles = client.player.look_around()
    goIndex = 0
    for index, tile in enumerate(tiles):
        if tile.SiburCount > 0:
            goIndex = index
            break
    if goIndex == 0:
        client.player.take_object("sibur")
    direction = utils.fillActionQueue(goIndex, client.player.player_info.score)
    client.player.move_forward()
    if direction == 1:
        client.player.turn_right()
        client.player.move_forward()
    if direction == -1:
        client.player.turn_left()
        client.player.move_forward()

def look_for_thystame():
    tiles = client.player.look_around()
    goIndex = 0
    for index, tile in enumerate(tiles):
        if tile.ThystameCount > 0:
            goIndex = index
            break
    if goIndex == 0:
        client.player.take_object("thystame")
    direction = utils.fillActionQueue(goIndex, client.player.player_info.score)
    client.player.move_forward()
    if direction == 1:
        client.player.turn_right()
        client.player.move_forward()
    if direction == -1:
        client.player.turn_left()
        client.player.move_forward()

def action_look_for_ressources_to_elevate():
    inventory = client.player.inventory()
    ressources = ressourcesForLevel[client.player.player_info.score]
    if ressources.LinemateCount > inventory.LinemateCount:
        look_for_linemate()
    if ressources.MendianeCount > inventory.MendianeCount:
        look_for_mendiane()
    if ressources.PhirasCount > inventory.PhirasCount:
        look_for_phiras()
    if ressources.SiburCount > inventory.SiburCount:
        look_for_sibur()
    if ressources.ThystameCount > inventory.ThystameCount:
        look_for_thystame()

def is_on_the_tile():
    return client.player.broadcastDirection == 0

def already_broadcasted():
    return client.player.alreadyBrocasted

def action_set_objects_down():
    client.player.set_object("linemate")
    client.player.set_object("sibur")
    client.player.set_object("mendiane")
    client.player.set_object("phiras")
    client.player.set_object("thystame")

def move_toward_broadcast():
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

def tell_leader_ready():
    client.player.broadcast("I'm here")
    client.player.alreadyBrocasted = True

def action_tell_others_to_elevate():
    client.player.broadcast("Ready")
    client.player.ready_to_elevate = True
    action_set_objects_down()

def init_decision_tree():
    leafEnoughPlayers = DecisionNode(enough_player_to_elevate, ActionNode(action_tell_others_to_elevate), ActionNode(action_broadcast_elevation_ready))
    leafEnoughRessourcesOnTile = DecisionNode(enough_ressources_on_tile, ActionNode(action_elevate), leafEnoughPlayers)
    leafEnoughFoodToElevateSolo = DecisionNode(enough_food_to_elevate, leafEnoughRessourcesOnTile, ActionNode(action_look_for_food_and_cancel_broad))

    leafEnoughFoodToFork = DecisionNode(enough_food_to_fork, ActionNode(action_fork), ActionNode(action_look_for_food))

    leafEnoughRessourcesToStartElevate = DecisionNode(enough_ressources_to_elevate, ActionNode(action_broadcast_elevation_ready), ActionNode(action_look_for_ressources_to_elevate))
    leafEnoughFoodToStartElevate = DecisionNode(enough_food_to_elevate, leafEnoughRessourcesToStartElevate, ActionNode(action_look_for_food))
    leafConnectNbr = DecisionNode(is_team_full, leafEnoughFoodToStartElevate, leafEnoughFoodToFork)
    leafIsLvl8 = DecisionNode(is_level_8, None, leafConnectNbr)

    leafElevationReady = DecisionNode(is_elevation_ready, ActionNode(action_set_objects_down), None)
    leafAlreadyBroadcasted = DecisionNode(already_broadcasted, leafElevationReady, ActionNode(tell_leader_ready))
    leafOnTheTileToElevate = DecisionNode(is_on_the_tile, leafAlreadyBroadcasted, ActionNode(move_toward_broadcast))
    leafEnoughRessourcesToHelpElevate = DecisionNode(enough_ressources_to_elevate,leafOnTheTileToElevate, ActionNode(action_look_for_ressources_to_elevate))
    leafEnoughFoodToHelpElevate = DecisionNode(enough_food_to_elevate, leafEnoughRessourcesToHelpElevate, ActionNode(action_look_for_food))
    leafElevationUnderway = DecisionNode(is_elevation_underway, leafEnoughFoodToHelpElevate, leafIsLvl8)


    root = DecisionNode(is_broadcast_on, leafEnoughFoodToElevateSolo, leafElevationUnderway)
    return root