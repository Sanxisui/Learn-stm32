/***********************************************************
File name : echo1.go
Author name : xiongyansong
Email address : sanxisui@gmail.com
Create time : 2023-03-10 09:12:35
***********************************************************/
package main

import (
	"fmt"
	"os"
)

func main() {
	var s, sep string
	for i := 1; i < len(os.Args); i++ {
		s += sep + os.Args[i]
		sep = ""
	}
	fmt.Println(s)
}
