package main

import (
	"fmt"
)

type FooBar struct {
	n       int
	fooChan chan bool // 用于 Foo 完成后通知 Bar
	barChan chan bool // 用于 Bar 完成后通知 Foo
}

func NewFooBar(n int) *FooBar {
	fb := &FooBar{
		n:       n,
		fooChan: make(chan bool, 1), // 缓冲为 1 以避免初始的阻塞
		barChan: make(chan bool),
	}
	fb.fooChan <- true
	return fb
}

func (fb *FooBar) Foo(printFoo func()) {
	for i := 0; i < fb.n; i++ {
		<-fb.fooChan // 等待通知
		printFoo()
		fb.barChan <- true // 通知 Bar
	}
}

func (fb *FooBar) Bar(printBar func()) {
	for i := 0; i < fb.n; i++ {
		<-fb.barChan // 等待通知
		printBar()
		fb.fooChan <- true // 通知 Foo
	}
}

func printFoo() { fmt.Println("foo") }
func printBar() { fmt.Println("bar") }

func main() {
	f := NewFooBar(10)
	go f.Bar(printBar)
	go f.Foo(printFoo)
	//fmt.Println("hi")
}
