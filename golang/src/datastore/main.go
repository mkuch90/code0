package main

import (
	"fmt"
	"time"
	//  "strconv"
)

import "shard"

type newclass struct {
	val string
}

func NewClass(val string) newclass {
	c := newclass{val}
	return c
}

func PrintLn(s string) {
	fmt.Printf(s)
	fmt.Printf("\n")

}

func WaitForInterrupt() {
	PrintLn("Waiting for interrupt <ctrl+c>")
	for true {
	}
}

func main() {

	shard.StartShardMaster(3)
	duration := time.Duration(1) * time.Second
	time.Sleep(duration)

	//shard.TestPropose()
	// master.CallFunction("words")
	//WaitForInterrupt()


	// Synchronous call

}
