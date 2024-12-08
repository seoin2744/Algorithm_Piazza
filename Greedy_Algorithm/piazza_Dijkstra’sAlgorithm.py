import heapq
import math

def dijkstra(graph, source):
    V = len(graph)
    distances = [math.inf] * V 
    distances[source] = 0 
    priority_queue = [(0, source)]

    print(f"출발점: {chr(source + ord('A'))}")
    while priority_queue:
        current_distance, current_node = heapq.heappop(priority_queue)

        if current_distance > distances[current_node]:
            continue

        for neighbor, weight in graph[current_node]:
            new_distance = distances[current_node] + weight
            if new_distance < distances[neighbor]:
                print(f"{chr(current_node + ord('A'))} → {chr(neighbor + ord('A'))}, {distances[neighbor]} → {new_distance}")
                distances[neighbor] = new_distance
                heapq.heappush(priority_queue, (new_distance, neighbor))

    return distances

def build_graph():
    # 0:A, 1:B, 2:C, 3:D, 4:E, 5:F
    graph = [[] for _ in range(6)]
    graph[0] = [(1, 3), (2, 5), (3, 9)]
    graph[1] = [(0, 3), (2, 3), (3, 4), (4, 7)]
    graph[2] = [(0, 5), (1, 3), (3, 2), (4, 6), (5, 8)]
    graph[3] = [(0, 9), (1, 4), (2, 2), (4, 2), (5, 2)]
    graph[4] = [(1, 7), (2, 6), (3, 2), (5, 5)]
    graph[5] = [(2, 8), (3, 2), (4, 5)]
    return graph

graph = build_graph()
source = 0  # A 노드
distances = dijkstra(graph, source)

print("\n=== 최단 경로 (출발: A) ===")
for i, distance in enumerate(distances):
    print(f"A → {chr(i + ord('A'))}: {distance}")
