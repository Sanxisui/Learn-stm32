/***********************************************************
File name : echo1.go
Author name : xiongyansong
Email address : sanxisui@gmail.com
Create time : 2023-03-16 09:51:50
Description:Use of the variables in the languages
			change variables i and j
***********************************************************/
// package main

// import "fmt"

// const boilingF = 212.0

// func main() {
// 	var (
// 		f = boilingF
// 		c = (f - 32) * 5 / 9
// 	)
// 	fmt.Printf("%g %g", f, c)
// }
// package main

// import "fmt"

// func main() {
// 	var i, j, k int
// 	/*注意逗号的位置隔开定义以及赋值*/
// 	var s, d, f = true, 3.2, "three"
// 	/*bool类型用%t打印，%b打印的是二进制的整数*/
// 	fmt.Printf("%d %d %d %t %f %s", i, j, k, s, d, f)
// }
package main

import "fmt"

func main() {
	//声明变量有超多方式,如果局部变量在函数内，直接:=声明加赋值就好很多，但是还是想看看编码标准
	i, j := 3, 7
	//很有意思的交换变量的值
	i, j = j, i
	fmt.Printf("%d %d", i, j)
}
