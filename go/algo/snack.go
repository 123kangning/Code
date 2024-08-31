package algo

// Snack 转为蛇形数组
func Snack(nums []int) []int {
	ans := make([][]int, 0)
	x, y, i, sign := 0, 0, 0, true
	for i < len(nums) {
		if y == 0 {
			sign = true
			ans = append(ans, []int{nums[i]})
			i++
			x++
			if i < len(nums) {
				ans = append(ans, []int{nums[i]})
			}
		} else if x == 0 {
			sign = false
			ans[x] = append(ans[x], nums[i])
			i++
			y++
			if i < len(nums) {
				ans[x] = append(ans[x], nums[i])
			}
		} else {
			ans[x] = append(ans[x], nums[i])
		}

		if sign {
			x--
			y++
		} else {
			x++
			y--
		}
		i++
	}
	ret := make([]int, 0)
	for _, v := range ans {
		//fmt.Println(v)
		ret = append(ret, v...)
	}
	return ret
}
