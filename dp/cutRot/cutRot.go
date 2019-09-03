package main

import "fmt"

func MemoizedCutRotAux(p []int, n int, r []int) int {
	//是否计算过
	if r[n] >= 0 {
		return r[n]
	}
	if n == 0 {
		return 0
	}

	max := -1
	for i := 1; i <= n; i++ {
		q := cutRot(p, n-i) + p[i-1]
		if q > max {
			max = q
		}
	}
	r[n] = max
	return max
}

//带备忘的自顶向下过程参考代码,时间复杂度O（n2）
func MemoizedCutRod(p []int, n int) int {
	pLen := len(p)
	r := make([]int, pLen+1)
	for i := 0; i < pLen+1; i++ {
		r[i] = -1
	}
	return MemoizedCutRotAux(p, n, r)
}

func BootomUpCutRot(p []int, n int) int {
	pLen := len(p)
	//dp ，存储长度为i的最大效益值
	dp := make([]int, pLen+1)
	for i := 0; i < pLen+1; i++ {
		dp[i] = -1
	}
	dp[0] = 0
	for j := 1; j <= n; j++ {
		max := -1
		for i := 1; i <= j; i++ {
			tmp := p[i-1] + dp[j-i]
			if tmp > max {
				max = tmp
			}
		}
		dp[j] = max
	}
	return dp[n]
}
func cutRot(p []int, n int) int {
	if n == 0 {
		return 0
	}
	max := -1
	for i := 1; i <= n; i++ {
		q := cutRot(p, n-i) + p[i-1]
		if q > max {
			max = q
		}
	}
	return max
}
func main() {
	p := []int{1, 5, 8, 9, 10, 17, 17, 20, 24, 30}
	fmt.Println(cutRot(p, 7))
	fmt.Println(MemoizedCutRod(p, 7))
	fmt.Println(BootomUpCutRot(p, 7))
}
