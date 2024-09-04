package temp

import (
	"fmt"
	"math"
)

// GetCounter 返回一个计数器方法，输入 w 重量，返回快递费用
func GetCounter() func(w float64) int {
	w2Cost := make(map[int]int, 100)
	base := 18
	lastLevel := base
	w2Cost[1] = 18
	for i := 2; i <= 100; i++ {
		cur := int(math.Round(float64((i-1)*5+base) + float64(lastLevel)*0.01))
		lastLevel = cur
		w2Cost[i] = cur
	}
	fmt.Println(w2Cost)
	return func(w float64) int {
		realW := int(math.Ceil(w))
		return w2Cost[realW]
	}
}
