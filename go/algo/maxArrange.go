package algo

import "fmt"

// MaxArrange n个格子，m种颜色，求最大排列数
func MaxArrange(n, m int) int {
	var mod int = 1e9 + 7
	dp := make([][]int, n+1)
	for i := range dp {
		dp[i] = make([]int, m+1)
	}
	for i := 1; i <= n; i++ {
		dp[i][1] = m
	}
	for i := 1; i <= n; i++ {
		for j := 2; j <= m; j++ {
			dp[i][j] = (dp[i-1][j] * j) % mod
			dp[i][j] = (dp[i][j] + dp[i-1][j-1]*(m-j+1)) % mod
		}
	}
	for i := 0; i <= n; i++ {
		fmt.Println(dp[i])
	}
	fmt.Println()
	return dp[n][m]
}
