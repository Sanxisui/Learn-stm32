/***********************************************************
File name : echo1.go
Author name : xiongyansong
Email address : sanxisui@gmail.com
Create time : 2023-03-21 14:39:21
Description : 《少年狂想录》是真的好听啊
			   bool类型
***********************************************************/
package main

import "fmt"

func main() {
	// s := [...]string{"string"}
	// fmt.Printf("s[1]%s\n", s)
	// // b := []int{122, 333}
	// var b bool = false
	// c := true
	// if c == false {
	// 	fmt.Printf("b:%v\n", b)
	// }
	// fmt.Printf("c: %v\n", c)
	age := 18
	s := age > 17
	fmt.Printf("s: %v\n", s)
	if s == false {
		fmt.Printf("age: %v\n", age)
	}
	count := 10
	for i := 0; i < count; i++ {
		fmt.Printf("i: %v\n", i)
		if i == count {
			fmt.Printf("i: %v\n", i)
		}
	}

}
