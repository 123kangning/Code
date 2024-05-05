package algo

import "fmt"

func QuickSort(nums []int) {
	if len(nums) <= 1 {
		return
	}
	mid := 1
	for i, v := range nums {
		if v < nums[0] {
			nums[mid], nums[i] = nums[i], nums[mid]
			mid++
		}
	}
	nums[mid-1], nums[0] = nums[0], nums[mid-1]
	fmt.Println(nums)
	QuickSort(nums[:mid-1])
	QuickSort(nums[mid:])
}
