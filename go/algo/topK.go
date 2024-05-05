package algo

import "fmt"

//func main() {
//	nums := []int{3, 2, 1, 5, 6, 4} // 示例输入数组
//	k := 2                          // 要找第k大的元素
//
//	kthLargest := findKthLargest(nums, k)
//	fmt.Printf("第%d大的元素是：%d\n", k, kthLargest)
//}

func findKthLargest(nums []int, k int) int {
	n := len(nums)
	if k <= 0 || k > n {
		return -1
	}

	return quickSelect(nums, 0, n-1, k)
}

func quickSelect(nums []int, low, high, k int) int {
	if low < high {
		pivotIndex := partition(nums, low, high)

		if pivotIndex == k-1 {
			return nums[pivotIndex]
		} else if pivotIndex > k-1 {
			return quickSelect(nums, low, pivotIndex-1, k)
		} else {
			return quickSelect(nums, pivotIndex+1, high, k)
		}
	}

	return nums[low]
}

func partition(nums []int, low, high int) int {
	pivot := nums[high]
	i := low - 1
	fmt.Println(nums[low : high+1])
	for j := low; j < high; j++ {
		if nums[j] >= pivot {
			i++
			nums[i], nums[j] = nums[j], nums[i]
		}
		fmt.Println(nums[low : high+1])
	}
	fmt.Println(nums[low : high+1])
	nums[i+1], nums[high] = nums[high], nums[i+1]
	fmt.Println(nums[low : high+1])
	return i + 1
}
