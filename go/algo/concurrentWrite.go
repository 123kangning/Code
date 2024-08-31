package algo

import (
	"fmt"
	"time"
)

var nums []int

func ConcurrentWrite() {
	nums1, nums2 := []int{1, 1}, []int{2, 2}
	sign := make(chan []int, 10)
	go t(sign)
	go func() {
		for i := 0; i < 10; i++ {
			go add(sign, nums1)
			go add(sign, nums2)
			time.Sleep(time.Second)
		}
		close(sign)
	}()
	go func() {
		for true {
			time.Sleep(time.Second)
			fmt.Println(nums)
		}
	}()
	time.Sleep(time.Minute)
}
func t(sign chan []int) {
	for arr := range sign {
		nums = append(nums, arr...)
	}
}
func add(sign chan []int, arr []int) {
	sign <- arr
}
