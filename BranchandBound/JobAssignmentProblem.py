import heapq
import copy

N = 4

class Node:
    def __init__(self, x, y, assigned, parent):
        self.parent = parent
        self.pathCost = 0
        self.cost = 0
        self.workerID = x
        self.jobID = y
        self.assigned = copy.deepcopy(assigned)
        if y != -1:
            self.assigned[y] = True

    def __lt__(self, other):
        return self.cost < other.cost

# 우선순위 큐
class CustomHeap:
    def __init__(self):
        self.heap = []

    def push(self, node):
        heapq.heappush(self.heap, (node.cost, node))

    def pop(self):
        if self.heap:
            _, node = heapq.heappop(self.heap)
            return node
        return None

def new_node(x, y, assigned, parent):
    return Node(x, y, assigned, parent)

# Bound 계산 함수
def calculate_cost(cost_matrix, x, y, assigned, is_person_based):
    cost = 0
    available = [True] * N
    for i in range(x + 1, N):
        min_val = float('inf')
        for j in range(N):
            if not assigned[j] and available[j] and cost_matrix[i if is_person_based else j][j if is_person_based else i] < min_val:
                min_val = cost_matrix[i if is_person_based else j][j if is_person_based else i]
        cost += min_val
    return cost

# 할당 출력
def print_assignments(min_node, is_person_based):
    if min_node.parent is None:
        return
    print_assignments(min_node.parent, is_person_based)
    if is_person_based:
        print("Assign Person {} to Job {}".format(chr(min_node.workerID + ord('A')), min_node.jobID + 1))
    else:
        print("Assign Job {} to Person {}".format(min_node.jobID + 1, chr(min_node.workerID + ord('A'))))

# Branch and Bound 알고리즘
def find_min_cost(cost_matrix, is_person_based=True):
    pq = CustomHeap()
    assigned = [False] * N
    root = new_node(-1, -1, assigned, None)
    root.pathCost = root.cost = 0
    root.workerID = -1
    pq.push(root)

    while True:
        min_node = pq.pop()
        i = min_node.workerID + 1
        if i == N:
            print_assignments(min_node, is_person_based)
            return min_node.cost

        for j in range(N):
            if not min_node.assigned[j]:
                child = new_node(i, j, min_node.assigned, min_node)
                child.pathCost = min_node.pathCost + (cost_matrix[i][j] if is_person_based else cost_matrix[j][i])
                child.cost = child.pathCost + calculate_cost(cost_matrix, i, j, child.assigned, is_person_based)
                pq.push(child)


cost_matrix = [
    [11, 12, 18, 40],
    [14, 15, 13, 22],
    [10, 17, 19, 23],
    [17, 14, 20, 28]
]

print("<Person 기준>")
optimal_cost_person = find_min_cost(cost_matrix, is_person_based=True)
print("\nOptimal Cost (Person 기준): {}\n".format(optimal_cost_person))


print("<Job 기준>")
optimal_cost_job = find_min_cost(cost_matrix, is_person_based=False)
print("\nOptimal Cost (Job 기준): {}\n".format(optimal_cost_job))
