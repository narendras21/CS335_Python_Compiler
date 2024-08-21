# Test Case 2
def test_case_2():
     # Class definition
     class Animal:
          def __init__(self, species):
               self.species = species

          def display_species(self):
               print("Species:", self.species)


     class Dog(Animal):
          def __init__(self, species, name):
               super().__init__(species)
               self.name = name

          def bark(self):
               print("Woof! My name is", self.name)


# Function declaration
def count_down(start):
     while start > 0:
          print(start)
          start -= 1
     print("Blast off!")


# Main part
if __name__ == "__main__":
     print("Welcome to the animal world!")
     # Object instantiation
     animal = Animal("Canine")
     animal.display_species()

     # Object instantiation
     my_dog = Dog("Canine", "Max")
     my_dog.display_species()
     my_dog.bark()

     # Function call
     count_down(5)

def test_logical_operators():
# Logical operators
     
     result_or = True or False
     if not result_or:
          print("OR operation failed")
     result_and = True and True
     if not result_and:
          print("AND operation failed")

     result_not = not False
     if not result_not:
          print("NOT operation failed")

print("End of the program.")

test_case_2()

def test_if_else():
    # If-else control flow
    x = 250
    if x > 0:
        result = "Strictly Positive"
    elif x == 0:
        result = "Zero"
    else:
        result = "I don't know"