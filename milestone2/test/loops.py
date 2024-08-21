def main():

    x:int = 0

    while( x<20):
       x = x+1
       print(x)
       
       if(x==15):
          break
    
    for i in range(0,10,1):
       for j in range(0,10,2):
          x = i + j

          if(x == 10):
            break




if __name__ == "__main__":
  main()
