package algo

import (
	"fmt"
	"math/rand"
	"sort"
)

/*
通用加权轮询算法
*/

// WeightRand 第1、2、3个节点的权重为weight[0]、[1]、[2],返回节点号，从1开始
func WeightRand(weight []int) func() int {
	n := len(weight)
	pre := make([]int, n+1)
	for i, v := range weight {
		pre[i+1] = pre[i] + v
	}
	fmt.Println(pre)
	return func() int {
		r := rand.Intn(pre[n])
		ans := sort.Search(n, func(i int) bool {
			return pre[i] > r
		})
		return ans
	}
}
