class Klass:
    def type(x:int):
        print("this is int")


class SubKlass(Klass):
    def type(y:float):
      print("this is float")

    def type(s:str):
      print("this is string")


def main():
    a:Klass
    b:SubKlass

    a.type(10)
    b.type(9)  #method inherited
    b.type(5.4)

    # a.type("asdkjfjj")    #should give error
    # b.type("alsjksdjfj")  #will work


if __name__ == "__main__":
  main()
