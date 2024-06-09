package design

type AbstractFactory interface {
	CreateFruit() Fruit
}

type AppleFactory struct {
	AbstractFactory
}

func (a *AppleFactory) CreateFruit() Fruit {
	return &apple{}
}

type BananaFactory struct {
	AbstractFactory
}

func (b *BananaFactory) CreateFruit() Fruit {
	return &banana{}
}

func FacMethodTest() {
	appleFactory := &AppleFactory{}
	apple := appleFactory.CreateFruit()
	apple.Show()
	bananaFactory := &BananaFactory{}
	banana := bananaFactory.CreateFruit()
	banana.Show()
}
