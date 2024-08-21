# Test Case 5
def test_case_5():
     class ShiftReduceParser:

          def __init__(self, name_: str):
               self.srname: str = name_


     class LR0Parser(ShiftReduceParser):

          def __init__(self, myname_: str, parentname_: str):
               self.lr0name: str = myname_
               ShiftReduceParser.__init__(self, parentname_)


     class CLRParser(ShiftReduceParser):

          def __init__(self, myname_: str, parentname_: str):
               self.clrname: str = myname_
               ShiftReduceParser.__init__(self, parentname_)


     class LALRParser(CLRParser):

          def __init__(self, myname_: str, clrname_: str, srname_: str):
               self.lalrname: str = myname_
               CLRParser.__init__(self, clrname_, srname_)

          def print_name(self):
               print("SLR name:")
               print(self.srname)
               print("CLR name:")
               print(self.clrname)
               print("LALR name:")
               print(self.lalrname)


     def main():
          obj: LALRParser = LALRParser("LALR", "CLR", "Shift-Reduce")
          obj.print_name()

def count_down(start):
    while start > 0:
        print(start)
        start /= 2
    print("ho gaya kaam")


def fibo(n):
    if n <= 1:
        return n
    else:
        return fibo(n - 1) + fibo(n - 2)

if __name__ == "__main__":
     main()

test_case_5()