import client


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