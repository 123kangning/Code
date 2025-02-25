package scene

import (
	"fmt"
	uuid2 "github.com/google/uuid"
	"log"
	"sync"
	"time"
)

// LongtimeLogin 扫码登录，长轮询实现
func LongtimeLogin() {
	lm := &loginManager{
		uuidChan: make(chan string, 1000),
		mapAuth: &myRWMap{
			lock: sync.RWMutex{},
			m:    make(map[string]*auth),
		},
	}
	go lm.MobileScan()
	//模拟多次定时登录
	ticker := time.NewTicker(time.Second * 5)
	for range ticker.C {
		go lm.PcLogin()
	}
	select {}
}

type myMap interface {
	get(uuid string) (*auth, bool)
	set(uuid string, a *auth)
	del(uuid string)
}

// 读写相当或写远大于读时使用
type myRWMap struct {
	lock sync.RWMutex
	m    map[string]*auth
}

func (m *myRWMap) get(uuid string) (*auth, bool) {
	m.lock.RLock()
	defer m.lock.RUnlock()
	val, ok := m.m[uuid]
	return val, ok
}

func (m *myRWMap) set(uuid string, a *auth) {
	m.lock.Lock()
	defer m.lock.Unlock()
	m.m[uuid] = a
}

func (m *myRWMap) del(uuid string) {
	m.lock.Lock()
	defer m.lock.Unlock()
	delete(m.m, uuid)
}

// 读远大于写时使用
type mySyncMap struct {
	m sync.Map
}

func (m *mySyncMap) get(uuid string) (*auth, bool) {
	value, ok := m.m.Load(uuid)
	if !ok {
		return nil, false
	}
	a, ok := value.(*auth)
	return a, ok
}

func (m *mySyncMap) set(uuid string, a *auth) {
	m.m.Store(uuid, a)
}

func (m *mySyncMap) del(uuid string) {
	m.m.Delete(uuid)
}

type loginManager struct {
	//维护二维码UUID的chan
	uuidChan chan string
	//维护二维码UUID到Auth的映射
	mapAuth myMap
}
type auth struct {
	//登录uuid
	uuid string
	//用户token
	Token string
	Done  chan string
}

func (lm *loginManager) PcLogin() {
	//生成真正的uuid
	uuid, err := uuid2.NewUUID()
	if err != nil {
		log.Default().Println("uuid2.NewUUID() failed, err:", err)
		return
	}
	a := &auth{
		uuid:  uuid.String(),
		Token: "",
		Done:  make(chan string),
	}
	//维护二维码UUID到Auth的映射
	lm.mapAuth.set(a.uuid, a)
	//模拟发送登录二维码给PC端
	fmt.Println("PC login uuid:", a.uuid)
	lm.uuidChan <- a.uuid

	//等待手机端确认登录
	a.Token = <-a.Done

	//登录完成后，删除二维码UUID到Auth的映射
	lm.mapAuth.del(a.uuid)
	fmt.Println("PC login success")
	fmt.Println("PC login Token:", a.Token, "\n--------------------------------")
}

func (lm *loginManager) MobileConfirmLogin(uuid string, token string) {
	a, ok := lm.mapAuth.get(uuid)
	if !ok {
		log.Default().Println("MobileLogin failed, uuid2 not exist")
		return
	}
	a.Done <- token
	fmt.Println("Mobile login confirm success")
}

// MobileScan 模拟用户扫码
func (lm *loginManager) MobileScan() {
	for uuid := range lm.uuidChan {
		//模拟手机端扫码登录
		fmt.Println("Mobile scan uuid:", uuid)
		time.Sleep(time.Second)
		//模拟手机端确认登录
		lm.MobileConfirmLogin(uuid, "kangning's token")
	}
}
