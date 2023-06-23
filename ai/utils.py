
def fillActionQueue(targetTile, level):
    middleIndex = [2]
    lineSizes = [1, 3]
    nbLines = 0
    for i in range(1, level + 1):
        if i != 1:
            lineSizes.append(lineSizes[i - 1] + 2)
            middleIndex.append(middleIndex[i - 2] + lineSizes[i] - 1)
        nbLines += 1
    lineSizes.pop(0)
    for line, middle in enumerate(middleIndex):
        if targetTile == middle:
            return 0
        if targetTile < middle and (line == 0 or targetTile > middleIndex[line - 1] + int(lineSizes[line - 1] / 2)):
            return -1
        if targetTile > middle and (line == len(middleIndex) - 1 or targetTile < middleIndex[line + 1] - int(lineSizes[line + 1] / 2)):
            return 1