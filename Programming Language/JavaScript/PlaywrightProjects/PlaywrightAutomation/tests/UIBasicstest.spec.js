// 프로젝트에 playwright을 설치하려면 밑의 명령어를 수행한다.
// npm init playwright@latest
//
// playwright을 수행하는 경우 playwright 전용 browser를 이용하는 것이 좋다. 밑 명령어로 playwright browser를 설치한다.
// npx playwright install
//
// playwright 프로젝트 수행을 위해선 밑과 같은 명령어들을 사용할 수 있다.
// npx playwright test -> playwright.config.js를 찾아 해당 파일에서 지시한대로 테스트 수행
// npx playwright test --project=chromium -> chromium으로 테스트 수행
// npx playwright test tests/UIBasicstest.spec.js // 특정 파일을 지정해 테스트 수행, 나머지 설정은 playwright.config.js에 지정된 대로 가져감
// npx playwright test --debug -> 디버그 모드로 테스트 수행
// npx playwright test --ui -> UI 모드로 테스트 수행
//
// 모든 테스트는 headless 방식으로 진행되기 때문에 별도의 명령어가 없다면 브라우저가 보이지 않음
// npx playwright test --headed
// 위와 같이 headed 옵션을 달아줘야 실제로 브라우저 진행 상황이 보임, 혹은 playwright.config.js의 headless 옵션을 이용
//
// 리포트 결과를 보는 명령어는 밑과 같다.
// npx playwright show-report
//
// playright은 codegen 기능도 제공한다.
// npx playwright codegen [특정 링크] 명령어로 사용할 수 있다.
// 해당 명령어를 치면 특정 링크로 접속한 상태의 브라우저가 뜨는데 여기서 자기가 원하는 행위를 하면 codegen 출력창에 playwright 코드가 쓰여진다.

// test와 expect 키워드를 이용하기 위해 선언함
// request는 Web Api 테스트를 위해 필요하다.
const { test, expect, request } = require("@playwright/test");
const ExcelJs = require("exceljs");

import { resolve } from "path";
import { APIUtil } from "./utilities/APIUtil";
//import { ExcelJs } from "exceljs";

// browser를 넘기는 경우는 무조건 {}로 감싸야 playwright의 browser로 인식한다.
// 그리고 함수를 전달할 때 async로 전달해야만 await가 의미있다.
test("First Playwright test", async ({ browser }) => {
  // 쿠키나 예전에 깔았던 크로니움 기반 확장들을 모두 날린 상태의 순수한 세션을 만듦
  // 순수한 세션을 만들고 이용하여 속도를 높이는 효과도 있음
  // 생성되는 브라우저의 종류는 playwright.config.js에서 설정가능
  const context = await browser.newContext();

  // 새로운 탭 생성
  const page = await context.newPage();

  // 특정 링크로 이동
  await page.goto("https://google.com/");
});

// browser 말고 page를 넘기면
// const context = await browser.newContext();
// const page = await context.newPage();
// 위 코드를 생략할 수 있음
// { browser, page }에서 browser가 필요없다면 { page } 이렇게 넘겨도 됨
test("Second Playwright test", async ({ browser, page }) => {
  await page.goto("https://playwright.dev/");

  // 해당 페이지 타이틀 획득
  console.log(await page.title());

  // expect는 테스트를 하기 위한 주요 함수다.
  // toHaveTitle: 특정 페이지의 타이틀을 비교하여 똑같으면 테스트 패스, 아니면 실패로 간주함
  await expect(page).toHaveTitle(
    "Fast and reliable end-to-end testing for modern web apps | Playwright"
  );
});

// test.only를 이용하면 해당 테스트는 수행되지만 나머지 정의된 모든 테스트는 스킵된다.
// test.only("Skip all the tests below this test", async ({ browser, page }) => {
//   await page.goto("https://naver.com/");
// });

