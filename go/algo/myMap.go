package algo

import "fmt"

func TestMyMap() {
	hashMap := NewHashMap(1)
	hashMap.Put("a", "1")
	hashMap.Put("b", "2")
	hashMap.Put("c", "3")
	hashMap.Put("a", "4")
	hashMap.Put("q", "4")
	hashMap.Print()
	fmt.Println()
	hashMap.Put("w", "4")
	hashMap.Put("e", "4")
	hashMap.Put("r", "4")
	hashMap.Print()
	fmt.Println()
	fmt.Println(hashMap.Get("a"))
	hashMap.Remove("a")
	hashMap.Print()
}

// 手写一个hashMap，使用拉链法解决hash冲突

type Node struct {
	Key  string
	Val  string
	Next *Node
}
type HashMap struct {
	Nodes []*Node
	Size  int
}

func NewHashMap(size int) *HashMap {
	return &HashMap{Nodes: make([]*Node, size), Size: size}
}
func (h *HashMap) Put(key, val string) {
	index := h.hash(key)
	node := h.Nodes[index]
	if node == nil {
		h.Nodes[index] = &Node{Key: key, Val: val}
	} else {
		for node.Next != nil {
			if node.Key == key {
				node.Val = val
				return
			}
			node = node.Next
		}
		node.Next = &Node{Key: key, Val: val}
	}
	if h.Size/len(h.Nodes) > 5 {
		h.Rehash(h.Size * 2)
	}
}
func (h *HashMap) Get(key string) string {
	index := h.hash(key)
	node := h.Nodes[index]
	for node != nil {
		if node.Key == key {
			return node.Val
		}
		node = node.Next
	}
	return ""
}
func (h *HashMap) hash(key string) int {
	sum := 0
	for _, v := range key {
		sum += int(v)
	}
	return sum % h.Size
}
func (h *HashMap) Remove(key string) {
	index := h.hash(key)
	node := h.Nodes[index]
	if node == nil {
		return
	}
	if node.Key == key {
		h.Nodes[index] = node.Next
		return
	}
	for node.Next != nil {
		if node.Next.Key == key {
			node.Next = node.Next.Next
			return
		}
		node = node.Next
	}
}
func (h *HashMap) Print() {
	for i, node := range h.Nodes {
		for node != nil {
			fmt.Printf("index:%d key:%s val:%s\n", i, node.Key, node.Val)
			node = node.Next
		}
	}
}
func (h *HashMap) Rehash(size int) {
	newHashMap := NewHashMap(size)
	for _, node := range h.Nodes {
		for node != nil {
			newHashMap.Put(node.Key, node.Val)
			node = node.Next
		}
	}
	h.Nodes = newHashMap.Nodes
	h.Size = size
}
