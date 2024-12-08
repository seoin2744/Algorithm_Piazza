import heapq

def prim(graph, start):
    mst = [] 
    visited = set()  
    min_heap = [(0, start, None)]

    print("=== Prim's Algorithm 과정 ===")
    while min_heap:
        weight, current, previous = heapq.heappop(min_heap)

        if current in visited:
            continue

        visited.add(current)
        if previous is not None:  
            mst.append((previous, current, weight))
            print(f"{previous} → {current} (가중치: {weight})")

        for neighbor, edge_weight in graph[current]:
            if neighbor not in visited:
                heapq.heappush(min_heap, (edge_weight, neighbor, current))

    return mst

graph = {
    'A': [('B', 2), ('C', 4)],
    'B': [('A', 2), ('C', 3), ('D', 9), ('G', 4), ('H', 2)],
    'C': [('A', 4), ('B', 3), ('D', 1), ('E', 3)],
    'D': [('B', 9), ('C', 1), ('E', 3), ('F', 3), ('G', 1)],
    'E': [('C', 3), ('D', 3), ('F', 2)],
    'F': [('D', 3), ('E', 2), ('G', 6)],
    'G': [('B', 4), ('D', 1), ('F', 6), ('H', 14)],
    'H': [('B', 2), ('G', 14)],
}

start_node = 'A'
mst = prim(graph, start_node)

print("\n=== Minimum Spanning Tree (MST) ===")
for edge in mst:
    print(f"{edge[0]} → {edge[1]} (가중치: {edge[2]})")

total_weight = sum(edge[2] for edge in mst)
print(f"\n총 가중치: {total_weight}")
