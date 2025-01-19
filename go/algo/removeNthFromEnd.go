package algo

import (
	"fmt"
	"github.com/pkg/errors"
)

//删除倒数第n个节点

type LNode struct {
	val  int
	Next *LNode
}

func NewList(n int) (*LNode, error) {
	if n < 1 {
		return nil, errors.New("n需要>=1")
	}
	head := &LNode{}
	cur := head
	for i := 1; i <= n; i++ {
		n := &LNode{
			val:  i,
			Next: nil,
		}
		cur.Next = n
		cur = cur.Next
	}
	return head.Next, nil
}

func NodePrint(head *LNode) {
	if head == nil {
		fmt.Println("链表为nil")
		return
	}
	for cur := head; cur != nil; cur = cur.Next {
		fmt.Printf("-> %d ", cur.val)
	}
	fmt.Println()
}

func RemoveNthFromEnd(head *LNode, n int) (*LNode, error) {
	if n <= 0 {
		return nil, errors.New("n 需要大于0")
	}
	last := &LNode{Next: head}
	to := last
	for i := 0; i < n; i++ {
		to = to.Next
		if to == nil {
			return nil, errors.New("n 大于链表长度")
		}
	}
	cur := last
	for to.Next != nil {
		to = to.Next
		cur = cur.Next
	}
	cur.Next = cur.Next.Next
	return last.Next, nil
}
