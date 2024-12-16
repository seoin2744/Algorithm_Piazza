def solve_maze(maze, start, finish):
    rows, cols = len(maze), len(maze[0])
    path = [] 

    def is_safe(x, y):
        return 0 <= x < rows and 0 <= y < cols and maze[x][y] == 1

    def backtrack(x, y):
        if (x, y) == finish: 
            path.append((x, y))
            return True

        if is_safe(x, y):
            path.append((x, y))
            maze[x][y] = 2  
  
            if backtrack(x + 1, y):  
                return True
            if backtrack(x, y + 1): 
                return True
            if backtrack(x - 1, y):
                return True
            if backtrack(x, y - 1): 
                return True

            path.pop()
            maze[x][y] = 1

        return False

    if backtrack(start[0], start[1]):
        return path
    else:
        return None


maze = [
    [1, 1, 0, 0, 0, 0, 0],
    [0, 1, 1, 1, 0, 0, 0],
    [0, 0, 0, 1, 0, 0, 0],
    [0, 1, 1, 1, 1, 1, 0],
    [0, 1, 0, 0, 0, 1, 0],
    [0, 1, 1, 1, 0, 1, 1],
    [0, 0, 0, 1, 1, 1, 1],
]

start = (0, 0)
finish = (6, 6)

result_path = solve_maze(maze, start, finish)

if result_path:
    print("경로:")
    print(" -> ".join([f"({x}, {y})" for x, y in result_path]))
else:
    print("경로를 찾을 수 없습니다.")
