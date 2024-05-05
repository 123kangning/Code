package algo

func CountSort(nums []int) {
	max := GetMaxValue(nums)
	count := make([]int, max+1)
	for _, v := range nums {
		count[v]++
	}
	start := 0
	for i, v := range count {
		if v > 0 {
			for j := 0; j < v; j++ {
				nums[start] = i
				start++
			}
		}
	}
}
