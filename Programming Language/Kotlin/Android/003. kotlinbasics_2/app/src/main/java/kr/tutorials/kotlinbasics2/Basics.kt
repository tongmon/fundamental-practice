package kr.tutorials.kotlinbasics2

fun main() {
    SomeFunc(100)
    println(SomeFuncWithRet("Hello"))

    var someDog = Dog("tongstar")
    someDog.Bark("tongmon")
    println("someDog.name = ${someDog.name}")
}

fun SomeFunc(someArg: Int)
{
    println(someArg)
}

fun SomeFuncWithRet(someArg: String): String {
    return "$someArg Hi!"
}
