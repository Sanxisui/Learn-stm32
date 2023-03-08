/***********************************************************
File name : test.go
Author name : xiongyansong
Email address : sanxisui@gmail.com
Create time : 2023-03-10 09:31:24
***********************************************************/
package main

import (
	"fmt"
)

func main() {
	var a, i int
	for a < 13 {
		for i = 1; i < 10; i++ {
			fmt.Println(i)
			a++
		}
	}
}
