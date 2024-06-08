package design

type Fruit interface {
	Show()
}
type apple struct {
	Fruit
}

func (a *apple) Show() {
	println("apple")
}

type banana struct {
	Fruit
}

func (b *banana) Show() {
	println("banana")
}
func NewFruit(name string) Fruit {
	switch name {
	case "apple":
		return &apple{}
	case "banana":
		return &banana{}
	}
	return nil
}