test("Third Playwright test", async ({ page }) => {
  await page.goto("https://rahulshettyacademy.com/loginpagePractise/");

  // locator는 웹 페이지의 특정 UI를 찾는 곳에 쓰임
  // locator를 통해 특정 UI를 찾는 방법에는 4가지가 있음
  //
  // 1. ID가 주어진 경우
  // tagname#id 혹은 #id (ex.input#username)
  //
  // 2. 클래스가 주어진 경우
  // tagname.class 혹은.class (ex.input.form-control)
  //
  // 3. Css Attribute를 통해 찾는 경우
  // 해당 방식의 장점은 정규식 사용이 가능하다는 것이다.
  // 자세한 내용은 https://developer.mozilla.org/ko/docs/Learn/CSS/Building_blocks/Selectors/Attribute_selectors 참조
  // tagname[attribute = 'value'] 혹은 [attribute = 'value'] (ex. [name = 'username'])
  //
  // 4. Css 부모 자식 관계를 통해 찾는 경우 (>> 혹은 공백 둘 다 가능)
  // parent_tagname >> child_tagname (ex.form >> div >> input)
  //
  // SelectorsHub라는 브라우저 확장앱을 설치하면 더 편하다.
  await page.locator("#username").fill("tongstar"); // fill 함수로 input UI를 채움
  await page.locator("[type='password']").fill("my password");
  await page.locator("#signInBtn").click(); // 특정 버튼 클릭

  const alertText = await page.locator("[style*='block']");

  // 텍스트 추출, textContent 함수는 화면 렌더링이 되어 해당 CSS 요소를 획득할 때까지 기다려줌
  console.log(await alertText.textContent());

  await expect(alertText).toContainText("Incorrect"); // Incorrect 텍스트를 획득하는지 확인
});

test("Fourth Playwright test", async ({ page }) => {
  await page.goto("https://rahulshettyacademy.com/loginpagePractise/");

  const idInput = page.locator("#username");
  const pwInput = page.locator("[type='password']");
  const signInBtn = page.locator("#signInBtn");

  await idInput.fill("rahulshettyacademy"); // fill 함수로 input UI를 채움
  await pwInput.fill("learning");
  await signInBtn.click(); // 특정 버튼 클릭

  const cardInfo = await page.locator(".card-body a");

  // locator가 탐색하여 찾은 element가 여럿인 경우 nth(index)를 이용하면 된다.
  console.log(await cardInfo.nth(0).textContent());

  // 밑도 nth(0)과 같은 기능을 수행함
  // console.log(await cardInfo.first().textContent());

  // waitForLoadState() 함수는 특정 네트워크 상황에 도달할 때까지 기다리게 만든다.
  // networkidle 상태는 모든 network call이 마무리되고 idle 상태인 경우를 의미한다.
  // 하지만 브라우저에 따라 실패하는 경우도 있다.
  await page.waitForLoadState("networkidle");

  // waitFor() 함수는 해당 요소가 로딩이 완전히 될 때까지 기다려준다.
  // waitFor()는 locator()가 가리킨 곳에 단 하나의 요소만 존재하는 경우 이용할 수 있다.
  // 따라서 first(), last() 등으로 하나의 요소로 만든 후에 사용해야 한다.
  await cardInfo.last().waitFor();

  // allTextContents를 통해 전체 텍스트를 획득함
  // allTextContents 함수는 화면 렌더링이 완료되는 시점까지 기다려주지 않기에 실제로는 값이 존재하지만 빈 배열을 반환해버리는 경우가 있다.
  // 따라서 waitForLoadState()와 함께 사용하여 화면 로딩이 확실하게 될 때까지 기다린 후에 작동되도록 만들어줘야 한다.
  // 아니면 textContent()를 호출한 후 allTextContents()를 사용하는 방법도 있다.
  // 혹은 waitFor()를 이용할 수도 있다.
  console.log(await cardInfo.allTextContents());
});

test("Fifth Playwright test", async ({ page }) => {
  await page.goto("https://rahulshettyacademy.com/loginpagePractise/");

  const idInput = page.locator("#username");
  const pwInput = page.locator("[type='password']");
  const signInBtn = page.locator("#signInBtn");
  const docLink = page.locator("[href*='documents-request']");

  const dropDown = page.locator("select.form-control");
  await dropDown.selectOption("consult"); // Option Css의 value 값을 넣어준다.

  // 매칭된 .radiotextsty 중에서 마지막 녀석을 클릭함
  await page.locator(".radiotextsty").last().click();

  // 해당 버튼이 체크 상태인지 확인함
  await expect(page.locator(".radiotextsty").last()).toBeChecked();

  // 밑의 방식으로도 체크 상태를 확인할 수 있다.
  const checkedRet = await page.locator(".radiotextsty").last().isChecked();

  await page.locator("#okayBtn").click();

  await page.locator("#terms").click();

  // click 해서 체크했다면 uncheck로 체크를 해제할 수도 있다.
  await page.locator("#terms").uncheck();

  // toBeFalsy() 함수를 통해 expect()에 주어진 값이 false인지 검사할 수 있다.
  // Action이 expect() 함수 내부에서 isChecked() 함수를 통해 발생하고 있으므로 expect() 내부에 await을 넣어줘야 한다.
  // Action인지 아닌지 확인하는 방법은 함수가 Promise<>를 반환한다면 Action인 것이다.
  //
  // 반환형이 Promise<>인 경우 Js에서는 항상 3가지 상태를 즉시 반환한다.
  // 1. Pending
  // 함수가 비동기로 동작하고 있는 상태
  // 2. Rejected
  // 비동기 처리가 비정상적으로 완료되어 반환된 상태
  // 3. Fulfilled
  // 비동기 처리가 정상적으로 완료되어 반환된 상태
  expect(await page.locator("#terms").isChecked()).toBeFalsy();

  // toHaveAttribute()로 특정 속성이 있는지 검사
  await expect(docLink).toHaveAttribute("class", "blinkingText");

  // 테스트 중인 페이지를 멈춤, 중단점이 해당 시점으로 잡힘
  // await page.pause();

  await idInput.fill("rahulshettyacademy"); // fill 함수로 input UI를 채움
  await pwInput.fill("learning");
  await signInBtn.click(); // 특정 버튼 클릭
});

