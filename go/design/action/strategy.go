package design

import "fmt"

type Pay interface {
	Pay(amount float64)
}

type CreditCard struct {
	CardNumber string
}

func (c *CreditCard) Pay(amount float64) {
	fmt.Printf("Paying $%.2f using Credit Card %s\n", amount, c.CardNumber)
}

type PayPal struct {
	Email string
}

func (p *PayPal) Pay(amount float64) {
	fmt.Printf("Paying $%.2f using PayPal %s\n", amount, p.Email)
}

type Order struct {
	Amount       float64
	PaymentStyle Pay
}

func (o *Order) ProcessPayment() {
	o.PaymentStyle.Pay(o.Amount)
}

func StrategyTest() {
	creditCard := &CreditCard{CardNumber: "1234567890"}
	order1 := &Order{Amount: 100.0, PaymentStyle: creditCard}
	order1.ProcessPayment()

	payPal := &PayPal{Email: "john@example.com"}
	order2 := &Order{Amount: 50.0, PaymentStyle: payPal}
	order2.ProcessPayment()
}
