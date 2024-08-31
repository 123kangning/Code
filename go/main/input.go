package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func input() {
	reader := bufio.NewReader(os.Stdin)
	line, _ := reader.ReadString('\n')
	part := strings.Fields(line)
	fmt.Println(part)
}
func toInt(nums []string) []int {
	ans := []int(nil)
	for _, s := range nums {
		v, _ := strconv.Atoi(s)
		ans = append(ans, v)
	}
	return ans
}
