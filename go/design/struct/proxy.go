package design

//理解为加了前后hook函数

type Subject interface {
	Request()
}
type ConcreteSubject struct {
	Subject
}

func (c *ConcreteSubject) Request() {
	println("ConcreteSubject request")
}

type Proxy struct {
	Subject
}

func (p *Proxy) Request() {
	println("pre process")
	p.Subject.Request()
	println("post process")
}

func ProxyTest() {
	subject := &ConcreteSubject{}
	proxy := &Proxy{subject}
	proxy.Request() // Output: Proxy's pre-processing, ConcreteSubject's request, Proxy's post-processing
}
