package algo

import (
	"container/heap"
	"fmt"
	"sort"
)

/*
有N个餐厅和M个外卖员，每个餐厅在某个时间点会产生一个外卖订单，这些订单都有产生时间、所需送达时间和优先级。
外卖员在空闲时会选择最优先的订单来配送，直到所有订单都被送达。具体规则如下:
对于每个餐厅的订单，优先级高的订单优先，其次是所需送达时间最短的订单，再次是产生时间最早的订单。
外卖员在空闲时会从所有餐厅的最高优先级订单中挑选一个所需送达时间最短的订单进行配送，
若所需送达时间相同则选择餐厅编号最小的订单
---- 思路：
1. 订单按照开始时间顺序，依次进入优先队列
2. 外卖员也依次进入优先队列，表示每个外卖员最早什么时候能够开始送餐
3. 每次选择一个订单和一个外卖员，确定开始时间，更新外卖员下一次可以送餐的时间
4. 将所有订单遍历完毕，即可结束
*/

// Order 订单结构体
type Order struct {
	restaurant   int // 餐厅编号
	startTime    int // 订单生成时间
	priority     int // 优先级
	deliveryTime int // 送达时间
	index        int // 订单原始顺序
}

// OrderHeap 定义优先级队列的订单堆
type OrderHeap []Order

func (h OrderHeap) Len() int { return len(h) }
func (h OrderHeap) Less(i, j int) bool {
	if h[i].priority != h[j].priority {
		return h[i].priority > h[j].priority
	}
	if h[i].deliveryTime != h[j].deliveryTime {
		return h[i].deliveryTime < h[j].deliveryTime
	}
	return h[i].restaurant < h[j].restaurant
}
func (h *OrderHeap) Swap(i, j int) {
	(*h)[i], (*h)[j] = (*h)[j], (*h)[i]
}

func (h *OrderHeap) Push(x interface{}) {
	*h = append(*h, x.(Order))
}

func (h *OrderHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

// Move 主函数
func Move() {
	_, M, P := 2, 2, 4 // N: 餐厅数量, M: 外卖员数量, P: 订单数量

	// 初始化订单
	orders := []Order{
		{1, 1, 2, 5, 0},
		{1, 4, 3, 2, 1},
		{2, 2, 1, 4, 2},
		{2, 5, 2, 1, 3},
	}

	// 按生成时间排序订单
	sort.Slice(orders, func(i, j int) bool {
		return orders[i].startTime < orders[j].startTime
	})

	result := make([]int, P) // 结果数组
	pq := &OrderHeap{}       // 创建订单优先队列
	heap.Init(pq)

	// 外卖员的空闲时间，最小堆
	movers := make([]int, M)
	for i := range movers {
		movers[i] = 0 // 初始化外卖员为空闲状态
	}
	de := &MoverHeap{movers}
	heap.Init(de)

	i := 0
	// 处理订单
	for i < P || pq.Len() > 0 {
		currentTime := heap.Pop(de).(int) // 获取当前时间
		if i < P {
			currentTime = max(currentTime, orders[i].startTime) // 取当前时间和下一个订单生成时间的最大值
		}

		// 将当前时间之前的订单加入优先队列
		for i < P && orders[i].startTime <= currentTime {
			heap.Push(pq, orders[i])
			i++
		}

		if pq.Len() > 0 {
			// 取出最早空闲的外卖员
			deliveryBoyTime := currentTime

			// 选择优先级最高的订单
			topOrder := heap.Pop(pq).(Order)

			// 更新送达时间
			deliveryTime := max(deliveryBoyTime, topOrder.startTime) + topOrder.deliveryTime
			result[topOrder.index] = deliveryTime

			// 更新外卖员的空闲时间
			heap.Push(de, deliveryTime)
		} else {
			// 如果当前没有订单可分配，推进时间到下一个订单的生成时间
			if i < P {
				heap.Push(de, orders[i].startTime)
			}
		}
	}

	// 输出结果
	for _, res := range result {
		fmt.Println(res)
	}
}

type MoverHeap struct {
	ints []int
}

func (h MoverHeap) Len() int           { return len(h.ints) }
func (h MoverHeap) Less(i, j int) bool { return h.ints[i] < h.ints[j] }
func (h MoverHeap) Swap(i, j int)      { h.ints[i], h.ints[j] = h.ints[j], h.ints[i] }

func (h *MoverHeap) Push(x interface{}) {
	h.ints = append(h.ints, x.(int))
}

func (h *MoverHeap) Pop() interface{} {
	old := h.ints
	n := len(old)
	x := old[n-1]
	h.ints = old[0 : n-1]
	return x
}

// 求最大值的辅助函数
func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
