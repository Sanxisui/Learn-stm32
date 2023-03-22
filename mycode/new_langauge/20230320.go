/***********************************************************
File name : echo1.go
Author name : xiongyansong
Email address : sanxisui@gmail.com
Create time : 2023-03-20 09:12:24
Drscription : 换了一家视频看，https://www.bilibili.com/video/BV1zR4y1t7Wj?p=11&vd_source=f775a528bd385a85fbc32763f1975fc8
			  感觉很可以！
***********************************************************/
package main

import "fmt"

// func test_1(p *int, s string) int {
// 	s = "hello"
// 	fmt.Printf("%s", *p)
// 	return 10
// }

func main() {
	// test_1,"world")
	//类似c中的枚举，有比这更好的用法
	// const (
	// 	a1 = iota //=0
	// 	a2 = iota //1
	// 	_S
	// 	a3 = iota //3
	// )
	// var name string = "name"
	// age := 10
	// b := true
	// fmt.Printf("%T\n", name) //%T打印数据的类型
	// fmt.Printf("%T\n", age)
	// fmt.Printf("%T", b)
	//数组
	a := [...]int{1, 2, 3}
	b := [...]string{1: "hello", 3: "world"}
	fmt.Printf("%s\n", b[3])
	//比较有意思的地方答应数组的首地址，然后答应出来了整个数组
	fmt.Printf("%d\n", a)
	// var c [5]int = {2, 5, 8, 9, 10}

}
