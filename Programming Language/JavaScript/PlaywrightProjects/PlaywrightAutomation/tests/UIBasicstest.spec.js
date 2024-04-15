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
//
// 모든 테스트는 headless 방식으로 진행되기 때문에 별도의 명령어가 없다면 브라우저가 보이지 않음
// npx playwright test --headed
// 위와 같이 headed 옵션을 달아줘야 실제로 브라우저 진행 상황이 보임, 혹은 playwright.config.js의 headless 옵션을 이용
//
// 리포트 결과를 보는 명령어는 밑과 같다.
// npx playwright show-report

// test와 expect 키워드를 이용하기 위해 선언함
const { test, expect } = require("@playwright/test");
const exp = require("constants");

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
  // [attribute = 'value'] (ex. [name = 'username'])
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
  // console.log(await cardInfo.nth(0).textContent());

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

test.only("Fifth Playwright test", async ({ page }) => {
  await page.goto("https://rahulshettyacademy.com/loginpagePractise/");

  const idInput = page.locator("#username");
  const pwInput = page.locator("[type='password']");
  const signInBtn = page.locator("#signInBtn");

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
  await expect(await page.locator("#terms").isChecked()).toBeFalsy();

  // 테스트 중인 페이지를 멈춤, 중단점이 해당 시점으로 잡힘
  // await page.pause();

  await idInput.fill("rahulshettyacademy"); // fill 함수로 input UI를 채움
  await pwInput.fill("learning");
  await signInBtn.click(); // 특정 버튼 클릭
});
