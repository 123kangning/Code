package algo

// Fibonacci 快速幂
func Fibonacci(n int) int {
	if n < 2 {
		return n
	}
	f := [][]int{{1, 1}, {1, 0}}
	f = power(f, n-1)
	return f[0][0]
}
func power(a [][]int, n int) [][]int {
	ans := [][]int{{1, 0}, {0, 1}}

	for n > 0 {
		if n%2 == 1 {
			ans = multi(ans, a)
		}
		a = multi(a, a)
		n /= 2
	}
	return ans
}
func multi(a, b [][]int) [][]int {
	return [][]int{
		{a[0][0]*b[0][0] + a[0][1]*b[1][0], a[0][0]*b[0][1] + a[0][1]*b[1][1]},
		{a[1][0]*b[0][0] + a[1][1]*b[1][0], a[1][0]*b[0][1] + a[1][1]*b[1][1]},
	}
}
