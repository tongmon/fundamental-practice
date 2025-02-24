package kr.tutorials.kotlinbasics

fun main() {
    println("Hello World")

    // var은 변할 수 있는 변수
    var name = "tongstar"
    println("Hello $name")
    name = "tongmon"
    println(name.uppercase())

    // val은 const와 같이 불변
    val number = 777
    println(number)

    var someUnicodeChar: Char = '\u00AE'
    println(someUnicodeChar)

    val bval: Boolean = true // or false
    if (bval) {
        println("bval is true!")
    } else {
        println("bval is false!")
    }

    val userInput = readln()
    var numInput = userInput.toInt()
    // 12 <= numInput && numInput <= 41 조건을 in 으로 줄일 수 있음
    if (numInput in 12..41) {
        println("Number: $numInput, Number belongs to the range of 12~41")
    } else {
        println("Number: $numInput")
    }

    val someNumber = (1..300).random()
    // switch 문이 코들린에서는 when이다.
    when (someNumber) {
        1 -> {
            println("This is one.")
        }

        2 -> {
            println("This is two.")
        }

        in 3..99 -> {
            println("Number is under 100")
        }

        else -> {
            println("This is two.")
        }
    }

    // 기존 switch랑 다른 점은 밑과 람다처럼 사용할 수 있음
    var someConditionResult = when {
        1 == 2 -> "Not a true"
        1 == 1 -> "This is true"
        else -> "This is not reachable"
    }

    var cnt = 3
    while (cnt >= 0) {
        cnt--
        println("Count: $cnt")
    }

    for (i in 1..3) {
        println("Count: $i")
    }

    val someAry: IntArray = intArrayOf(1, 2, 3, 4, 5)
    someAry.forEachIndexed { index, value ->
        println("the element at $index is $value")
    }

    for ((index, value) in someAry.withIndex()) {
        println("the element at $index is $value")
    }
}