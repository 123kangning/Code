package algo

import (
	"fmt"
	"time"
)

func PrintABC() {
	go printA()
	go printB()
	go printC()
	cha <- struct{}{}
	select {}
}

var cha, chb, chc = make(chan struct{}), make(chan struct{}), make(chan struct{})

func printA() {
	for {
		<-cha
		fmt.Println("a")
		time.Sleep(time.Second)
		chb <- struct{}{}
	}
}
func printB() {
	for {
		<-chb
		fmt.Println("b")
		time.Sleep(time.Second)
		chc <- struct{}{}
	}
}
func printC() {
	for {
		<-chc
		fmt.Println("c")
		time.Sleep(time.Second)
		cha <- struct{}{}
	}
}
