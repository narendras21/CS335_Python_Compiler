def binarySearch(array: list[int], x: int, low: int, high: int) -> int:
  while low <= high:
    mid: int = low + (high - low) // 2
    if array[mid] == x:
      return mid
    elif array[mid] < x:
      low = mid + 1
    else:
      high = mid - 1
  return -1


def binarySearch(array: list[float], x: int, low: int, high: int) -> int:
  while low <= high:
    mid: int = low + (high - low) // 2
    if array[mid] == x:
      return mid
    elif array[mid] < x:
      low = mid + 1
    else:
      high = mid - 1
  return -1


def main():
    
    #static polymorphism tested
    array1:list[int] = [3, 4, 5, 6, 7, 8, 9]
    result1:int = binarySearch(array1, 4, 0, 5)
    print(result1)

    array2:list[float] = [3.0, 4.4, 5.6, 6.3, 2.7, 3.38, 8.9]
    result2:int = binarySearch(array2, 4, 0, 5)
    print(result2)


if __name__ == "__main__":
  main()
