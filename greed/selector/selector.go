package main

import "fmt"

func dynamicSelector(start, finished []int) int {
	n := len(start)
	if n != len(finished) || n == 0 {
		return 0
	}
	start = append([]int{0}, start...)
	start = append(start, 0xffffffff)
	finished = append([]int{0}, finished...)
	finished = append(finished, 0xffffffff)

	counts := make([][]int, n+2)
	for i := 0; i < n+2; i++ {
		counts[i] = make([]int, n+2)
	}
	for j := 0; j <= n+1; j++ {
		for i := 0; i < j; i++ { //i < j
			maxTemp := 0
			for k := i + 1; k < j; k++ {
				if start[k] >= finished[i] && finished[k] <= start[j] {
					if counts[i][k]+counts[k][j]+1 > maxTemp {
						maxTemp = counts[i][k] + counts[k][j] + 1
					}
				}
			}
			counts[i][j] = maxTemp

		}
	}
	return counts[0][n+1]
}
func main() {
	Si := []int{1, 5}
	Fi := []int{4, 6}
	fmt.Println(dynamicSelector(Si, Fi))
}
