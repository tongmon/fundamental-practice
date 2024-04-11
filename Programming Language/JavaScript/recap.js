/*
Multiple Line
Comment
*/

// Single Line Comment

// Variables
var a = 4;
var my_name = true;
var my_name = "tongstar"; // var는 중복 선언 가능

let b = 5; // let은 중복 선언 불가능

const c = 6; // const는 c++의 const와 동일

let unknown_empty_thing = null; // 알 수 없는, 텅 빈 값은 null로 정의

let not_init = undefined; // 초기화가 안된 상태는 undefined로 정의

let big_int =
  12334234324324588678123342343243245886781233423432432458867812334234324324588678n; // 아주 긴 숫자에 n을 붙이면 big int 자료형임

let inf = 1 / 0; // Infinity 값으로 바뀜
console.log(inf);

// Formatting
console.log("' is same " + 'with "'); // js에서는 "이거나 '이거나 같음
console.log(`My name is ${my_name}`); // `를 이용하면 fmt와 같은 표현 사용 가능

// Casting
let some_boolean = true;
some_boolean = String(some_boolean); // some_boolean은 이제 "true"가 됨
console.log(some_boolean);

let some_number = "123";
some_number = Number(some_number);
console.log("100" / "2"); // 이런 경우 자동으로 Number("100") / Number("2") 이렇게 변형됨

// Operator
// 대부분은 C++과 유사하나 다른 것들만 추려서 정리함
console.log(2 ** 3); // 2의 세제곱
console.log(2 + "3"); // 2 + "3"은 "23"이다. 문자열과 숫자를 더하면 무조건 문자열로 바뀜

let x = 100;
let y = null;
console.log(x ?? y); // x ?? y -> (x !== null && x !== undefined) ? x : y 와 같은 표현, 즉 x가 정의되어 있으면 x를 반환하고 아니면 y를 반환함

// Compare
console.log(1 == "1"); // true, "1"은 숫자로 자동으로 변환되어 평가됨
console.log(1 === "1"); // false, ===는 타입까지 검사함

// false, false, false, true, true, null은 <=, >=에만 true로 반응함...
// 굳이 이렇게 사용할 필요도 없고 알 필요도 없음
console.log(
  (null > 0) +
    " " +
    (null < 0) +
    " " +
    (null == 0) +
    " " +
    (null <= 0) +
    " " +
    (null >= 0)
);

console.log(null == undefined); // true, undefined는 null 이외의 값과 모든 비교 연산자에 false를 반환함
console.log(null == undefined); // false, 값은 같으나 자료형이 다름

// Logics
if (!a) {
  console.log(a + " is zero");
} else if (my_name == "tongstar") {
  console.log("My name is " + my_name);
} else {
  console.log("Nothing right");
}
