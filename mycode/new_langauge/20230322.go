/***********************************************************
File name : echo1.go
Author name : xiongyansong
Email address : sanxisui@gmail.com
Create time : 2023-03-21 14:39:21
Description : string类型以及，string加法
***********************************************************/
package main

import (
	"fmt"
	"strconv"
)

func main() {
	s := "hello"
	b := "world熊"
	// r := []rune(b)
	//计算字符串长度
	fmt.Printf("s: %v\n", len(s))
	fmt.Printf("r: %v\n", len(b))
	//便利字符串以及解决有中文的问题，
	// for i := 0; i < len(b); i++ {
	// 	fmt.Printf("b: %c\n", r[i])
	// }
	//将字符串转换为数字
	n, err := strconv.Atoi("123")
	if err != nil {
		fmt.Println("转换错误", err)
	} else {
		fmt.Println("转成的结果是：", n)
	}
	fmt.Printf("n: %v\n", n)
	fmt.Printf("err: %v\n", err)
	//将整数转化为字符串
	str := strconv.Itoa(13)
	fmt.Printf("str: %s\n", str)
	//字符串转切片
	qie := []byte("hello world")
	fmt.Printf("qie: %v\n", qie)
}
