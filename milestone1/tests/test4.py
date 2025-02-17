# Test Case 4
def test_case_4():
     data: list[float] = [-2.3, 3.14, 0.9, 11, -9.1]


     def compute_min() -> float:
          min_value = None
          for i in range(len(data)):
               if not min_value:
                    min_value = data[i]
               elif data[i] < min_value:
                    min_value = data[i]
          return min_value


     def compute_avg() -> float:
          avg_value = None
          sum = 0
          for i in range(len(data)):
               sum += data[i]
          return sum / len(data)


     def main():
          min_value: float = compute_min()
          print("Minimum value: ")
          print(min_value)
          avg_value: float = compute_avg()
          print("Average value: ")
          print(avg_value)


if __name__ == "__main__":
     def test_break():
          # Break statement
          name = "Alice"
          for i in range(10):
               if name[i] == 'c':
                    break

def test_range_iteration():
    result = []
    for i in range(11):
        result.append(i)

test_case_4()
