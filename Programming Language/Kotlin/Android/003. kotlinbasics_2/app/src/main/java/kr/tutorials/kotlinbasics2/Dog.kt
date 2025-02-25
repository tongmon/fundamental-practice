package kr.tutorials.kotlinbasics2

// 생성자 인자를 클래스 옆에다 적음
// class Dog (name: String) 그냥 이렇게 하면 name은 클래스 멤버 변수가 아님, 그저 생성자의 인자일 뿐임
// class Dog (var name: String) 이렇게 var를 달아주면 name은 멤버 변수가 됨, 따로 클래스 내부에 멤버 변수를 선언하지 않아도 되어 코드량을 줄일 수 있음
class Dog (var name: String){
    var someMemberVariable: Boolean = true
    private var somePrivateVariable: Int = 100 // private 변수

    // 생성자
    init {
        Bark(name)
    }

    fun Bark(name:String){
        println("$name: Woof Woof")
    }
}