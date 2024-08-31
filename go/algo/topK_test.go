package algo

import "testing"

func TestTopK1(t *testing.T) {
	//nums := []int{3, 2, 1, 5, 6, 4,7,9}
	nums := []int{3, 2, 1, 5, 6, 4, 11, 21, 43, 7} // 示例输入数组
	k := 2                                         // 要找第k大的元素

	kthLargest := TopK1(nums, k)
	t.Logf("第%d大的元素是：%d %v\n", k, kthLargest, nums)
}
