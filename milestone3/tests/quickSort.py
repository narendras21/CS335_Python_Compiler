# Python program for implementation of Quicksort Sort

# Function to find the partition position
def partition(array:list[int], low:int, high:int)->int:
	# choose the rightmost element as pivot
	pivot = array[high]

	i = low - 1
	# compare each element with pivot
	for j in range(low, high):
		if array[j] <= pivot:
			i = i + 1
            x:int = array[i]
            array[i] = array[j]
            array[j] = x
	# Swap the pivot element with the greater element specified by i
    x:int = array[i + 1]
    array[i + 1] = array[high]
    array[high] = x
	# Return the position from where partition is done
	return i + 1

# function to perform quicksort


def quickSort(array:list[int], low:int, high:int)->list[int]:
	if low < high:
		pi = partition(array, low, high)
		# Recursive call on the left of pivot
		arr1:list[int] = quickSort(array, low, pi - 1)
		# Recursive call on the right of pivot
		array = quickSort(arr1, pi + 1, high)
	
    return array

def main():
    data = [1, 7, 4, 1, 10, 9, -2]
   
    for i in range(0, 7):
        print(data[i])

    sortData:list[int] = quickSort(data, 0, 6)

    for i in range(0, 7):
        print(sortData[i])

e call on the left of pivot
		arr1:list[int] = quickSort(array, low, pi - 1)
		# Recursive call on the right of pivot
		array = quickSort(arr1, pi + 1, high)
	
    return array

def main():
    data = [1, 7, 4, 1, 10, 9, -2]
   
    for i in range(0, 7):
        print(data[i])

    sortData:list[int] = quickSort(data, 0, 6)

    for i in range(0, 7):
        print(sortData[i])

