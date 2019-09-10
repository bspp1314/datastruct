package main

import "fmt"

type ListNode struct {
	Val  int
	Next *ListNode
}

func sortList(head *ListNode) *ListNode {
	return sortListHelp(head, nil)
}

func sortListHelp(head *ListNode, tail *ListNode) *ListNode {
	if head == tail || head.Next == nil || head.Next == nil {
		return head
	}
	i := head
	j := head.Next
	for j != tail {
		if j.Val <= head.Val {
			i = i.Next
			i.Val, j.Val = j.Val, i.Val
		}
		j = j.Next
	}
	head.Val, i.Val = i.Val, head.Val
	sortListHelp(head, i)
	if i != nil {
		sortListHelp(i.Next, nil)
	}
	return head
}
func printList(head *ListNode, tail *ListNode) {
	for head != tail {
		if head == nil {
			break
		}
		fmt.Printf(" %d ", head.Val)
		head = head.Next
	}
}
func partition(array []int, p, q int) {
	x := array[p]
	i := p
	for j := p + 1; j < q; j++ {
		if array[j] <= x {
			i = i + 1
			array[i], array[j] = array[j], array[i]
		}
	}
	array[i], array[p] = array[p], array[i]
}
func arrayToList(array []int) *ListNode {
	if len(array) == 0 {
		return nil
	}
	head := &ListNode{Val: array[0]}
	curr := head
	for i := 1; i < len(array); i++ {
		curr.Next = &ListNode{Val: array[i]}
		curr = curr.Next
	}
	return head
}
func main() {
	array := []int{6, 5, 2, 3, 5, 7, 8, -3, 10, 4}

	head := arrayToList(array)
	sortList(head)
	printList(head, nil)
	//head, mid := sortListHelp(head)
	//printList(head, nil)
	//printList(mid)
}
