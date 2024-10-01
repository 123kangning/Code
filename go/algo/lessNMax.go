package algo

import (
	"fmt"
	"strconv"
)

// LessNMax 小于n的最大数，这个数组由nums中的数字组成。
func LessNMax(n int, nums []int) {
	//n = 2533
	//nums = []int{1, 2, 4, 9} //默认排好序,结果为2499
	max := -10000
	for _, v := range nums {
		if v > max {
			max = v
		}
	}
	index := 0
	strN := strconv.Itoa(n)
	min := 0
	//先正序查找，相等就跳过
	for ; index < len(strN); index++ {
		num := int(strN[index] - '0')
		sign := 0
		for i := len(nums) - 1; i >= 0; i-- {
			min = nums[i]
			if num == nums[i] {
				sign = 1
				break
			} else if num > nums[i] {
				sign = 2
				break
			}
		}
		if sign == 1 {
			continue
		}
		if sign == 2 {
			break
		}
	}
	//每个位都有相等的，倒序再找出小于当前位的最大值
	if index == len(strN) {
		for ; index >= 0; index-- {
			num := int(strN[index] - '0')
			sign := 0
			for i := len(nums) - 1; i >= 0; i-- {
				min = nums[i]
				if num > nums[i] {
					sign = 2
					break
				}
			}
			if sign == 2 {
				break
			}
		}
	}
	//从发现小于的位置开始，后面的都是nums中最大值
	base, _ := strconv.Atoi(strN[:index])
	base = base*10 + min
	index++
	for index < len(strN) {
		base = base*10 + max
		index++
	}
	fmt.Println(n, base)
}
