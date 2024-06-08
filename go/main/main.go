package main

import (
	"fmt"
	design "test/design/struct"
)

func main() {
	component := &design.ConcreteComponent{}
	decorator := design.NewDecorator(component)
	fmt.Println(decorator.Operate())
	decorator1 := design.NewConcreteDecorator1(decorator)
	fmt.Println(decorator1.Operate())
	decorator2 := design.NewConcreteDecorator2(decorator1)
	fmt.Println(decorator2.Operate()) //多个装饰器的组合，链式调用
}
