package design

import (
	"fmt"
	"sync"
)

//以epoll为例，epoll是一个被观察者，用户是观察者，epoll发生了读IO和写IO，用户得到通知

type Observer interface {
	Update(context string)
}

type Observable interface {
	Add(observer Observer)
	Del(observer Observer)
	Notify(context string)
}

type epoll struct {
	observers []Observer
}

func (e *epoll) Add(observer Observer) {
	e.observers = append(e.observers, observer)
}

func (e *epoll) Del(observer Observer) {
	for i, v := range e.observers {
		if v == observer {
			e.observers = append(e.observers[:i], e.observers[i+1:]...)
			break
		}
	}
}

func (e *epoll) Notify(context string) {
	wg := sync.WaitGroup{}
	for _, v := range e.observers {
		wg.Add(1)
		go func(v Observer) {
			defer wg.Done()
			v.Update(context)
		}(v)
	}
	wg.Wait()
}

type user struct {
	name string
}

func (u *user) Update(context string) {
	fmt.Println(u.name, "得到epoll发生", context)
}

func ObserverTest() {
	epoll := &epoll{}
	user1 := &user{"张三"}
	user2 := &user{"李四"}
	epoll.Add(user1)
	epoll.Add(user2)
	epoll.Notify("读IO")
	epoll.Notify("写IO")
}
