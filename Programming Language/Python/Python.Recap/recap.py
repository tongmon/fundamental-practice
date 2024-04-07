""" 
Mutlple line
Comment
"""

# Single Line Comment

from builtins import print


# function
def some_func(a=1, b=2):
    return a + b


# You can write nothing on function with pass keyword
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
print(f"Color {colors[1]} is counted {colors.count(colors[1])} times")
colors.reverse()
colors.append("black")
colors.remove("blue")
colors.clear()

# nested list
table = ["some text", [1, 2, 3, [True, False]], (10.1, 7.77)]
print(table[1][3][0])
table.append(["text 1", "text 2"])

# tuple == const list
days = ("Mon", "Tue", "Wed")
for day in days:
    print(day)

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

# slicing, [ start : end : step ]
datas = ["a", "b", "c", "d", "e"]
print(datas[0:])  # datas[0:] == datas[0], datas[1], datas[2], datas[3], datas[4]
print(datas[1:2])  # datas[1:2] == datas[1], datas[2]
print(datas[:3])  # datas[:3] == datas[0], datas[1], datas[2], datas[3]
print(
    datas[3:0:-1]
)  # datas[3:0:-1] == datas[3], datas[2], datas[1], datas[0], decrease index by -1
print(datas[::2])  # datas[::2] == datas[0], datas[2], datas[4], increase index by 2

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
    id = ""
    price = 0
    type = ""

    # initiator
    def __init__(self, id, price):
        self.id = id
        self.price = price

    # Same with c++'s [ std::ostream& operator << (std::ostream &out, ...) ]
    def __str__(
        self,
    ):
        return f"{self.id}'s type is {self.type}, price: {self.price}"

    # Same with c++'s virtual function
    def drive():
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


tesla_car = ElectricCar("Model S", 200, "tesla")
print(tesla_car)
super(ElectricCar, tesla_car).blow_the_horn()  # super() can use like c++'s dynamic_cast
tesla_car.blow_the_horn()
