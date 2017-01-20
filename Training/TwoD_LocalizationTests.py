def tests (localize, show):
    # [testOne, testTwo, testThree, testFour, testFive, testSix,testSeven]
    testCase = [testOne, testTwo, testThree, testFour, testFive, testSix,testSeven]
    for index in range(len(testCase)):
        output = testCase[index](localize)
        testCheck(index, output[0], output[1], show)
def testCheck (index, actual, intended, show):
    print("Test Case: " + str(index+1), end=" ")
    if equal(actual, intended):
        print ("Success")
    else:
        print("Failure")
        print("Actual:")
        show(actual)
        print("Intended:")
        show(intended)
def equal (grid1, grid2):
    grid2 = normalize(grid2)
    if len(grid1)==len(grid2) and len(grid1[0]) == len(grid2[0]):
        for row in range(len(grid1)):
            for col in range(len(grid1[row])):
                if round(grid1[row][col],2) != round(grid2[row][col],2):
                    print("Failure @:" + str(grid1[row][col]) + str(grid2[row][col]))
                    return False
        return True
    return False
def testOne(localize):
    colors = [['G', 'G', 'G'],
              ['G', 'R', 'G'],
              ['G', 'G', 'G']]
    measurements = ['R']
    motions = [[0,0]]
    sensor_right = 1.0
    p_move = 1.0
    p = localize(colors,measurements,motions,sensor_right,p_move)
    correct_answer = (
        [[0.0, 0.0, 0.0],
         [0.0, 1.0, 0.0],
         [0.0, 0.0, 0.0]])
    return [p, correct_answer]
def testTwo(localize):
    colors = [['G', 'G', 'G'],
              ['G', 'R', 'R'],
              ['G', 'G', 'G']]
    measurements = ['R']
    motions = [[0,0]]
    sensor_right = 1.0
    p_move = 1.0
    p = localize(colors,measurements,motions,sensor_right,p_move)
    correct_answer = (
        [[0.0, 0.0, 0.0],
         [0.0, 0.5, 0.5],
         [0.0, 0.0, 0.0]])
    return [p, correct_answer]
def testThree(localize):
    colors = [['G', 'G', 'G'],
              ['G', 'R', 'R'],
              ['G', 'G', 'G']]
    measurements = ['R']
    motions = [[0,0]]
    sensor_right = 0.8
    p_move = 1.0
    p = localize(colors,measurements,motions,sensor_right,p_move)
    correct_answer = (
        [[0.06666666666, 0.06666666666, 0.06666666666],
         [0.06666666666, 0.26666666666, 0.26666666666],
         [0.06666666666, 0.06666666666, 0.06666666666]])
    return [p,correct_answer]
def testFour(localize):
    colors = [['G', 'G', 'G'],
              ['G', 'R', 'R'],
              ['G', 'G', 'G']]
    measurements = ['R', 'R']
    motions = [[0,0], [0,1]]
    sensor_right = 0.8
    p_move = 1.0
    p = localize(colors,measurements,motions,sensor_right,p_move)
    correct_answer = (
        [[0.03333333333, 0.03333333333, 0.03333333333],
         [0.13333333333, 0.13333333333, 0.53333333333],
         [0.03333333333, 0.03333333333, 0.03333333333]])
    return [p,correct_answer]
def testFive(localize):
    colors = [['G', 'G', 'G'],
              ['G', 'R', 'R'],
              ['G', 'G', 'G']]
    measurements = ['R', 'R']
    motions = [[0,0], [0,1]]
    sensor_right = 1.0
    p_move = 1.0
    p = localize(colors,measurements,motions,sensor_right,p_move)
    correct_answer = (
        [[0.0, 0.0, 0.0],
         [0.0, 0.0, 1.0],
         [0.0, 0.0, 0.0]])
    return [p, correct_answer]
def testSix(localize):
    colors = [['G', 'G', 'G'],
              ['G', 'R', 'R'],
              ['G', 'G', 'G']]
    measurements = ['R', 'R']
    motions = [[0,0], [0,1]]
    sensor_right = 0.8
    p_move = 0.5
    p = localize(colors,measurements,motions,sensor_right,p_move)
    correct_answer = (
        [[0.0289855072, 0.0289855072, 0.0289855072],
         [0.0724637681, 0.2898550724, 0.4637681159],
         [0.0289855072, 0.0289855072, 0.0289855072]])
    return [p,correct_answer]
def testSeven(localize):
    colors = [['G', 'G', 'G'],
              ['G', 'R', 'R'],
              ['G', 'G', 'G']]
    measurements = ['R', 'R']
    motions = [[0,0], [0,1]]
    sensor_right = 1.0
    p_move = 0.5
    p = localize(colors,measurements,motions,sensor_right,p_move)
    correct_answer = (
        [[0.0, 0.0, 0.0],
         [0.0, 0.33333333, 0.66666666],
         [0.0, 0.0, 0.0]])
    return [p,correct_answer]
def normalize (grid):
    # print("Pre-Norm row: " + str(len(grid)))
    # print("Pre-Norm col: " + str(len(grid[0])))
    output = []
    output_col = []
    total = sum(map(sum,grid))
    for row in grid:
        for elem in row:
            output_col.append(elem/total)
        output.append(output_col)
        output_col = []
    # print("Post-Norm row: " + str(len(output)))
    # print("Post-Norm col: " + str(len(output[0])))
    return output
