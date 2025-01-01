/*
Multiple Line
Comment
*/

// Single Line Comment

// import, export는 기본적으로 html에 <script> 태그에 type="module"이 적혀있어야 작동함
// export 변수는 다른 파일에서 `import { some_exported_string } from './recap.js'`으로 포함하고 some_exported_string로 사용 가능
// 이름을 바꿔서 부를 수도 있는데 `import { some_exported_string as exported_str } from './recap.js'` 이렇게 as로 exported_str 이름으로 부를 수도 있음
export let some_exported_string = "hello js";

// 디폴트 export 변수는 파일마다 단 하나만 존재 가능
// 다른 파일에서 `import whatever_you_want from './recap.js'`으로 포함하고 whatever_you_want로 사용 가능
// 디폴트 변수라 whatever_you_want에는 원하는 변수 이름 아무거나 넣어도 상관없음
export default "hello this is default value";

// 여러 개의 export 변수들을 한 번에 가져오고 싶을 때가 있음
// 그런 경우는 `import { str_01, int_01 } from './recap.js'`으로 여러 개를 해줘도 됨
export let str_01 = "hello str";
export let int_01 = 777;

// 완전히 모든 것을 import 하고자 한다면 `import * as whatever_you_want from './recap.js'`로 포함할 수 있음
// whatever_you_want에는 원하는 이름 아무거나 넣어도 상관없음
// whatever_you_want.float_01 이렇게 객체마냥 사용이 가능함
// 디폴트 변수는 whatever_you_want.default가 됨
export let float_01 = 1.34;
export let ary_01 = [777, "hello"];

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

let some_ary = [1, 2, 3];
some_ary.push(4); // 뒤에 추가
some_ary.unshift(0); // 앞에 추가
let poped = some_ary.pop(); // 뒤에 하나 제거
let shifted = some_ary.shift(); // 앞에 하나 제거

// C++ unordered_map이랑 비스무리하지만 많이 다른 Js의 Object
let some_key = "final_key";
let user = {}; // {} === new Object()
let specific_user = {
  name: "gyungjoonlee",
  id: "tongstar",
  "favorite foods": ["curry", "ramen"], // 띄어쓰기 포함 단어도 key로 사용 가능
  [some_key]: 12345, // key를 동적으로 획득해서 사용가능
  obj: {
    name: "child object",
  },
  // 함수도 Object에 포함 가능
  some_function() {
    console.log("hello");
  },
};

specific_user.some_function();
delete specific_user.id; // property 삭제
console.log(specific_user["favorite foods"]); // property 참조

console.log(Object.keys(specific_user).length > 0); // 비어있는지 확인
console.log(specific_user.hasOwnProperty("favorite foods")); // 특정 키가 있는지 확인

// Object 순회
// key가 정수라면 정렬되어 오름차순으로 출력됨
// key가 정수가 아니라면 객체 key가 추가된 순서대로 출력됨
for (let key in specific_user)
  console.log("key: " + key + ", value: " + specific_user[key]);

// Object 복사
user = specific_user; // Object의 등호는 참조를 나타냄. 즉 user는 specific_user를 가리킬 뿐임

// 원시적인 복사는 이렇게 함
let clone = Object.assign({}, specific_user);

// 하지만 specific_user.obj는 Object 내의 Object이기에 복사가 안되고 참조를 유지함
console.log(clone.obj == specific_user.obj);

// 결과적으로 깊은 복사를 하기 위해선 모든 Object 형을 재귀적으로 찾아 복사해줘야 한다.
clone.obj = Object.assign({}, specific_user.obj);
console.log(clone.obj == specific_user.obj);

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
console.log(null === undefined); // false, 값은 같으나 자료형이 다름

// Logics
// C++과 다른 것만 정리함

// break, continue문은 C++과 동일하게 사용할 수도 있으나 밑과 같이 C++의 goto 처럼 사용 가능함.
point1: for (let i = 0; i < 3; i++) {
  point2: for (let j = 0; j < 4; j++) {
    if (my_name === "yellowjam") {
      continue point1;
    }
    if (my_name === "victoh") {
      break point2;
    }
  }
}

