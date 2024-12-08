import heapq
from collections import Counter, defaultdict

class HuffmanNode:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq

def build_huffman_tree(text):
    freq_dict = Counter(text)
    heap = [HuffmanNode(char, freq) for char, freq in freq_dict.items()]
    heapq.heapify(heap)

    while len(heap) > 1:
        node1 = heapq.heappop(heap)
        node2 = heapq.heappop(heap)
        merged = HuffmanNode(None, node1.freq + node2.freq)
        merged.left = node1
        merged.right = node2
        heapq.heappush(heap, merged)

    return heap[0] 

def generate_huffman_codes(root):
    codes = {}

    def generate_codes_helper(node, current_code):
        if node is None:
            return
        if node.char is not None:
            codes[node.char] = current_code
        generate_codes_helper(node.left, current_code + "0")
        generate_codes_helper(node.right, current_code + "1")

    generate_codes_helper(root, "")
    return codes

def encode_text(text, codes):
    return ''.join(codes[char] for char in text)

def decode_text(encoded_text, root):
    decoded_text = []
    current_node = root
    for bit in encoded_text:
        current_node = current_node.left if bit == "0" else current_node.right
        if current_node.char is not None:
            decoded_text.append(current_node.char)
            current_node = root
    return ''.join(decoded_text)

text = "Fuzzy Wuzzy was a bear. Fuzzy Wuzzy had no hair. Fuzzy Wuzzy wasn’t very fuzzy, was he?"
root = build_huffman_tree(text)
codes = generate_huffman_codes(root)
encoded_text = encode_text(text, codes)
decoded_text = decode_text(encoded_text, root)

print("\nHuffman Codes:\n")
for char, code in codes.items():
    print(f"'{char}': {code}")
print("\nEncoded Text:\n")
print(encoded_text)
print("\nDecoded Text:\n")
print(decoded_text)