test("Child Windows handling", async ({ browser }) => {
  const context = await browser.newContext();
  const page = await context.newPage();
  await page.goto("https://rahulshettyacademy.com/loginpagePractise/");

  const docLink = page.locator("[href*='documents-request']"); // 누르면 특정 페이지가 새로 열리는 링크 텍스트

  // waitForEvent() 함수는 특정 이벤트가 발생할 때까지 기다려줌
  // 'page'인자를 넘긴다면 새로운 페이지가 생성될 때까지 기다린 후에 새로운 페이지를 반환하며 종료한다.
  //
  // Promise.all()을 통해 waitForEvent("page"), click() 두 개의 비동기 함수를 트랜잭션과 같이 묶어줘야 하는 이유가 있다.
  // 3가지 상황을 고려해보자.
  //
  // 1. click() 수행 후 waitForEvent("page") 수행
  // click() 수행이 되는 즉시 새로운 페이지가 생겨버리면 waitForEvent()가 반응할 시간이 없기에 계속 기다리기만 하다가 에러를 출력한다.
  //
  // 2 waitForEvent("page") 수행 후 click() 수행
  // 전제부터 잘못되었다.
  // waitForEvent("page")는 특정 페이지가 생기지 않는 이상 수행되지 않는다.
  // 따라서 click()이 진행될 수 없다.
  //
  // 3. waitForEvent("page") 비동기 수행 후 click() 수행
  // waitForEvent("page")가 비동기이기에 잘 동작한다.
  //
  // 3번 빼고는 모두 정상적인 수행이 불가능하다.
  // 3번도 좋지만 이러한 경우 Promise.all()을 이용하는 것이 가독성이 명확하기에 선호된다.
  const [newPage] = await Promise.all([
    context.waitForEvent("page"),
    docLink.click(),
  ]);

  console.log(await newPage.locator(".red").textContent());
});

