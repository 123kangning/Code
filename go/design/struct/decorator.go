package design

import "fmt"

//一个人穿了一件又一件漂亮的衣服，这些衣服就是装饰器，人就是具体的

type Component interface {
	Operate() string
}

type ConcreteComponent struct{}

func (c *ConcreteComponent) Operate() string {
	return "ConcreteComponent"
}

type Decorator struct {
	Component Component
}

func NewDecorator(component Component) *Decorator {
	return &Decorator{Component: component}
}
func (d *Decorator) Operate() string {
	return "Decorator " + d.Component.Operate()
}

type ConcreteDecorator1 struct {
	Decorator
}

func NewConcreteDecorator1(component Component) *ConcreteDecorator1 {
	return &ConcreteDecorator1{Decorator: Decorator{Component: component}}
}
func (cd1 *ConcreteDecorator1) Operate() string {
	return cd1.Decorator.Operate() + " ConcreteDecorator1's "
}

type ConcreteDecorator2 struct {
	Decorator
}

func NewConcreteDecorator2(component Component) *ConcreteDecorator2 {
	return &ConcreteDecorator2{Decorator: Decorator{Component: component}}
}
func (cd2 *ConcreteDecorator2) Operate() string {
	return cd2.Decorator.Operate() + " ConcreteDecorator2's "
}

func DecoratorTest() {
	component := &ConcreteComponent{}
	decorator := NewDecorator(component)
	fmt.Println(decorator.Operate())
	decorator1 := NewConcreteDecorator1(decorator)
	fmt.Println(decorator1.Operate())
	decorator2 := NewConcreteDecorator2(decorator1)
	fmt.Println(decorator2.Operate()) //多个装饰器的组合，链式调用
}
