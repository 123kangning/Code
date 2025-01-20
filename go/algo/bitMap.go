package algo

import "fmt"

//位图

type BitMap struct {
	val []byte
}

func NewBitMap(n int) *BitMap {
	return &BitMap{
		val: make([]byte, n),
	}
}

func (b *BitMap) Clear() {
	clear(b.val)
}

func (b *BitMap) Show(index int) {
	for i := 0; i < 8; i++ {
		if b.val[index]&(1<<(8-i-1)) > 0 {
			fmt.Print(1)
		} else {
			fmt.Print(0)
		}
	}
	fmt.Println()
}

func (b *BitMap) Fill(v int) {
	by, bit := v/8, v%8
	//余数从0到7，一个字节中的bit位，自左向右排列
	bit = 7 - bit
	b.val[by] |= 1 << bit
}

func (b *BitMap) Exist(v int) bool {
	by, bit := v/8, v%8
	bit = 7 - bit
	return b.val[by]&(1<<bit) > 0
}

// Exists 批量判断是否在存在
func (b *BitMap) Exists(existNums []int) bool {
	for _, v := range existNums {
		if !b.Exist(v) {
			return false
		}
	}
	return true
}
