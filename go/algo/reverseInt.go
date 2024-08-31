package algo

import (
	"math"
)

// Reverse 逐步二进制，避免循环溢出
func Reverse(x int8) (int8, bool) {
	var base int8 = 0
	for x > 0 {
		t := x % 10
		x /= 10
		tt := base << 1
		for i := 0; i < 3; i++ {
			base <<= 1
			if base < 0 {
				return 0, false
			}
		}
		base = base + tt + t
		if base < 0 {
			return 0, false
		}
	}
	return base, true
}

// Reverse1 base增加前，进行溢出判断：base*10+t>max => base>(max-t)/10
func Reverse1(x int8) (int8, bool) {
	var max int8 = math.MaxInt8
	var base int8 = 0
	for x > 0 {
		t := x % 10
		x /= 10
		if base > (max-t)/10 {
			return 0, false
		}
		base = base*10 + t
	}
	return base, true
}
