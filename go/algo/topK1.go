package algo

// 堆排序
func heapSort(arr []int) []int {
	//构建大顶堆
	for i := len(arr)/2 - 1; i >= 0; i-- {
		adjustHeap(arr, i, len(arr))
	}
	//调整堆结构+交换堆顶元素与末尾元素
	for j := len(arr) - 1; j > 0; j-- {
		arr[0], arr[j] = arr[j], arr[0]
		adjustHeap(arr, 0, j)
	}
	return arr
}
func adjustHeap(arr []int, i, length int) {
	temp := arr[i]
	for k := 2*i + 1; k < length; k = 2*k + 1 {
		if k+1 < length && arr[k] < arr[k+1] {
			k++
		}
		if arr[k] > temp {
			arr[i] = arr[k]
			i = k
		} else {
			break
		}
	}
	arr[i] = temp
}