test("Market Shopping handling", async ({ browser }) => {
  const targetProductName = "IPHONE 13 PRO";
  const email = "anshika@gmail.com";

  const context = await browser.newContext();
  const page = await context.newPage();
  await page.goto("https://rahulshettyacademy.com/client");

  const idInput = page.locator("#userEmail");
  const pwInput = page.locator("#userPassword");
  const loginBtn = page.locator("[value='Login']");

  await idInput.fill(email);
  await pwInput.fill("Iamking@000");
  await loginBtn.click();

  const products = page.locator(".card-body");
  await products.last().locator("b").waitFor();
  const productsCnt = await products.count();

  for (let i = 0; i < productsCnt; i++) {
    if (
      (await products.nth(i).locator("b").textContent()) === targetProductName
    ) {
      // text로 버튼을 찾아 누르기
      // text=Add*Cart와 같이 정규식도 사용이 가능함
      await products.nth(i).locator("text=Add To Cart").click();
      break;
    }
  }

  // 장바구니에 담긴 물건을 확인하기 위해 카트 버튼 클릭
  await page.locator("[routerlink*='cart']").click();

  // 밑에서 수행할 isVisible()을 auto-waiting 함수가 아니기에 waitFor()를 수행해줘야 한다.
  await page.locator("div li").first().waitFor();

  // tagname:has-text("특정 텍스트") 기능은 tagname 하위에 "특정 텍스트"를 가지고 있는 녀석들을 모두 골라주는 방법이다.
  // h3:has-text("IPHONE 13 PRO")라면 h3 자신 혹은 그 자식 요소 중 "IPHONE 13 PRO"와 일치하는 녀석들을 모두 가져옴
  // 밑은 장바구니에 targetProductName을 가진 물건이 제대로 들어있는지 확인하기 위한 코드
  const isVisible = await page
    .locator(`h3:has-text("${targetProductName}")`)
    .isVisible();

  expect(isVisible).toBeTruthy();

  await page.locator("text=Checkout").click();

  // fill()말고 pressSequentially()를 이용해야 자동완성 선택지를 정상적으로 표기할 수 있음
  // fill()은 한 방에 모든 단어를 Copy + Paste 하는 것이고 pressSequentially()는 한 글자씩 타이핑하는 것
  // 자동 완성 선택를 고르기 위해 Korea, Democratic People's Republic of의 kor만 삽입함
  await page.locator("[placeholder*='Country']").pressSequentially("kor");

  // 자동 완성 드롭 다운 처리
  const dropDown = page.locator(".ta-results");
  await dropDown.last().waitFor();
  const optCnt = await dropDown.locator("button").count();
  for (let i = 0; i < optCnt; i++) {
    const text = await dropDown.locator("button").nth(i).textContent();

    // 자동완성 목록에서 남한을 선택
    if (text.trim() === "Korea, Democratic People's Republic of") {
      await dropDown.locator("button").nth(i).click();
      break;
    }
  }

  await expect(page.locator(".user__name label[type='text']")).toHaveText(
    email
  );
  await page.locator(".action__submit").click(); // 결재 버튼 클릭

  await expect(page.locator(".hero-primary")).toHaveText(
    "Thankyou for the order."
  );

  // 주문 코드 획득
  const orderId = await page
    .locator(".em-spacer-1 .ng-star-inserted")
    .textContent();
  console.log(orderId);
});

test("Practice get by functions", async ({ page }) => {
  await page.goto("https://rahulshettyacademy.com/angularpractice/");

  // 레이블을 통해 locator 접근
  // 그냥 "Check me out if you Love IceCreams!"가 쓰여져 있는 타겟을 가져오는 것
  await page.getByLabel("Check me out if you Love IceCreams!").click();

  // 체크 버튼, 버튼, 드롭다운 등은 getByLable()을 이용하는 것이 유효하지만 input 등 안먹히는 UI 계열도 있다.
  await page.getByLabel("Employed").check();
  await page.getByLabel("Gender").selectOption("Female");

  // text input의 경우 placeholder에 적힌 글자를 매칭시켜 찾을 수 있다.
  await page.getByPlaceholder("Password").fill("abc123");

  // 특정 Role을 통해 element를 가져오는 방법
  // 밑 코드는 화면에 있는 모든 Submit 버튼을 가져옴
  await page.getByRole("button", { name: "Submit" });

  // 특정 텍스트로 접근, 정규식도 사용 가능
  await page
    .getByText("Success! The Form has been submitted successfully!.")
    .isVisible();

  // 특정 링크가 담긴 요소들만 획득 가능
  await page.getByRole("link", { name: "Shop" }).click();

  // filter() 함수를 이용하여 app-card 요소를 가져올 때 하위 요소에 Nokia Edge 텍스트가 존재하는 녀석들을 추려서 가져옴
  await page
    .locator("app-card")
    .filter({ hasText: "Nokia Edge" })
    .getByRole("button")
    .click();
});

test("Calendar validations", async ({ page }) => {
  const month = "6",
    day = "15",
    year = "2027";
  const date = [month, day, year];
  await page.goto("https://rahulshettyacademy.com/seleniumPractise/#/offers");
  await page.locator(".react-date-picker__inputGroup").click(); // 달력 클릭
  await page.locator(".react-calendar__navigation__label").click(); // 달력 날짜 선택 scope 조정
  await page.locator(".react-calendar__navigation__label").click(); // 달력 날짜 선택 scope 조정
  await page.getByText(year).click(); // 년도 선택
  await page
    .locator(".react-calendar__year-view__months__month")
    .nth(month - 1)
    .click(); // 월 선택

  // xpath를 이용해 요소를 찾는다.
  // xpath에 대한 자세한 정보는 https://blog.hashscraper.com/understanding-xpath-for-web-crawling/ 참고
  await page.locator(`//abbr[contains(text(),'${day}')]`).click(); // 일자 선택

  const timeData = page.locator(".react-date-picker__inputGroup input");
  // 첫번째 인덱스는 불필요한 정보라 스킵하고 1부터 분석
  for (let i = 1; i < (await timeData.count()); i++) {
    const value = await timeData.nth(i).getAttribute("value");
    expect(value).toEqual(date[i - 1]);
  }
});

