const { test } = require("@playwright/test");

// 함수를 전달할 때 async로 전달해야만 await가 의미있다.
test("First Playwright test", async () => {
  await page.goto("https://playwright.dev/");
});
