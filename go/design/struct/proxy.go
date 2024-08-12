package design

//理解为加了前后hook函数
//代理是指与被代理对象具有相同的接口，客户端无需知道代理对象的存在，只需要知道被代理对象的接口即可
//代理模式的优点是可以在客户端无感知的情况下实现对被代理对象的访问控制，同时可以降低系统的耦合度
//代理模式的缺点是会造成系统设计中类的数目增加，增加了系统的复杂度
//代理模式的结构比较简单，主要包括三个角色：抽象主题角色、具体主题角色和代理主题角色
//抽象主题角色是一个接口，具体主题角色是实现抽象主题角色的类，代理主题角色也是实现抽象主题角色的类，但是在代理主题角色中可以对具体主题角色进行增强处理

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