test("Popup validations", async ({ page }) => {
  await page.goto("https://rahulshettyacademy.com/AutomationPractice/");

  await expect(page.locator("#displayed-text")).toBeVisible(); // 요소가 보이는 상태인지
  await page.locator("#hide-textbox").click();
  await expect(page.locator("#displayed-text")).toBeHidden(); // 요소가 숨겨진 상태인지

  // on()으로 이벤트를 낚아채 dialog 팝업을 컨트롤 할 수 있다.
  // 이벤트 발생 시에 어떤 것을 행하라는 행위를 등록해놓는 것이기에 await는 필요없다.
  // 즉 모든 dialog 이벤트는 accpet()를 해버리기에 행위를 바꾸고 싶다면 따로 on()을 더 써줘야 한다.
  page.on("dialog", (dialog) => dialog.accept());
  await page.locator("#confirmbtn").click();

  // 특정 요소에 마우스 호버링
  await page.locator("#mousehover").hover();

  // iframe 획득
  const framePage = page.frameLocator("#courses-iframe");

  // 여러 항목 중 보이는 것만 가져오고 싶다면 isVisible()를 이용한 순회를 해도 되지만 :visible을 달아줘도 된다.
  await framePage.locator("li a[href*='lifetime-access']:visible").click();
  const someText = await framePage.locator(".text h2").textContent();
  console.log(someText.split(" ")[1]);
});

// test 키워드
// only => 다른 테스트 무시하고 해당 테스트만 수행
// beforeAll => 모든 테스트가 수행되기 전 첫 순위로 해당 테스트가 수행됨
// beforeEach => 모든 테스트가 수행되기 전마다 해당 테스트를 계속 같이 수행시킴

test("Use WebAPI", async ({ browser }) => {
  const apiContext = await request.newContext();

  // post() 함수를 통해 http 서버에서 요청하는 값을 받아 활용할 수 있다.
  // 요구되는 인자는 다음과 같다.
  // 1. Request Url
  // 2. Post Object
  // 2-1. Request Payload
  // 2-2. Request Header
  // ... more
  const loginResponse = await apiContext.post(
    "https://rahulshettyacademy.com/api/ecom/auth/login",
    {
      data: {
        userEmail: "anshika@gmail.com",
        userPassword: "Iamking@000",
      },
    }
  );

  // ok() 함수로 loginResponse가 성공인지 확인한다.
  expect(loginResponse.ok()).toBeTruthy();

  // loginResponse의 결과를 json으로 바꿔 받는다.
  const loginResponseJson = await loginResponse.json();

  // 로그인 결과를 저장할 수 있는 토큰을 획득한다.
  const loginToken = loginResponseJson.token;

  const context = await browser.newContext();
  const page = await context.newPage();

  // addInitScript() 함수를 통해 특정 스크립트를 지정해 실행하거나 특정 함수를 수행한다.
  // 물론 함수에 인자가 들어간다면 인자를 함께 넘겨준다.
  // 웹 창에 획득한 token 값을 로컬 저장소에 저장하는 함수를 수행하고 있다.
  page.addInitScript((value) => {
    window.localStorage.setItem("token", value);
  }, loginToken);

  await page.goto("https://rahulshettyacademy.com/client");

  // 장바구니에 물건 추가
  const addCartResponse = await apiContext.post(
    "https://rahulshettyacademy.com/api/ecom/user/add-to-cart",
    {
      data: {
        _id: "620c7bf148767f1f1215d2ca",
        product: {
          _id: "6581ca979fd99c85e8ee7faf",
          productName: "ADIDAS ORIGINAL",
          productCategory: "household",
          productSubCategory: "shoes",
          productPrice: 31500,
          productDescription: "Adidas shoes for Men",
          productImage:
            "https://rahulshettyacademy.com/api/ecom/uploads/productImage_1650649488046.jpg",
          productRating: "0",
          productTotalOrders: "0",
          productStatus: true,
          productFor: "men",
          productAddedBy: "admin@gmail.com",
          __v: 0,
        },
      },
      headers: {
        Authorization: loginToken,
        "Content-Type": "application/json",
      },
    }
  );

  const addCartResponseJson = await addCartResponse.json();
  expect(addCartResponseJson.message === "Product Added To Cart").toBeTruthy();

  // 주문
  const orderResponse = await apiContext.post(
    "https://rahulshettyacademy.com/api/ecom/order/create-order",
    {
      data: {
        orders: [
          {
            country: "Korea, Democratic People's Republic of",
            productOrderedId: "6581ca979fd99c85e8ee7faf",
          },
        ],
      },
      headers: {
        Authorization: loginToken,
        "Content-Type": "application/json",
      },
    }
  );

  const orderResponseJson = await orderResponse.json();
  expect(
    orderResponseJson.message === "Order Placed Successfully"
  ).toBeTruthy();
});

