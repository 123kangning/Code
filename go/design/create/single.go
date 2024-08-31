package design

import (
	"fmt"
	"sync"
)

//单例模式示例

func (s *Single) Show() {
	fmt.Println("my name is ", s.Name)
}

type Single struct {
	Name string
}

func GetInstance() *Single {
	once.Do(func() {
		single = &Single{Name: "instance"}
	})
	return single
}

var once sync.Once
var single, single1 *Single

func SingleTest() {
	//单例模式示例
	single1 := GetInstance()
	single1.Show()
	single2 := GetInstance()
	single2.Show()
	fmt.Println(single1 == single2)

	single3 := GetInstance1()
	single3.Show()
	single4 := GetInstance1()
	single4.Show()
	fmt.Println(single3 == single4)
}

var mu sync.Mutex

func GetInstance1() *Single {
	if single1 != nil {
		return single1
	}
	mu.Lock()
	defer mu.Unlock()
	if single1 == nil {
		single1 = &Single{Name: "instance1"}
	}
	return single1
}
