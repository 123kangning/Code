package algo

import (
	"fmt"
	"hash/crc32"
	"sort"
	"strconv"
)

/*
一致性hash理论
在实际使用中，还需要维护一个物理节点key到实际节点ip:port的映射,用于最终的请求定位
虚拟节点hash冲突：后者和前者冲突，后者添加失败
*/

// Hash maps bytes to uint32
type Hash func(data []byte) uint32

// Map 一致性hash对象
type Map struct {
	hash     Hash
	replicas int            //每个物理节点对应多少个虚拟节点
	keys     []int          // 存放虚拟节点的hash值
	hashMap  map[int]string //存放虚拟节点到物理节点的映射
}

// New creates a Map instance
func New(replicas int, fn Hash) *Map {
	m := &Map{
		replicas: replicas,
		hash:     fn,
		hashMap:  make(map[int]string),
	}
	if m.hash == nil {
		m.hash = crc32.ChecksumIEEE
	}
	return m
}

// Add 从物理节点生成虚拟节点，将虚拟节点加到哈希环中，维护虚拟节点到物理节点的映射
func (m *Map) Add(keys ...string) {
	for _, key := range keys {
		for i := 0; i < m.replicas; i++ {
			hash := int(m.hash([]byte(strconv.Itoa(i) + key)))

			//该虚拟节点的hash槽位已经被使用，直接跳过
			if _, exist := m.hashMap[hash]; exist {
				continue
			}
			fmt.Println("hash=", hash)
			m.keys = append(m.keys, hash)
			m.hashMap[hash] = key
		}
	}
	sort.Ints(m.keys)
}

// Get 找到key对应的虚拟节点，再找到对应的物理节点
func (m *Map) Get(key string) string {
	if len(m.keys) == 0 {
		return ""
	}

	hash := int(m.hash([]byte(key)))
	// Binary search for appropriate replica.
	idx := sort.Search(len(m.keys), func(i int) bool {
		h := m.keys[i]
		if h < hash {
			return false
		}
		_, exist := m.hashMap[h]
		return exist
	})

	return m.hashMap[m.keys[idx%len(m.keys)]]
}

// Remove 移除对应物理节点，并移除对应的虚拟节点
func (m *Map) Remove(keys ...string) {
	for _, key := range keys {
		for i := 0; i < m.replicas; i++ {
			hash := int(m.hash([]byte(strconv.Itoa(i) + key)))
			//虚拟节点hash冲突,导致该物理节点的这个虚拟节点一开始就设置失败了，也不用删除
			//此时的虚拟节点对应的是另一个物理节点
			if oldKey, _ := m.hashMap[hash]; oldKey != key {
				continue
			}
			fmt.Println("del hash=", hash)
			delete(m.hashMap, hash)
		}
	}
}
