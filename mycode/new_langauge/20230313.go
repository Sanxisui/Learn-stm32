/***********************************************************
File name : echo1.go
Author name : xiongyansong
Email address : sanxisui@gmail.com
Create time : 2023-03-13 20:59:36
Description:Use of the variables in the languages
            2023-03-15 10:28:11
***********************************************************/
package main

import "fmt"

func main() {
	// var c string
	// b := "hello"
	// a := 7
	// fmt.Println(a)
	// fmt.Printf("%s\n", b)
	// fmt.Printf(c)
	var (
		a int    = 10
		b string = "name"
		c int    = -1
		// d string = 's'
		e struct {
			f float32
		}
	)
	fmt.Println(a, b, c)
	fmt.Printf("a:%d,b:%s,c:%d\n", a, b, c)
	// fmt.Printf("a:%c", d)
}
