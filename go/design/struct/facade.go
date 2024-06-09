package design

//原系统中有多个子系统，通过外观模式提供一个简单的接口，隐藏子系统的复杂性
import "fmt"

// 子系统 - 电视机
type TV struct {
	isOn bool
}

func (t *TV) TurnOn() {
	t.isOn = true
	fmt.Println("TV has been turned on.")
}

func (t *TV) TurnOff() {
	t.isOn = false
	fmt.Println("TV has been turned off.")
}

// 子系统 - 音响
type Amplifier struct {
	isOn bool
}

func (a *Amplifier) TurnOn() {
	a.isOn = true
	fmt.Println("Amplifier has been turned on.")
}

func (a *Amplifier) TurnOff() {
	a.isOn = false
	fmt.Println("Amplifier has been turned off.")
}

func (a *Amplifier) SetVolume(volume int) {
	fmt.Printf("Amplifier volume set to %d.\n", volume)
}

// 子系统 - DVD 播放器
type DVDPlayer struct {
	isOn bool
}

func (d *DVDPlayer) TurnOn() {
	d.isOn = true
	fmt.Println("DVD Player has been turned on.")
}

func (d *DVDPlayer) TurnOff() {
	d.isOn = false
	fmt.Println("DVD Player has been turned off.")
}

func (d *DVDPlayer) PlayDVD() {
	if d.isOn {
		fmt.Println("DVD Player is playing a movie.")
	} else {
		fmt.Println("DVD Player is off.")
	}
}

// 外观模式 - 家庭影院
type HomeTheaterFacade struct {
	tv        *TV
	amplifier *Amplifier
	dvdPlayer *DVDPlayer
}

func NewHomeTheaterFacade() *HomeTheaterFacade {
	return &HomeTheaterFacade{
		tv:        &TV{},
		amplifier: &Amplifier{},
		dvdPlayer: &DVDPlayer{},
	}
}

func (h *HomeTheaterFacade) WatchMovie() {
	h.tv.TurnOn()
	h.amplifier.TurnOn()
	h.amplifier.SetVolume(5)
	h.dvdPlayer.TurnOn()
	h.dvdPlayer.PlayDVD()
}

func (h *HomeTheaterFacade) StopMovie() {
	h.tv.TurnOff()
	h.amplifier.TurnOff()
	h.dvdPlayer.TurnOff()
}

func FacadeTest() {
	homeTheater := NewHomeTheaterFacade()
	homeTheater.WatchMovie()
	fmt.Println()
	homeTheater.StopMovie()
}
