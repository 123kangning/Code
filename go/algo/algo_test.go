package algo

import (
	"fmt"
	"strconv"
	"testing"
)

func TestAlgo(t *testing.T) {
	TestKmp()
}
func TestTestMultiEat(t *testing.T) {
	TestMultiEat()
}
func TestMap_Add(t *testing.T) {
	hash := New(3, func(key []byte) uint32 {
		i, _ := strconv.Atoi(string(key))
		return uint32(i)
	})

	// Given the above hash function, this will give replicas with "hashes":
	// 2, 4, 6, 12, 14, 16, 22, 24, 26
	hash.Add("6", "4", "2")

	testCases := map[string]string{
		"2":  "2",
		"11": "2",
		"23": "4",
		"27": "2",
	}

	for k, v := range testCases {
		if hash.Get(k) != v {
			t.Errorf("Asking for %s, should have yielded %s", k, v)
		}
	}

	fmt.Println(hash.hashMap)
	fmt.Println(hash.keys)
	// Adds 8, 18, 28
	hash.Add("8")

	// 27 should now map to 8.
	testCases["27"] = "8"

	fmt.Println(hash.hashMap)
	fmt.Println(hash.keys)

	for k, v := range testCases {
		if hash.Get(k) != v {
			t.Errorf("Asking for %s, should have yielded %s", k, v)
		}
	}
}
func TestHashMap_Remove(t *testing.T) {
	hash := New(3, func(key []byte) uint32 {
		i, _ := strconv.Atoi(string(key))
		return uint32(i)
	})

	hash.Add("2", "4")
	testCases := map[string]string{
		"2":  "2",
		"11": "2",
		"23": "4",
		"27": "2",
	}

	for k, v := range testCases {
		if hash.Get(k) != v {
			t.Errorf("Asking for %s, should have yielded %s", k, v)
		}
	}

	//移除两个物理节点
	hash.Remove("4")
	testCases["23"] = "2"
	fmt.Println(hash.hashMap)
	fmt.Println(hash.keys)

	for k, v := range testCases {
		if hash.Get(k) != v {
			t.Errorf("Asking for %s, should have yielded %s", k, v)
		}
	}

}
func TestWeightRand(t *testing.T) {
	type args struct {
		weight []int
	}
	tests := []struct {
		name string
		args args
	}{
		{"1", args{[]int{1, 3, 5}}},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			r := WeightRand(tt.args.weight)
			for i := 0; i < 10; i++ {
				fmt.Println(r())
			}
		})
	}
}
func TestLessNMax(t *testing.T) {
	type args struct {
		n    int
		nums []int
	}
	tests := []struct {
		name string
		args args
		want int
	}{
		{"1", args{2533, []int{1, 2, 4, 9}}, 2499},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			LessNMax(tt.args.n, tt.args.nums)
		})
	}
}
func TestFibonacci(t *testing.T) {
	type args struct {
		n int
	}
	tests := []struct {
		name string
		args args
		want int
	}{
		{"1", args{0}, 0},
		{"2", args{1}, 1},
		{"10", args{10}, 55},
		{"20", args{20}, 6765},
		{"30", args{30}, 832040},
		{"40", args{40}, 102334155},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := Fibonacci(tt.args.n); got != tt.want {
				t.Errorf("Fibonacci() = %v, want %v", got, tt.want)
			}
		})
	}
}
func TestChineseToNumber(t *testing.T) {
	type args struct {
		chineseNum []rune
	}
	tests := []struct {
		name string
		args args
		want int
	}{
		{"1", args{[]rune("一千五百万四十三亿一千五百万三千四百二十一")}, 1500004315003421},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := ChineseToNumber(tt.args.chineseNum); got != tt.want {
				t.Errorf("ChineseToNumber() = %v, want %v", got, tt.want)
			}
		})
	}
}
func TestRemoveNthFromEnd(t *testing.T) {
	type fields struct {
		list *LNode
	}
	type args struct {
		n int
	}
	tests := []struct {
		name    string
		fields  fields
		args    args
		wantErr bool
	}{
		{
			name:    "n正常==1",
			fields:  func() fields { f, _ := NewList(10); return fields{list: f} }(),
			args:    args{n: 1},
			wantErr: false,
		},
		{
			name:    "n正常==10",
			fields:  func() fields { f, _ := NewList(10); return fields{list: f} }(),
			args:    args{n: 10},
			wantErr: false,
		},
		{
			name:    "n>10",
			fields:  func() fields { f, _ := NewList(10); return fields{list: f} }(),
			args:    args{n: 11},
			wantErr: true,
		},
		{
			name:    "n==0",
			fields:  func() fields { f, _ := NewList(10); return fields{list: f} }(),
			args:    args{n: 0},
			wantErr: true,
		},
		{
			name:    "n==-1",
			fields:  func() fields { f, _ := NewList(10); return fields{list: f} }(),
			args:    args{n: -1},
			wantErr: true,
		},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			_, err := RemoveNthFromEnd(tt.fields.list, tt.args.n)
			//NodePrint(res)
			if (err != nil) != tt.wantErr {
				t.Errorf("RemoveNthFromEnd() error = %v, wantErr %v", err, tt.wantErr)
				return
			}
		})
	}
}
func TestBitMap_Exist(t *testing.T) {
	type field struct {
		bitMap *BitMap
	}
	type args struct {
		fillNums  []int
		existNums []int
	}
	bMap := NewBitMap(10)
	tests := []struct {
		name  string
		field field
		args  args
		want  bool
	}{
		{
			name: "存在",
			field: field{
				bitMap: bMap,
			},
			args: args{
				fillNums:  []int{1, 2, 3, 4, 5},
				existNums: []int{1, 2, 3, 4, 5},
			},
			want: true,
		}, {
			name: "不存在",
			field: field{
				bitMap: bMap,
			},
			args: args{
				fillNums:  []int{1, 2, 3, 4},
				existNums: []int{1, 2, 3, 4, 5, 6},
			},
			want: false,
		},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			for _, v := range tt.args.fillNums {
				tt.field.bitMap.Fill(v)
			}
			if got := tt.field.bitMap.Exists(tt.args.existNums); got != tt.want {
				t.Errorf("BitMap.Exist() = %v, want %v", got, tt.want)
			}
		})
	}
}
