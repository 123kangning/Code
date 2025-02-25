package cache

import (
	"fmt"
	"testing"
	"time"
)

func TestCacheGetAndUpdate(t *testing.T) {
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

	// 随机选择一个键进行获取操作
	outerKey := "outerKey50"
	innerKey := "innerKey50"
	eventData, exists := cache.Get(outerKey, innerKey)
	if !exists {
		t.Errorf("Expected key (%s, %s) to exist, but it does not", outerKey, innerKey)
	}
	expectedStrategy := fmt.Sprintf("strategy%d", 50*100+50)
	if eventData.AlarmStrategyType != expectedStrategy {
		t.Errorf("Expected AlarmStrategyType to be %s, but got %s", expectedStrategy, eventData.AlarmStrategyType)
	}
}
