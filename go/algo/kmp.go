package algo

import "fmt"

func TestKmp() {
	s1 := "abceabcabca"
	s2 := "abca"
	fmt.Println(s1, s2, Kmp(s1, s2))
	fmt.Println(s1, s2, KmpCount(s1, s2))
}

// [len()==next[last]](cn)...[len()==next[last]](last)|cur
// next[i]表示0~i-1的字符串中，前缀和后缀最长匹配的长度
// if s[cn]==s[last], next[cur]=next[last]+1
func findNext(s string) []int {
	n := len(s)
	next := make([]int, n)
	next[0] = -1
	next[1] = 0
	i, cn := 2, 0
	//i表示当前要求的next的位置，cn表示上一个字符将要匹配的位置
	for i < n {
		if s[i] == s[cn] {
			cn++
			next[i] = cn
			i++
		} else if cn > 0 {
			cn = next[cn]
		} else {
			next[i] = 0
			i++
		}
	}
	return next
}

// Kmp 返回s1中s2的位置，没有则返回-1
func Kmp(s1, s2 string) int {
	next := findNext(s2)
	i, j := 0, 0
	for i < len(s1) && j < len(s2) {
		if s1[i] == s2[j] {
			i++
			j++
		} else if next[j] == -1 {
			i++
		} else {
			j = next[j]
		}
	}
	if j == len(s2) {
		return i - j
	}
	return -1
}

// KmpCount 返回s1中包含s2的个数
func KmpCount(s1, s2 string) int {
	next := findNext(s2)
	i, j := 0, 0
	count := 0
	for i < len(s1) {
		if j == len(s2) {
			count++
			j = 0
			i -= len(s2) - 1
		}
		if s1[i] == s2[j] {
			i++
			j++
		} else if next[j] == -1 {
			i++
		} else {
			j = next[j]
		}
	}
	if j == len(s2) {
		count++
	}
	return count
}
