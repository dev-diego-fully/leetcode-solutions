func isPalindrome(x int) bool {
	if x < 0 {
		return false
	}

	digits := getDigits(x)
	digitsCount := len(digits)

	for i := 0; i < digitsCount-1; i++ {
		if digits[i] != digits[digitsCount-i-1] {
			return false
		}
	}

	return true
}

func getDigits(number int) []int {
	digits := []int{}

	for current := number; current > 0; current /= 10 {
		digits = append(digits, current%10)
	}

	return digits
}
