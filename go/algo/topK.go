package algo

//func main() {
//	nums := []int{3, 2, 1, 5, 6, 4} // 示例输入数组
//	k := 2                          // 要找第k大的元素
//
//	kthLargest := findKthLargest(nums, k)
//	fmt.Printf("第%d大的元素是：%d\n", k, kthLargest)
//}

func TopK1(nums []int, k int) int {
	n := len(nums)
	if k <= 0 || k > n {
		return -1
	}

	return quickSelect(nums, 0, n-1, k-1)
}

func quickSelect(nums []int, low, high, k int) int {
	if low == high {
		return nums[low]
	}

	mid := low
	midVal := nums[mid]
	l, r := low-1, high+1
	for l < r {
		l++
		for l <= high && nums[l] > midVal {
			l++
		}
		r--
		for r >= low && nums[r] < midVal {
			r--
		}
		if l < r {
			nums[l], nums[r] = nums[r], nums[l]
		}
	}
	if k <= r {
		return quickSelect(nums, low, r, k)
	}
	return quickSelect(nums, r+1, high, k)
}
