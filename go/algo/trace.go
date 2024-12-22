package algo

import (
	"fmt"
	"os"
	"runtime"
	"runtime/trace"
	"time"
)

func Trace() {
	//创建trace文件
	f, err := os.Create("trace.out")
	if err != nil {
		panic(err)
	}

	defer f.Close()

	//启动trace goroutine
	err = trace.Start(f)
	if err != nil {
		panic(err)
	}
	defer trace.Stop()

	for i := 0; i < 10; i++ {
		go myTest()
	}
	select {}
}

var finish = make(chan bool)

func myTest() {
	t := time.NewTicker(100 * time.Millisecond)
	for {
		select {
		case <-finish:
			fmt.Println("finish")
			return
		case <-t.C:
			runtime.Gosched()
			fmt.Println(runtime.NumCPU())
		default:
		}
	}
}
