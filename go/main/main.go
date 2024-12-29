package main

import "strings"

func main() {

}
func choose(a, b string) string {
	if len(a) > len(b) {
		return a
	} else if len(a) < len(b) {
		return b
	}
	if strings.Compare(a, b) > 0 {
		return b
	}
	return a
}
