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
    // 밑과 같이 참조 말고 특정 원소만 변경하여 복사를 수행할 수 있다.
    var otherData = someData.copy(someData2 = 200)
    
    // 고정 크기 배열은 밑과 같이 만듦
    val someList = listOf<Int>(1, 2, 3)

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

    // 밑과 같이 js에서 배열을 순회하는 map 함수가 코틀린에도 존재한다.
    // doubled는 2, 4, 6이 될 것이다.
    val doubled = someList.map { it * 2 }

    // String? 이렇게 뒤에 '?'가 붙으면 nullable 자료형이 된다.
    // null이거나 String이거나 둘 중 하나라는 것이다.
    var name: String? = "Ella"
    // let으로 블록을 지정하여 불필요한 변수 선언을 피할 수 있다.
    // it 변수는 원본 객체의 복사본이다.
    // let 블록 내의 마지막 라인은 let 블록의 return 값이 된다.
    var letRet = name?.let {
        println(it.uppercase())
        "This is \"let\" block!"
    }
    // letRet은 "This is "let" block!"가 된다.
    println(letRet)
}

fun SomeFunc(someArg: Int)
{
    println(someArg)
}

fun SomeFuncWithRet(someArg: String): String {
    return "$someArg Hi!"
}