test("Use WebAPI With Wrapping Class", async ({ browser }) => {
  const apiContext = await request.newContext();

  const apiUtil = new APIUtil(apiContext, {
    userEmail: "anshika@gmail.com",
    userPassword: "Iamking@000",
  });

  const addCartResponse = await apiUtil.addToCart({
    _id: "620c7bf148767f1f1215d2ca",
    product: {
      _id: "6581ca979fd99c85e8ee7faf",
      productName: "ADIDAS ORIGINAL",
      productCategory: "household",
      productSubCategory: "shoes",
      productPrice: 31500,
      productDescription: "Adidas shoes for Men",
      productImage:
        "https://rahulshettyacademy.com/api/ecom/uploads/productImage_1650649488046.jpg",
      productRating: "0",
      productTotalOrders: "0",
      productStatus: true,
      productFor: "men",
      productAddedBy: "admin@gmail.com",
      __v: 0,
    },
  });

  expect(addCartResponse.message === "Product Added To Cart").toBeTruthy();

  const orderResponse = await apiUtil.createOrder({
    orders: [
      {
        country: "Korea, Democratic People's Republic of",
        productOrderedId: "6581ca979fd99c85e8ee7faf",
      },
    ],
  });

  expect(orderResponse.message === "Order Placed Successfully").toBeTruthy();
});

