package main

import (
	"fmt"
)

func main() {
	//测试WordDictionary
	obj := Constructor()
	obj.AddWord("bad")
	obj.AddWord("dad")
	obj.AddWord("mad")
	fmt.Println(obj.Search("pad"))
	fmt.Println(obj.Search("bad"))
	fmt.Println(obj.Search(".ad"))
	fmt.Println(obj.Search("b.."))
}

type word struct {
	words [26]*word
	isEnd bool
}

func (w *word) Insert(s string) {
	node := w
	for _, c := range s {
		index := int(c - 'a')
		//fmt.Println("==>", node, index, len(node.words))
		//fmt.Println(node.words)
		//if len(node.words) == 0 {
		//	node.words = make([]*word, 26)
		//}

		if node.words[index] == nil {
			node.words[index] = &word{}
		}
		node = node.words[index]
		//fmt.Println("<==", node)
	}
	node.isEnd = true
}

func (w *word) Search(s string) bool {
	if len(s) == 0 {
		return false
	}
	node := w
	for i, c := range s {
		if node == nil {
			return false
		}
		if node.isEnd {
			return true
		}
		if c == '.' {
			newS := s[i+1:]
			if len(newS) == 0 {
				return true
			}
			for _, v := range node.words {
				if v.Search(newS) {
					return true
				}
			}
		} else {
			index := int(c - 'a')
			node = node.words[index]
		}
	}
	return node.isEnd
}

type WordDictionary struct {
	root *word
}

func Constructor() WordDictionary {
	return WordDictionary{root: &word{}}
}

func (this *WordDictionary) AddWord(word string) {
	this.root.Insert(word)
}

func (this *WordDictionary) Search(word string) bool {
	return this.root.Search(word)
}

/**
 * Your WordDictionary object will be instantiated and called as such:
 * obj := Constructor();
 * obj.AddWord(word);
 * param_2 := obj.Search(word);
 */
