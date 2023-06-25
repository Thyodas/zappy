
def fill_action_queue(targetTile, level):
    middle_index = [2]
    line_sizes = [1, 3]
    nb_lines = 0
    for i in range(1, level + 1):
        if i != 1:
            line_sizes.append(line_sizes[i - 1] + 2)
            middle_index.append(middle_index[i - 2] + line_sizes[i] - 1)
        nb_lines += 1
    line_sizes.pop(0)
    for line, middle in enumerate(middle_index):
        if targetTile == middle:
            return 0
        if targetTile < middle and (line == 0 or targetTile > middle_index[line - 1] + int(line_sizes[line - 1] / 2)):
            return -1
        if targetTile > middle and (line == len(middle_index) - 1 or targetTile < middle_index[line + 1] - int(line_sizes[line + 1] / 2)):
            return 1
