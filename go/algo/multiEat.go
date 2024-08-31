package algo

import (
	"fmt"
	"strconv"
	"sync"
)

/*
单生产者，多消费者模型，并发退出示例
*/
var from chan string
var done chan struct{}
var wg sync.WaitGroup

func TestMultiEat() {
	from = make(chan string, 5)
	done = make(chan struct{})
	wg = sync.WaitGroup{}
	for i := 0; i < 5; i++ {
		wg.Add(1)
		go eat(strconv.Itoa(i))
	}
	foods := []string{"apple", "banana", "orange", "aaa", "bbb", "q"}
	made(foods)
	//加入wg，等待所有协程优雅结束
	wg.Wait()
	fmt.Println(len(from))
}
func made(foods []string) {
	for _, food := range foods {
		if food == "q" {
			//close了from会导致，从from中读出空字符串
			close(done)
			close(from)
			return
		}
		from <- food
	}
}

// done被关闭之后，表示并发退出
func cancelled() bool {
	select {
	case <-done:
		return true
	default:
		return false
	}
}

func eat(name string) {
	defer func() {
		fmt.Println(name, "quit")
		wg.Done()
	}()
	//只需要关闭from即可，循环会自动结束，无需再引入done来进行关闭标识
	for food := range from {
		fmt.Println(name, food, "|")
	}

	//只有一个channel，没必要使用select
	//for {
	//	if cancelled() && len(from) == 0 {
	//		fmt.Println(name, "cancel true")
	//		return
	//	} /*else {
	//		fmt.Println(name, "cancel false")
	//	}*/
	//	select {
	//	//这个case在from管道关闭之后，会有一定概率读到几个空值
	//	case food := <-from:
	//		fmt.Println(name, food, "|")
	//		//加上这个没什么用的default，会导致cpu空转飙高，不加default，会阻塞在第一个case这里
	//		//所以最后要close(from)，确保select顺利退出
	//		//default:
	//		//	fmt.Println(name, "default")
	//	}
	//	//fmt.Println(name, "loop")
	//}
}
