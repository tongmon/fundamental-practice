package kr.tutorials.kotlinbasics2

// 밑과 같이 자료만 들어있는 클래스도 생성이 가능하다.
// C++의 변수만 있는 구조체라고 보면 될 듯.
data class DataStructure(val someData1: String,
                         val someData2: Int)

fun main() {
    SomeFunc(100)
    println(SomeFuncWithRet("Hello"))

    val someDog = Dog("tongstar")
    someDog.Bark("tongmon")
    println("someDog.name = ${someDog.name}")

    var someData = DataStructure("Data 01", 100)
    
    // 고정 크기 배열은 밑과 같이 만듦
    val someList = listOf<Int>(1, 2, 3, 4, 5)

    // 동적 배열은 밑과 같음
    val someMutableList = mutableListOf<String>("hi", "hello", "bye", "farewell")
    someMutableList.add("good bye")
    someMutableList.remove("bye")
    println(someMutableList)

    val hasGoodBye = someMutableList.contains("good bye")
    if (hasGoodBye){
        for (item in someMutableList){
            println("$item\n")
        }
        for ((index, item) in someMutableList.withIndex()) {
            println("$item\n")
        }
        for (index in someMutableList.indices) {
            println("${someMutableList[index]}\n")
        }
        for (index in 0 until someMutableList.size){
            println("${someMutableList[index]}\n")
        }
    }
}

fun SomeFunc(someArg: Int)
{
    println(someArg)
}

fun SomeFuncWithRet(someArg: String): String {
    return "$someArg Hi!"
}
