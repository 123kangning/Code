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

	return quickSelect(nums, 0, n-1, k)
}

func quickSelect(nums []int, low, high, k int) int {
	if low == high {
		return nums[low]
	}

	mid := (low + high) >> 1
	midVal := nums[mid]
	nums[low], nums[mid] = nums[mid], nums[low]
	l, r := low, high+1
	for l < r {
		l++
		for l <= high && nums[l] >= midVal {
			l++
		}
		r--
		for r > low && nums[r] <= midVal {
			r--
		}
		if l < r {
			nums[l], nums[r] = nums[r], nums[l]
		}
	}
	if r > 0 {
		//打乱顺序，避免陷入死循环
		nums[low], nums[r] = nums[r], nums[low]
	}
	cnt := r - low + 1
	if k <= cnt {
		return quickSelect(nums, low, r, k)
	}
	return quickSelect(nums, r+1, high, k-cnt)
}
