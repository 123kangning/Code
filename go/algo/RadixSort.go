package algo

import (
	"fmt"
	"math"
)

func RadixSort(arr []int) {
	// 获取数组中的最大值，确定最大值的位数
	maxValue := GetMaxValue(arr)
	maxDigits := int(math.Log10(float64(maxValue))) + 1

	// 对每一位进行计数排序
	for digit := 0; digit < maxDigits; digit++ {
		countingSort(arr, digit)
	}
}

func countingSort(arr []int, digit int) {
	n := len(arr)
	output := make([]int, n)
	count := make([]int, 10)

	// 统计当前位上每个数字的出现次数
	for i := 0; i < n; i++ {
		index := (arr[i] / int(math.Pow10(digit))) % 10
		count[index]++
	}
	fmt.Println("d=", digit, "count=", count)
	// 计算累计计数，分块，这一位小于等于i的有count[i]个
	for i := 1; i < 10; i++ {
		count[i] += count[i-1]
	}
	fmt.Println("d=", digit, "count=", count)
	// 从后向前，构建有序输出数组，为的是这一位相同时不打乱上一位排序的结果
	for i := n - 1; i >= 0; i-- {
		index := (arr[i] / int(math.Pow10(digit))) % 10
		output[count[index]-1] = arr[i]
		count[index]--
	}
	fmt.Println("d=", digit, "output=", output)
	// 将有序输出数组复制回原数组
	for i := 0; i < n; i++ {
		arr[i] = output[i]
	}
}

func GetMaxValue(arr []int) int {
	maxValue := arr[0]
	for _, num := range arr {
		if num > maxValue {
			maxValue = num
		}
	}
	return maxValue
}
