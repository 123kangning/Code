package main

import (
	"context"
	"fmt"
	"strings"
	"time"
)

func main() {
	ctx, cancel := context.WithTimeout(context.Background(), 3*time.Second)
	defer cancel()
	fmt.Println(time.Now().Format(time.DateTime))
	<-ctx.Done()
	fmt.Println(time.Now().Format(time.DateTime))

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
