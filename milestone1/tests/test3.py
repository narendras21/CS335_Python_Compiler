# Test Case 3
def test_case_3():
     def bubbleSort(array) -> None:
          for i in range(len(array)):
               swapped: bool = False
               for j in range(0, len(array) - i - 1):
                    if array[j] > array[j + 1]:
                         temp = array[j]
                         array[j] = array[j + 1]
                         array[j + 1] = temp
                         swapped = True
               if not swapped:
                    break


     def main():
          data: list[int] = [-2, 45, 0, 11, -9]
          bubbleSort(data)

          print('Sorted Array in Ascending Order:')
          for i in range(len(data)):
               print(data[i])


     if __name__ == "__main__":
          result_bitwise_and = 15 & 33
          if result_bitwise_and == 34:
               print("Bitwise AND failed")

          result_bitwise_complement = ~5
          if result_bitwise_complement != -6:
               print("Bitwise complement failed")
               
          result_bitwise_or = 4 | 3
          if result_bitwise_or == 7:
               print("Bitwise OR failed")

          result_bitwise_xor = 6 ^ 3
          if result_bitwise_xor != 6:
               print("Bitwise XOR failed")

          result_right_shift = 5 >> 1
          if result_right_shift != 10:
               print("Right shift failed")
          

          result_left_shift = 5 << 1
          if result_left_shift != 10:
               print("Left shift failed")


test_case_3()