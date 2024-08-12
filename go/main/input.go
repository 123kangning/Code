package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func input() {
	reader := bufio.NewReader(os.Stdin)
	line, _ := reader.ReadString('\n')
	part := strings.Fields(line)
	fmt.Println(part)
}
