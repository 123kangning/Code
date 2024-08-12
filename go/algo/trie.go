package algo

import "fmt"

// BuildTrie 构建字典树
func BuildTrie(words []string) *Trie {
	root := &Trie{}
	for _, word := range words {
		node := root
		for _, ch := range word {
			ch -= 'a'
			if node.children[ch] == nil {
				node.children[ch] = &Trie{}
			}
			node = node.children[ch]
		}
		node.isEnd = true
	}
	return root
}
func (t *Trie) searchPrefix(prefix string) *Trie {
	node := t
	for _, ch := range prefix {
		ch -= 'a'
		if node.children[ch] == nil {
			return nil
		}
		node = node.children[ch]
	}
	return node
}

// SearchWord 查询字典树中是否包含该前缀
func (t *Trie) SearchWord(word string) bool {
	node := t.searchPrefix(word)
	return node != nil && node.isEnd
}

type Trie struct {
	children [26]*Trie
	isEnd    bool
}

// IsExist 检测word中是否包含字典树中的一个串，用于过滤敏感词，返回是否含有敏感词
func (t *Trie) IsExist(word string) bool {
	for i := 0; i < len(word); i++ {
		node := t
		for j := i; j < len(word); j++ {
			if next := node.children[word[j]-'a']; next != nil {
				node = next
				if node.isEnd {
					//fmt.Println("word:", word[i:j+1])
					return true
				}
			} else {
				break
			}
		}
	}
	return false
}

// GetWords 获取该前缀对应的所有单词
func (t *Trie) GetWords(prefix string) []string {
	node := t.searchPrefix(prefix)
	var words []string
	var dfs func(node *Trie, path string)
	dfs = func(node *Trie, path string) {
		if node.isEnd {
			words = append(words, path)
		}
		for i, child := range node.children {
			if child != nil {
				dfs(child, fmt.Sprintf("%s%c", path, 'a'+i))
			}
		}
	}
	if node != nil {
		dfs(node, prefix)
	}
	return words
}

// 打印字典树
func (t *Trie) String() string {
	var dfs func(node *Trie, depth int) string
	dfs = func(node *Trie, depth int) string {
		var res string
		for i, child := range node.children {
			if child != nil {
				res += fmt.Sprintf("%s%c:%s\n", depthStr(depth), 'a'+i, dfs(child, depth+1))
			}
		}
		return res
	}
	return dfs(t, 0)
}
func depthStr(depth int) string {
	var res string
	for i := 0; i < depth; i++ {
		res += "--"
	}
	return res
}

//func main() {
//	//给出前缀类似的单词
//	words := []string{"dog", "dark", "cat", "door", "dodge"}
//	trie := buildTrie(words)
//	fmt.Println(trie.getWords("do"))
//}
