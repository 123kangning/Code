package design

import "fmt"

//责任链模式

type Handler interface {
	SetNext(handler Handler)
	Handle(request string)
}

// BaseHandler 是一个基础处理器结构体，实现了 SetNext 方法
type BaseHandler struct {
	next Handler
}

func (h *BaseHandler) SetNext(handler Handler) {
	h.next = handler
}

func (h *BaseHandler) Handle(request string) {
	if h.next != nil {
		h.next.Handle(request)
	}
}

// ConcreteHandlerA 是具体的处理器A
type ConcreteHandlerA struct {
	BaseHandler
	process func(request string)
}

func (h *ConcreteHandlerA) Handle(request string) {
	if request == "A" {
		h.process(request)
	} else {
		fmt.Println("ConcreteHandlerA 传递请求")
		h.BaseHandler.Handle(request)
	}
}

// ConcreteHandlerB 是具体的处理器B
type ConcreteHandlerB struct {
	BaseHandler
	process func(request string)
}

func (h *ConcreteHandlerB) Handle(request string) {
	h.process(request)
	fmt.Println("ConcreteHandlerB 传递请求")
	h.BaseHandler.Handle(request)
}

func HandlerTest() {
	handlerA := &ConcreteHandlerA{process: func(request string) {
		if request == "A" {
			fmt.Println("ConcreteHandlerA 处理请求", request)
		}
	}}
	handlerB := &ConcreteHandlerB{process: func(request string) {
		if request == "B" {
			fmt.Println("ConcreteHandlerB 处理请求", request)
		}
	}}

	handlerA.SetNext(handlerB)

	// 处理请求
	handlerA.Handle("A")
	handlerA.Handle("B")
	handlerA.Handle("C")
}
