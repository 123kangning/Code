package main

import (
	"fmt"
	"math"
)

// s,[]s
func main() {
	var x int8 = 127
	fmt.Println(math.MaxInt8)
	fmt.Println(reverse1(x))
}

// 逐步二进制，避免循环溢出
func reverse(x int8) (int8, bool) {
	fmt.Println("x=", x)
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

// base增加前，进行溢出判断：base*10+t>max => base>(max-t)/10
func reverse1(x int8) (int8, bool) {
	fmt.Println("x=", x)
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
