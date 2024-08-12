package algo

import (
	"fmt"
	"testing"
)

func TestBuildTrie(t *testing.T) {
	type args struct {
		words []string
	}
	tests := []struct {
		name string
		args args
	}{
		{"1", args{[]string{"abc", "bcd", "aaa", "bbb"}}},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			trie := BuildTrie(tt.args.words)
			fmt.Println(trie.String())
		})
	}
}

// TestTrie_IsExist 测试敏感词过滤
func TestTrie_IsExist(t *testing.T) {
	type args struct {
		word string
	}

	tests := []struct {
		name string
		args args
		want bool
	}{{"1", args{"mjjabc"}, true},
		{"2", args{"fhfbcd"}, true},
		{"3", args{"yyaaayyuu"}, true},
		{"4", args{"ttbbb"}, true},
		{"5", args{"abfrhr"}, false},
		{"6", args{"bcrgedr"}, false}}
	trie := BuildTrie([]string{"abc", "bcd", "aaa", "bbb"})
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := trie.IsExist(tt.args.word); got != tt.want {
				t.Errorf("Trie.IsExist() = %v, want %v", got, tt.want)
			}
		})
	}
}
