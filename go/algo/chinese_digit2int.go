package algo

// 汉字数字与阿拉伯数字的对应关系映射
var chineseDigitMap = map[string]int{
	"零": 0,
	"一": 1,
	"二": 2,
	"三": 3,
	"四": 4,
	"五": 5,
	"六": 6,
	"七": 7,
	"八": 8,
	"九": 9,
	"十": 10,
	"百": 100,
	"千": 1000,
	"万": 10000,
	"亿": 100000000,
}

func ChineseToNumber(chineseNum []rune) int {
	result := 0
	base1 := 1 //个、万、亿
	base2 := 1 //个、十、百、千
	for i := len(chineseNum) - 1; i >= 0; i-- {
		str := string(chineseNum[i])
		digit, ok := chineseDigitMap[str]
		if !ok {
			break
		}
		if digit == 10 || digit == 100 || digit == 1000 {
			base2 = digit
		} else if digit == 10000 || digit == 10000*10000 {
			if digit > base1 {
				base1 = digit
			} else {
				base1 *= digit
			}
			base2 = 1
		} else {
			result += digit * base1 * base2
		}
	}
	return result
}
