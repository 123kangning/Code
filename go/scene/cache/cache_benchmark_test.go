package cache

import (
	"testing"
	"time"
)

func BenchmarkCacheGet(b *testing.B) {
	// 创建一个缓存实例，设置刷新间隔为较长时间，避免测试期间刷新影响结果
	cache := NewCache(10 * time.Second)
	defer cache.Close()

	// 生成大量测试数据
	testData := generateTestData()

	// 发送更新请求
	resultChan := make(chan *EventTypeData)
	cache.RequestCh <- Request{
		OpType: UpdateOperation,
		Data:   testData,
		Result: resultChan,
	}

	b.ResetTimer()
	outerKey := "outerKey50"
	innerKey := "innerKey50"
	for i := 0; i < b.N; i++ {
		_, _ = cache.Get(outerKey, innerKey)
	}
}
