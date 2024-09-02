package main

import (
	"fmt"
	"sync"
)

func printFo(wg *sync.WaitGroup, ch chan bool) {
	for i := 0; i < 5; i++ {
		fmt.Print("foo")
		// 发送信号到通道，表示foo已打印完成
		ch <- true
		// 等待bar被打印
		<-ch
	}
	wg.Done()
}

func printBa(wg *sync.WaitGroup, ch chan bool) {
	for i := 0; i < 5; i++ {
		fmt.Print("bar")
		// 发送信号到通道，表示bar已打印完成
		ch <- true
		// 等待foo被打印
		<-ch
	}
	wg.Done()
}

func main() {
	var wg sync.WaitGroup
	ch := make(chan bool, 1)

	wg.Add(2)
	go printFo(&wg, ch)
	go printBa(&wg, ch)

	wg.Wait()
	close(ch)
}
