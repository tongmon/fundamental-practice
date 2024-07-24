""" 
Mutlple line
Comment
"""

# Single Line Comment

from builtins import print


# function
def some_func(a=1, b=2):
    return a + b


# function that don't know how many argument will be needed, You should add the asterisk in front of the arg name.
def many_arg_func(*many_arg):
    for arg in many_arg:
        print(arg)


many_arg_func("My", " Age is", 27)


# You can write nothing on function (or for, while loop) with `pass` keyword
def do_nothing_func():
    pass


# string
my_name = "tongstar"
my_name.upper()
my_name.startswith("tong")

# formatting
print(f"My name is {my_name}, Upper name is {my_name.lower()}")
print(f"One plus Two is {some_func()}")

# casting
my_age = int("27")

str_to_list = list("tongstar")  # str_to_list == ['t', 'o', 'n', 'g', 's', 't', 'a', 'r']

while my_age:
    print(my_age)
    my_age -= 1

if not my_age:
    print("My age decrease to zero")
elif my_name == "yellowjam" or my_name == "victoh":
    print("My name is not tongstar")
else:
    print("There is nothing right")

# list
colors = ["yellow", "blue", "pink", "red", "BLUE".lower(), "white"]

print("blue" in colors)  # true
print("red" not in colors)  # false
print(f"Color {colors[1]} is counted {colors.count(colors[1])} times")
colors.reverse()
colors.append("black")
colors.remove("blue")
del colors[1]
colors.clear()

# nested list
table = ["some text", [1, 2, 3, [True, False]], (10.1, 7.77)]
print(table[1][3][0])
table.append(["text 1", "text 2"])

# tuple == const list
days = ("Mon", "Tue", "Wed")
for day in days:
    print(day)

# set
"""
Not ordered, can contain various type.
Similar with C++'s unordered_set structure.
You can use issubset(), issuperset() for checking some element is in the set or not.
"""
some_set = {"some", "set", True, 1}

# dictionary
some_obj = {
    "id": "tongstar",
    "pw": "secret1997",
    "age": 27,
    "wife": {"id": "cukamon", "age": 26},
}
print(some_obj.get("id"))
print(some_obj["wife"]["id"])
some_obj["emails"] = ["tongstar@nate.com", "tongmon@hanmail.net"]
some_obj.pop("age")

for k in some_obj:
    print(k)  # key
    print(some_obj[k])  # value

# slicing, [ start : end : step ]
datas = ["a", "b", "c", "d", "e"]
print(datas[0:])  # datas[0:] == datas[0], datas[1], datas[2], datas[3], datas[4]
print(datas[1:2])  # datas[1:2] == datas[1], datas[2]
print(datas[:3])  # datas[:3] == datas[0], datas[1], datas[2], datas[3]
print(
    datas[3:0:-1]
)  # datas[3:0:-1] == datas[3], datas[2], datas[1], datas[0], decrease index by -1
print(datas[::2])  # datas[::2] == datas[0], datas[2], datas[4], increase index by 2

# You can use slicing when you put the value in list structure
datas[1:4] = ["this", "love"]  # datas == ["a", "this", "love", "e"] / replaced ["b", "c", "d"] part to ["this", "love"]

# split
split_text = "a b c d e".split()  # default separtor is space
print(split_text)
split_text = "a..b..c..d..e".split("..")
print(split_text)
split_text = "a-b-c-d-e".split("-", 2)  # you can set the max split count
print(split_text)


# parent class
# Every member function should have self arg
class Car:
    type = ""  # same as C++'s static member variable

    # initiator
    def __init__(self, id, price):
        self.id = id  # You can add local member variable in initializer
        self.price = price

    # Same with c++'s [ std::ostream& operator << (std::ostream &out, ...) ]
    # You can print Car object through print() function after declaring this function.
    def __str__(self):
        return f"{self.id}'s type is {self.type}, price: {self.price}"

    # Operator Overloading
    # You can use '+' operator between Cars after declaring this function.
    def __add__(self, other):
        self.id = self.id + "_" + other.id
        self.price = (self.price + other.price) * 0.7
        self.type = self.type + "_" + other.type + "_hybrid"
        return self

    # Same with c++'s virtual function
    def drive(self):
        pass

    def blow_the_horn(self):
        print("default horn sound!")


# child class
class ElectricCar(Car):
    manufacturer = ""

    # Can access parent class with super keyword
    def __init__(self, id, price, manufacturer):
        super().__init__(id, price)
        self.type = "electric"
        self.manufacturer = manufacturer

    def blow_the_horn(self):
        print("electric horn sound!")

    # cls variable point that this is a static class method.
    # This function apply to the class, not the object. (same with C++'s static class function)
    @classmethod
    def some_static_func(cls, val):
        print("manufacturer: " + cls.manufacturer, " val: " + val)

    """
    staticmethod function can be used as class static function or local function.
    If you call this function like `ElectricCar.some_static_or_local_func()` this, 
    then It will be executed like static class function. 
    `electric_car.some_static_or_local_func()`, then It will be executed like normal function.
    """
    @staticmethod
    def some_static_or_local_func(val):
        print("val: " + val)


tesla_car = ElectricCar("Model S", 200, "tesla")
print(tesla_car)
super(ElectricCar, tesla_car).blow_the_horn()  # super() can use like c++'s dynamic_cast
tesla_car.blow_the_horn()

ElectricCar("Model S", 200, "tesla").some_static_func("some var")  # static function
ElectricCar("Model S", 200, "tesla").some_static_or_local_func("some var")  # static function
tesla_car.some_static_or_local_func("some var")  # normal function


# multiple inheritance
class Cpu:
    calculation_speed = 0

    def __init__(self):
        pass

    def process(self):
        print(f"Calculate something with {self.calculation_speed} speed!")


class Ram:
    storage_size = 0

    def __init__(self):
        pass

    def process(self):
        print(f"Store something volatility in ram that has {self.storage_size} size!")


class Computer(Cpu, Ram):

    def __init__(self):
        super().__init__()


computer = Computer()
computer.process()  # because of the order of inheritance, Cpu's function will operates.


# Overloading feature is not supported in python.
# If you want to use overloading feature on python, you can use `multipledispatch` library
class AddObj:
    def add(self, a, b):
        return a + b

    def add(self, a, b, c=3):
        return a + b + c


add_obj = AddObj()
print(add_obj.add(1, 2))  # Second add() function will be called, Because python not support overloading
