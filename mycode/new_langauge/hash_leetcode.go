/***********************************************************
File name : hash_leetcode.go
Author name : xiongyansong
Email address : sanxisui@gmail.com
Create time : 2023-03-22 15:42:14
Description : hash查找go语言版本,gg了
			  不想写了是一部分，另一部分是有那个切片好像比数组好使
			  2023-03-23 14:44:54又gg了
			  为什么数组不能a[i++]啊，真让人摸不着头脑
***********************************************************/
package main

//hash函数
func hash_func(value int) int {
	return value % 10
}

//hash查找

//插入hash表
func inster_hashelemrnt(numb int, hash_array []int) int {
	new_numb:=hash_func(numb)
	if hash_array[new_numb++] !=0 {
		hash_array[new_numb]=numb
	}else if hash_array[new_numb+1]!=0 {

	}
	return 0
}

func main() {
	var length_hash = [10]int{0}
	inster_hashelemrnt(5, length_hash[])

}