test("Get google place info", async ({ page }) => {
  // searchKeyword 구성 방법 => 시/군/구/동 + " " + 유형
  const searchKeyword = "서울 구청"; // 서울 구청, 삼성동 맛집 ... 이런 검색 키워드마다 tagname이 계속 바뀜
  const excelSavePath = "D:/GoogleMapCrawlData.xlsx";
  let placeCnt = 0;

  // 엑셀 파일 저장을 위한 객체 구성
  const workBook = new ExcelJs.Workbook();
  const workSheet = workBook.addWorksheet("GoogleMap Sheet 01");

  workSheet.getCell("B1").value = "장소";
  workSheet.getCell("C1").value = "영업 시간";
  workSheet.getCell("D1").value = "웹 사이트";
  workSheet.getCell("E1").value = "전화번호";

  let putDataOnSheetFunc = (dataIndex, datas) => {
    let rowNum = dataIndex + 2;
    if (datas.hasOwnProperty("name"))
      workSheet.getCell("A" + rowNum).value = datas.name;
    if (datas.hasOwnProperty("location"))
      workSheet.getCell("B" + rowNum).value = datas.location;
    if (datas.hasOwnProperty("businessHours"))
      workSheet.getCell("C" + rowNum).value = datas.businessHours;
    if (datas.hasOwnProperty("webSite"))
      workSheet.getCell("D" + rowNum).value = datas.webSite;
    if (datas.hasOwnProperty("phone"))
      workSheet.getCell("E" + rowNum).value = datas.phone;
  };

  await page.goto("https://www.google.co.kr/maps/");
  await page.locator("#searchboxinput").fill(searchKeyword);
  await page.locator("#searchbox-searchbutton").click();

  // 숙박 장소를 검색하면 UI가 달라지는데... 일단 크롤링에 영향은 없는 듯 하여 여부만 따짐
  let isPlaceMode = false;
  let placeKeywords = [
    "호텔",
    "hotel",
    "모텔",
    "motel",
    "게스트하우스",
    "게하",
    "guest house",
    "숙박",
    "accomodation",
    "잘곳",
    "리조트",
    "resort",
    "콘도",
    "성급",
    "five-star",
    "펜션",
    "pension",
  ];

  for (let i = 0; i < placeKeywords.length && !isPlaceMode; i++) {
    if (searchKeyword.search(placeKeywords[i]) < 0) isPlaceMode = true;
  }

  await page.waitForTimeout(2000);
  // await page.waitForLoadState("domcontentloaded");

  // 검색 결과가 없는 경우
  if (await page.locator("button.kyuRq").isVisible()) return;

  // 검색 결과가 하나인 경우
  if (!(await page.locator("div.k7jAl.miFGmb.lJ3Kh.PLbyfe").isVisible())) {
    // 이름
    let nameLoc = page.locator("h1.DUwDvf");
    let name = "";
    if (await nameLoc.isVisible()) {
      name = await nameLoc.textContent();
      console.log(name);
    }

    // 장소
    let locationLoc = page.locator("button[data-item-id='address']");
    let location = "";
    if (await locationLoc.isVisible()) {
      location = await locationLoc.getAttribute("aria-label");
      console.log(location);
    }

    // 영업 시간
    let businessHoursSpan = page.locator("span.ZDu9vd");
    let businessHours = "";
    if (await businessHoursSpan.isVisible()) {
      await businessHoursSpan.click();

      let businessHoursLoc = page.locator("div.t39EBf.GUrTXd");
      if (await businessHoursLoc.isVisible()) {
        businessHours = await businessHoursLoc.getAttribute("aria-label");
        console.log(businessHours);
      }
    }

    // 웹 사이트
    let webSiteLoc = page.locator("a[data-item-id*='authority']");
    let webSite = "";
    if (await webSiteLoc.isVisible()) {
      webSite = await webSiteLoc.getAttribute("href");
      console.log(webSite);
    }

    // 전화번호
    let phoneLoc = page.locator("button[data-item-id*='phone']");
    let phone = "";
    if (await phoneLoc.isVisible()) {
      phone = await phoneLoc.getAttribute("aria-label");
      console.log(phone);
    }

    putDataOnSheetFunc(0, {
      name: name,
      location: location,
      businessHours: businessHours,
      webSite: webSite,
      phone: phone,
    });

    await workBook.xlsx.writeFile(excelSavePath);
    return;
  }

  let placeDivList = page.locator(".m6QErb[role$='feed']");
  await placeDivList.focus();

  let pastDelimCnt = 0;
  let curDelimCnt = 0;
  while (true) {
    curDelimCnt = await page.locator("div > a.hfpxzc").count();

    if (curDelimCnt === pastDelimCnt) break;

    pastDelimCnt = curDelimCnt;

    await page.keyboard.press("End");
    await page.waitForTimeout(2000); // 개선 필요
  }

  let placeElem = placeDivList.locator("div > a.hfpxzc");
  placeCnt = await placeElem.count();

  for (let i = 0; i < placeCnt; i++) {
    await placeElem.nth(i).click();

    await page.waitForTimeout(1500); // 개선이 필요함

    // 이름
    let nameLoc = page.locator("h1.DUwDvf");
    let name = "";
    if (await nameLoc.isVisible()) {
      name = await nameLoc.textContent();
      console.log(name);
    }

    // 장소
    let locationLoc = page.locator(
      "div.RcCsl.fVHpi.w4vB1d.NOE9ve.M0S7ae.AG25L > button[data-item-id='address']"
    );
    let location = "";
    if (await locationLoc.isVisible()) {
      location = await locationLoc.getAttribute("aria-label");
      console.log(location);
    }

    // 영업 시간
    let businessHoursSpan = page.locator("span.ZDu9vd");
    let businessHours = "";
    if (await businessHoursSpan.isVisible()) {
      await businessHoursSpan.click();

      let businessHoursLoc = page.locator(
        "div.OqCZI.fontBodyMedium.WVXvdc > div.t39EBf.GUrTXd"
      );
      if (await businessHoursLoc.isVisible()) {
        businessHours = await businessHoursLoc.getAttribute("aria-label");
        console.log(businessHours);
      }
    }

    // 웹 사이트
    let webSiteLoc = page.locator(
      "div.RcCsl.fVHpi.w4vB1d.NOE9ve.M0S7ae.AG25L > a[data-item-id*='authority']"
    );
    let webSite = "";
    if (await webSiteLoc.isVisible()) {
      webSite = await webSiteLoc.getAttribute("href");
      console.log(webSite);
    }

    // 전화번호
    let phoneLoc = page.locator(
      "div.RcCsl.fVHpi.w4vB1d.NOE9ve.M0S7ae.AG25L > button[data-item-id*='phone']"
    );
    let phone = "";
    if (await phoneLoc.isVisible()) {
      phone = await phoneLoc.getAttribute("aria-label");
      console.log(phone);
    }

    putDataOnSheetFunc(i, {
      name: name,
      location: location,
      businessHours: businessHours,
      webSite: webSite,
      phone: phone,
    });
  }

  await workBook.xlsx.writeFile(excelSavePath);
});

