/***********************************************************
File name : echo1.go
Author name : xiongyansong
Email address : sanxisui@gmail.com
Create time : 2023-03-16 16:39:48
Description:指针，非常非常非常有意思的点，go语言函数中可以返回局部变量的地址，c语言不能
			这样的而且*string类型，真的有这种东西吗，继续实验下。很神奇真的好神奇.
***********************************************************/
package main

import "fmt"

func return_fun_test3(p *int) int {
	*p++
	return *p
}

func return_fun_test() *int {
	c := 10
	return &c
}
func return_fun_test2() *string {
	b := "l am string"
	return &b
}

func main() {
	var (
		i int     = 10
		p *int    = &i
		s *string = return_fun_test2()
	)

	fmt.Println(i, *p)              //10
	fmt.Println(*return_fun_test()) //10
	fmt.Println(*s)                 //i am string

	fmt.Println(i, *p) //10
	fmt.Println(return_fun_test())
	fmt.Println(s)
	fmt.Println(return_fun_test3(&i))
}