// C++ goto와 차이점이라면 밑과 같이 lable을 하단에 추가할 수 없음
/*
for (let j = 0; j < 4; j++) {
    if (my_name === "yellowjam") {
      continue point1;
    }
}
  
point1: console.log("Can't reach this point!"); // 이렇게 밑에 lable 추가는 못함
*/

// Switch문은 C++과 다르게 대부분의 자료형이 위치할 수 있음
let some_string = "this is js recap!";
switch (some_string) {
  case "this is c++ recap!":
    break;
  case "this is js recap!":
    break;
  default:
    break;
}

// function
// C++과 대부분은 같지만 인자에 자료형을 명시하지 않음
function showMessage(arg1, arg2 = "default text") {
  console.log(arg1 + " " + arg2);
  return arg1 + arg2;
}

let func_pt_in_js = showMessage; // 함수는 변수에 함수 포인터마냥 저장할 수 있음

// C++의 Functor 비스무리한 것은 밑과 같이 사용함
// 값 캡쳐는 따로 안써줘도 그냥 됨...
let capture1 = 3,
  capture2 = 4;
let lambda = (arg1, arg2) => {
  return arg1 + arg2 + capture1 + capture2;
};
console.log(lambda(1, 2));

// 배열에는 map(), filter(), reduce() 등의 함수가 있음
// 제일 자주쓰이는 map()은 순회하면서 각 배열의 인자 값을 변화시켜주는데 밑과 같이 사용함
let some_array = [1, 2, 3];
let mapped_array = some_array.map((x) => {
  x * 2;
}); // [2, 4, 6]
let mapped_array2 = some_array.map((x, index) => ({ index: x })); // [{0: 1}, {1: 2}, {2: 3}]

// 자바스크립트의 클래스
// 클래스 이름의 첫 글자는 무조건 대문자로 시작해야 함
class User {
  constructor(name) {
    this.name = name;
  }
  sayHi() {
    console.log(this.name);
  }
}

const user1 = new User("tongstar");
user1.sayHi();

// 배열의 원소를 각각 변수에 할당할 수 있음
// C++의 tie와 비슷한 기능
// first = 1, second = 2가 됨
const [first, second] = [1, 2];

// Object도 밑과 같이 동일하게 분할이 가능함
// 대신 프로퍼티 이름이 같아야 함
let { name, age } = { name: "tongstar", age: 27 };

// 스프레드 연산자
// 중첩된 배열, 객체 등을 풀어줄 때 사용함
const spread_arr1 = [1, 2, 3];
const spread_arr2 = [4, 5, 6];
const not_spread = [spread_arr1, spread_arr2]; // [[1, 2, 3], [4, 5, 6]]
const spread = [...spread_arr1, ...spread_arr2]; // [1, 2, 3, 4, 5, 6]

const spread_obj1 = { a: 1, b: 2 };
const original_obj = { ...spread_obj1, c: 3 }; // { a: 1, b: 2, c: 3 }

// JavaScript에서의 참조와 복사
// 밑과 같은 기본 자료형(string, number, boolean, null, undefined, symbol)은 복사임
const some_basic_value = 1;
let some_basic_value_2 = some_basic_value; // 복사

// 반면 객체는 참조임
// 참조가 발생하는 객체에는 해당 변수에 주소가 할당 되어있음
const some_copy_obj_1 = { a: 1 };
let some_copy_obj_2 = some_copy_obj_1; // 참조
const some_copy_ary_1 = [1, 2, 3];
some_copy_ary_1[0] = 100; // 객체이기에 some_copy_ary_1의 주소만 고정이 되어 있다면 그 외 다른 것들은 변경 가능
// 주소를 바꾸는 것이기에 const로 선언된 상태에서 밑과 같이는 안됨
// some_copy_ary_1 = [4, 5, 6];
