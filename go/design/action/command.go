package design

import "fmt"

// Command 接口定义了一个执行命令的方法
type Command interface {
	Execute()
}

// ConcreteCommand 实现了具体的命令
type ConcreteCommand struct {
	receiver Receiver
}

func (c *ConcreteCommand) Execute() {
	c.receiver.Action()
}

// Receiver 定义了接收者的行为
type Receiver struct{}

func (r *Receiver) Action() {
	fmt.Println("Receiver action performed")
}

// Invoker 用于调用命令
type Invoker struct {
	command Command
}

func (i *Invoker) SetCommand(c Command) {
	i.command = c
}

func (i *Invoker) ExecuteCommand() {
	i.command.Execute()
}

func CommandTest() {
	receiver := Receiver{}
	command := &ConcreteCommand{receiver: receiver}
	invoker := &Invoker{command: command}

	invoker.ExecuteCommand() // Output: Receiver action performed
}
