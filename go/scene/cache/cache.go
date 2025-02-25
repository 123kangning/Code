package cache

import (
	"context"
	"fmt"
	"time"
)

// 定义操作类型
type OperationType int

const (
	GetOperation OperationType = iota
	UpdateOperation
)

// EventTypeData 结构体
type EventTypeData struct {
	AlarmStrategyType string `protobuf:"bytes,1,opt,name=AlarmStrategyType,proto3" json:"AlarmStrategyType,omitempty"` // 云监控侧策略类型
	EBProductType     string `protobuf:"bytes,2,opt,name=EBProductType,proto3" json:"EBProductType,omitempty"`         // eb侧产品类型
	EBEventType       string `protobuf:"bytes,3,opt,name=EBEventType,proto3" json:"EBEventType,omitempty"`             // eb侧事件类型
	DimensionInfo     string `protobuf:"bytes,4,opt,name=DimensionInfo,proto3" json:"DimensionInfo,omitempty"`         // eb侧所需实例维度信息
	SourcePattern     string `protobuf:"bytes,5,opt,name=SourcePattern,proto3" json:"SourcePattern,omitempty"`         // eb侧所需source匹配规则
	EventCnName       string `protobuf:"bytes,6,opt,name=EventCnName,proto3" json:"EventCnName,omitempty"`             // 事件类型中文名称
	EventEnName       string `protobuf:"bytes,7,opt,name=EventEnName,proto3" json:"EventEnName,omitempty"`             // 事件类型英文名称
}

type Request struct {
	OpType        OperationType
	EBProductType string
	EBEventType   string
	Data          map[string]map[string]EventTypeData
	Result        chan *EventTypeData
}

// Cache 缓存结构体
type Cache struct {
	Data      map[string]map[string]EventTypeData
	RequestCh chan Request
	Ctx       context.Context
	Cancel    context.CancelFunc
}

// NewCache 创建新的缓存实例
func NewCache(refreshInterval time.Duration) *Cache {
	ctx, cancel := context.WithCancel(context.Background())
	cache := &Cache{
		Data:      make(map[string]map[string]EventTypeData),
		RequestCh: make(chan Request),
		Ctx:       ctx,
		Cancel:    cancel,
	}
	go cache.processRequests()
	go cache.refreshPeriodically(refreshInterval)
	return cache
}

// Get 获取缓存中的值
func (c *Cache) Get(key1, key2 string) (*EventTypeData, bool) {
	resultChan := make(chan *EventTypeData)
	c.RequestCh <- Request{
		OpType:        GetOperation,
		EBProductType: key1,
		EBEventType:   key2,
		Result:        resultChan,
	}
	result := <-resultChan
	return result, result != nil
}

// processRequests 串行操作，避免数据竞争。对于整个map替换的行为，GO官方推荐通过宏观串行的方式保障数据并发安全，使用防御性编程的思想。
func (c *Cache) processRequests() {
	for {
		select {
		case req := <-c.RequestCh:
			switch req.OpType {
			case GetOperation:
				c.handleGetRequest(req)
			case UpdateOperation:
				c.handleUpdateRequest(req)
			}
		case <-c.Ctx.Done():
			return
		}
	}
}

// handleGetRequest 处理获取请求
func (c *Cache) handleGetRequest(req Request) {
	var result *EventTypeData
	if innerMap, ok := c.Data[req.EBProductType]; ok {
		if value, ok := innerMap[req.EBEventType]; ok {
			result = &value
		}
	}
	req.Result <- result
}

// handleUpdateRequest 处理更新请求
func (c *Cache) handleUpdateRequest(req Request) {
	c.Data = req.Data
}

// refreshPeriodically 定期刷新缓存
func (c *Cache) refreshPeriodically(interval time.Duration) {
	ticker := time.NewTicker(interval)
	defer ticker.Stop()

	for {
		select {
		case <-ticker.C:
			newData := c.fetchNewData()
			c.RequestCh <- Request{
				OpType: UpdateOperation,
				Data:   newData,
			}
		case <-c.Ctx.Done():
			return
		}
	}
}

// fetchNewData 模拟从网络 RPC 调用获取新数据
func (c *Cache) fetchNewData() map[string]map[string]EventTypeData {
	// 模拟网络 RPC 调用，这里同步进行
	time.Sleep(2 * time.Second)
	return map[string]map[string]EventTypeData{
		"key1Outer": {
			"key1Inner": {
				AlarmStrategyType: "strategy1",
				EBProductType:     "product1",
				EBEventType:       "event1",
				DimensionInfo:     "dim1",
				SourcePattern:     "pattern1",
				EventCnName:       "事件1中文名",
				EventEnName:       "Event 1 English Name",
			},
		},
	}
}

// Close 关闭缓存
func (c *Cache) Close() {
	c.Cancel()
	close(c.RequestCh)
}

func generateTestData() map[string]map[string]EventTypeData {
	testData := make(map[string]map[string]EventTypeData)
	for i := 0; i < 100; i++ {
		outerKey := fmt.Sprintf("outerKey%d", i)
		innerMap := make(map[string]EventTypeData)
		for j := 0; j < 100; j++ {
			innerKey := fmt.Sprintf("innerKey%d", j)
			innerMap[innerKey] = EventTypeData{
				AlarmStrategyType: fmt.Sprintf("strategy%d", i*100+j),
				EBProductType:     fmt.Sprintf("product%d", i*100+j),
				EBEventType:       fmt.Sprintf("event%d", i*100+j),
				DimensionInfo:     fmt.Sprintf("dim%d", i*100+j),
				SourcePattern:     fmt.Sprintf("pattern%d", i*100+j),
				EventCnName:       fmt.Sprintf("事件%d中文名", i*100+j),
				EventEnName:       fmt.Sprintf("Event %d English Name", i*100+j),
			}
		}
		testData[outerKey] = innerMap
	}
	return testData
}
