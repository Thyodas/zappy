import client
from enum import Enum
import utils
import logger

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
        DeraumerCount=0,
        SiburCount=0,
        PhirasCount=0,
        MendianeCount=0,
        ThystameCount=0
    ),
    2: client.Ressources(
        FoodCount=0,
        LinemateCount=1,
        DeraumerCount=1,
        SiburCount=1,
        PhirasCount=0,
        MendianeCount=0,
        ThystameCount=0
    ),
    3: client.Ressources(
        FoodCount=0,
        LinemateCount=2,
        DeraumerCount=0,
        SiburCount=1,
        PhirasCount=2,
        MendianeCount=0,
        ThystameCount=0
    ),
    4: client.Ressources(
        FoodCount=0,
        LinemateCount=1,
        DeraumerCount=1,
        SiburCount=2,
        PhirasCount=1,
        MendianeCount=0,
        ThystameCount=0
    ),
    5: client.Ressources(
        FoodCount=0,
        LinemateCount=1,
        DeraumerCount=2,
        SiburCount=1,
        PhirasCount=0,
        MendianeCount=3,
        ThystameCount=0
    ),
    6: client.Ressources(
        FoodCount=0,
        LinemateCount=1,
        DeraumerCount=6,
        SiburCount=3,
        PhirasCount=1,
        MendianeCount=0,
        ThystameCount=0
    ),
    7: client.Ressources(
        FoodCount=0,
        LinemateCount=2,
        DeraumerCount=2,
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
            return tiles[0].PlayerCount == 0
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
    inventory = client.player.inventory()
    if inventory == None:
        return False
    if inventory.FoodCount * 126 <= client.DefaultTimeLimit.INCANTATION.value / client.player.frequence:
        return False
    return True

def enough_food_to_fork():
    inventory = client.player.inventory()
    if inventory == None:
        return False
    if inventory.FoodCount * 126 <= client.DefaultTimeLimit.FORK.value / client.player.frequence:
        return False
    return True

def is_elevation_underway():
    return client.player.elevation_underway

def enough_player_to_elevate():
    return client.player.nbPlayersReady >= nbPlayersNeededToElevate[client.player.player_info.score]

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
    client.player.uuidIncanting = ""

def action_broadcast_elevation_ready():
    logger.info("I have enough ressources and food to elevate")
    if client.player.player_info.score == 1:
        action_set_objects_down()
        return action_elevate()
    client.player.broadcast("Help elevation")
    client.player.uuidIncanting = client.player.player_info.uuid
    client.player.leader = True
    client.player.nbPlayersReady += 1

def action_look_for_food():
    logger.info("I'm looking for food")
    tiles = client.player.look_around()
    goIndex = 0
    for index, tile in enumerate(tiles):
        if tile.Ressources.FoodCount > 0:
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
    logger.info("I'm reproducing")
    data = client.player.fork_player()
    if data == "ko":
        logger.error("Failed to reproduce")
        return "Failed to reproduce"
    client.player.alreadyReproduced = True
    logger.success("Reproduced sucessfully")
    return "Reproduced sucessfully"

def is_level_8():
    return (client.player.player_info.score == 8)

def is_team_full():
    nbConnections = int(client.player.get_team_slots())
    logger.info(f"Got {nbConnections} slots")
    if client.player.alreadyReproduced:
        return True
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
    if ressources.DeraumerCount > tiles[0].Ressources.DeraumerCount:
        return False
    return True

def enough_ressources_to_elevate():
    inventory = client.player.inventory()
    if inventory == None:
        return False
    print(client.player.player_info.score)
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
    if ressources.DeraumerCount > inventory.DeraumerCount:
        return False
    return True

def action_look_for_food_and_cancel_broad():
    logger.error("I'm cancelling the elevation because i don't have enough food")
    client.player.broadcast_on = False
    client.player.leader = False
    client.player.nbPlayersReady = 0
    client.player.ready_to_elevate = False
    client.player.broadcast("Cancel")
    action_look_for_food()

def look_for_linemate():
    logger.info("I'm looking for linemate")
    tiles = client.player.look_around()
    goIndex = 0
    for index, tile in enumerate(tiles):
        if tile.Ressources.LinemateCount > 0:
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

def look_for_deraumer():
    logger.info("I'm looking for deraumer")
    tiles = client.player.look_around()
    goIndex = 0
    for index, tile in enumerate(tiles):
        if tile.Ressources.DeraumerCount > 0:
            goIndex = index
            break
    if goIndex == 0:
        client.player.take_object("deraumer")
    direction = utils.fillActionQueue(goIndex, client.player.player_info.score)
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
    goIndex = 0
    for index, tile in enumerate(tiles):
        if tile.Ressources.MendianeCount > 0:
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
    logger.info("I'm looking for phiras")
    tiles = client.player.look_around()
    goIndex = 0
    for index, tile in enumerate(tiles):
        if tile.Ressources.PhirasCount > 0:
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
    logger.info("I'm looking for sibur")
    tiles = client.player.look_around()
    goIndex = 0
    for index, tile in enumerate(tiles):
        if tile.Ressources.SiburCount > 0:
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
    logger.info("I'm looking for thystame")
    tiles = client.player.look_around()
    goIndex = 0
    for index, tile in enumerate(tiles):
        if tile.Ressources.ThystameCount > 0:
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
    logger.info("I'm looking for ressources")
    inventory = client.player.inventory()
    if inventory == None:
        look_for_linemate()
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
    if ressources.DeraumerCount > inventory.DeraumerCount:
        look_for_deraumer()

def is_on_the_tile():
    return client.player.broadcastDirection == 0

def already_broadcasted():
    return client.player.alreadyBrocasted

def action_set_objects_down():
    logger.info("I'm putting object down")
    client.player.set_object("linemate")
    client.player.set_object("sibur")
    client.player.set_object("mendiane")
    client.player.set_object("phiras")
    client.player.set_object("thystame")
    client.player.set_object("deraumer")

def move_toward_broadcast():
    logger.info("I'm moving toward broadcast")
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
    logger.success("I'm ready to help my leader")
    client.player.broadcast("I'm here")
    client.player.alreadyBrocasted = True

def action_tell_others_to_elevate():
    logger.success("I'm telling others to put their objects down")
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