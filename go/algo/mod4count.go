package algo

import (
	"fmt"
	"math/big"
)

// 能被4整除的子串个数
func exec2(s string) {
	ans, n := 0, len(s)
	for j := 0; j < n; j++ {
		if (s[j]-'0')%2 == 1 {
			continue
		}
		for l := 1; l <= j+1; l++ {
			start := j - l + 1
			valStr := s[start : j+1]
			if is4(valStr) {
				ans++
				//fmt.Println(valStr, start, j, n)
			}
		}
	}
	fmt.Println(ans)
}
func is4(num string) bool {
	i := new(big.Int)
	four := &big.Int{}
	four.SetString("4", 10)
	i.SetString(num, 10)
	ret := i.Mod(i, four)
	return ret.Cmp(big.NewInt(0)) == 0
}