test("Get local cache json from process", async ({ browser }) => {
  const context = await browser.newContext();
  const page = await context.newPage();

  await page.goto("https://rahulshettyacademy.com/client");
  await page.locator("#userEmail").fill("anshika@gmail.com");
  await page.locator("#userPassword").type("Iamking@000");
  await page.locator("[value='Login']").click();
  await page.waitForLoadState("networkidle");

  // state.json 파일에 현재까지 진행한 웹 로컬 데이터를 저장함
  await context.storageState({ path: "state.json" });

  // state.json 파일을 이용해 브라우저 context를 생성하면 로그인 과정이 이미 되어있는 브라우저 상태를 획득할 수 있다.
  context = await browser.newContext({ storageState: "state.json" });
});

test.only("Get instagram hashtag info", async ({ page }) => {
  let id = "kyungjoon_1997",
    pw = "pw",
    searchKeyword = "#선릉역맛집";

  await page.goto("https://www.instagram.com/");
  await page.locator("input[name='username']").fill(id);
  await page.locator("input[name='password']").fill(pw);
  await page
    .locator(
      "body > div:nth-child(3) > div:nth-child(1) > div:nth-child(1) > div:nth-child(2) > div:nth-child(1) > div:nth-child(1) > div:nth-child(1) > section:nth-child(1) > main:nth-child(1) > article:nth-child(1) > div:nth-child(2) > div:nth-child(1) > div:nth-child(2) > form:nth-child(1) > div:nth-child(1) > div:nth-child(3)"
    )
    .click();

  // 검색 버튼 누르기
  await page
    .locator(
      "div[class='x1iyjqo2 xh8yej3'] div:nth-child(2) span:nth-child(1) div:nth-child(1) a:nth-child(1) div:nth-child(1) div:nth-child(2) div:nth-child(1) div:nth-child(1) span:nth-child(1) span:nth-child(1)"
    )
    .click();

  await page
    .locator(
      "input.x1lugfcp.x19g9edo.x1lq5wgf.xgqcy7u.x30kzoy.x9jhf4c.x972fbf.xcfux6l.x1qhh985.xm0m39n.x9f619.x5n08af.xl565be.x5yr21d.x1a2a7pz.xyqdw3p.x1pi30zi.xg8j3zb.x1swvt13.x1yc453h.xh8yej3.xhtitgo.xs3hnx8.x1dbmdqj.xoy4bel.x7xwk5j"
    )
    .pressSequentially(searchKeyword);

  let hashtagList = page.locator(
    "a.x1i10hfl.x1qjc9v5.xjbqb8w.xjqpnuy.xa49m3k.xqeqjp1.x2hbi6w.x13fuv20.xu3j5b3.x1q0q8m5.x26u7qi.x972fbf.xcfux6l.x1qhh985.xm0m39n.x9f619.x1ypdohk.xdl72j9.x2lah0s.xe8uvvx.xdj266r.x11i5rnm.xat24cr.x1mh8g0r.x2lwn1j.xeuugli.xexx8yu.x4uap5.x18d9i69.xkhd6sd.x1n2onr6.x16tdsg8.x1hl2dhg.xggy1nq.x1ja2u2z.x1t137rt.x1q0g3np.x87ps6o.x1lku1pv.x1a2a7pz.x1dm5mii.x16mil14.xiojian.x1yutycm.x1lliihq.x193iq5w.xh8yej3"
  );

  await page.waitForTimeout(2000);

  if (await hashtagList.count()) hashtagList.first().click();

  await page.waitForTimeout(2000);

  if (
    await page
      .locator(
        ".x1lliihq.x1plvlek.xryxfnj.x1n2onr6.x193iq5w.xeuugli.x1fj9vlw.x13faqbe.x1vvkbs.x1s928wv.xhkezso.x1gmr53x.x1cpjm7i.x1fgarty.x1943h6x.x1i0vuye.x1ms8i2q.xo1l8bm.x5n08af.x4zkp8e.xw06pyt.x10wh9bi.x1wdrske.x8viiok.x18hxmgj"
      )
      .isVisible()
  ) {
    await page.locator("div[role='button']").click();
  }

  // 테이블로 3개씩 묶음
  // _ac7v xzboxd6 x11ulueq x1f01sob xwq5r7b xcghwft -> 행, row
  // x1lliihq x1n2onr6 xh8yej3 x4gyw5p x2pgyrj x56m6dy x1ntc13c xn45foy x9i3mqj -> 열, col
});
