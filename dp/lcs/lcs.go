package main

import (
	"fmt"
	"math/rand"
)

//暴力法
func lcs(s1, s2 string) string {
	return string(lcs1Help(s1, s2))
}
func lcs1Help(s1, s2 string) []byte {
	m := len(s1)
	n := len(s2)
	if m == 0 || n == 0 {
		return []byte{}
	}
	if s1[m-1] == s2[n-1] {
		str := lcs1Help(s1[:m-1], s2[:n-1])
		return append(str, s1[m-1])
	} else {
		str1 := lcs1Help(s1[:m-1], s2[:n])
		str2 := lcs1Help(s1[:m], s2[:n-1])
		if len(str1) > len(str2) {
			return str1
		} else {
			return str2
		}
	}
}
func MemoizedLcsAux(s1, s2 string, i, j int, dp [][][]byte) []byte {
	if dp[i][j] == nil {
		dp[i][j] = make([]byte, 0)
		if i == 0 && j == 0 {
			return dp[i][j]
		} else if i == 0 {
			dp[i][j] = MemoizedLcsAux(s1, s2, i, j-1, dp)
		} else if j == 0 {
			dp[i][j] = MemoizedLcsAux(s1, s2, i-1, j, dp)
		} else {
			if s1[i-1] == s2[j-1] {
				dp[i][j] = append(MemoizedLcsAux(s1, s2, i-1, j-1, dp), s1[i-1])
			} else {
				str1 := MemoizedLcsAux(s1, s2, i-1, j, dp)
				str2 := MemoizedLcsAux(s1, s2, i, j-1, dp)
				if len(str1) > len(str2) {
					dp[i][j] = str1
				} else {
					dp[i][j] = str2
				}
			}
		}
	}
	return dp[i][j]
}
func MemoizedLcs(s1, s2 string) string {
	m := len(s1)
	n := len(s2)
	dp := make([][][]byte, m+1)
	for i := 0; i <= m; i++ {
		dp[i] = make([][]byte, n+1)
	}
	return string(MemoizedLcsAux(s1, s2, m, n, dp))
}

func BootomUpLcs(s1, s2 string) string {
	m := len(s1)
	n := len(s2)
	dp := make([][][]byte, m+1)
	for i := 0; i <= m; i++ {
		dp[i] = make([][]byte, n+1)
	}
	for i := 0; i <= m; i++ {
		dp[i][0] = []byte{}
	}
	for j := 0; j <= n; j++ {
		dp[0][j] = []byte{}
	}
	max := -1
	ri := 0
	rj := 0

	for i := 1; i <= m; i++ {
		for j := 1; j <= n; j++ {
			if s1[i-1] == s2[j-1] {
				dp[i][j] = append(dp[i-1][j-1], s1[i-1])
			} else if len(dp[i-1][j]) >= len(dp[i][j-1]) {
				dp[i][j] = dp[i-1][j]
			} else {
				dp[i][j] = dp[i][j-1]
			}
			if len(dp[i][j]) > max {
				max = len(dp[i][j])
				ri = i
				rj = j

			}
		}
	}
	return string(dp[ri][rj])
}
func RandStringBytesRmndr(n int) string {
	letterBytes := "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
	b := make([]byte, n)
	for i := range b {
		b[i] = letterBytes[rand.Int63()%int64(len(letterBytes))]
	}
	return string(b)
}

func main() {
	s1 := RandStringBytesRmndr(100)
	s2 := RandStringBytesRmndr(20)
	fmt.Println(lcs(s1, s2))
	fmt.Println(MemoizedLcs(s1, s2))
	fmt.Println(BootomUpLcs(s1, s2))
}
