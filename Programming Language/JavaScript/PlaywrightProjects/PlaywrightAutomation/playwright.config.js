// @ts-check
const { defineConfig, devices } = require("@playwright/test");
const { off } = require("process");

/**
 * Read environment variables from file.
 * https://github.com/motdotla/dotenv
 */
// require('dotenv').config();

/**
 * @see https://playwright.dev/docs/test-configuration
 */
module.exports = defineConfig({
  // 테스트 수행할 코드가 들어있는 폴더 위치
  testDir: "./tests",

  // 테스트를 병렬 수행할 것인지 여부
  fullyParallel: true,

  // 테스트 진행 중 timeout에 기재된 시간 동안 아무런 반응이 없다면 실패처리함
  // 즉 해당 시간은 test 명령에 대한 시간 제한 값임
  timeout: 30 * 1000 * 9999,

  /* Fail the build on CI if you accidentally left test.only in the source code. */
  forbidOnly: !!process.env.CI,

  /* Retry on CI only */
  retries: process.env.CI ? 2 : 0,
  /* Opt out of parallel tests on CI. */
  workers: process.env.CI ? 1 : undefined,

  /* 테스트의 결과를 보고 하기위한 파일의 형식, 자세한 내용은 https://playwright.dev/docs/test-reporters 링크 참조 */
  reporter: "html",

  expect: {
    // expect 한 라인 수행하는 경우, 최대 timeout에 기재된 시간을 기다림
    // 즉 해당 시간은 expect 명령에 대한 시간 제한 값임
    timeout: 5000,
  },

  /* 테스트 코드가 수행될 때 공유되는 특성들, 자세한 것은 https://playwright.dev/docs/api/class-testoptions 참조. */
  use: {
    /* Base URL to use in actions like `await page.goto('/')`. */
    // baseURL: 'http://127.0.0.1:3000',

    /* 테스트에 대한 로그를 언제 남길 것인지 설정 */
    // playwright의 로그는 굉장히 강력함
    // 각 라인 별로 어떤 행위가 수행되었는지 각 시간별로 화면을 보여줌
    trace: "retain-on-failure",

    // 스크린샷 캡쳐를 언제 수행할 것인지 설정
    screenshot: "only-on-failure",

    // 수행할 브라우저 유형
    browserName: "chromium",

    launchOptions: {
      channel: "msedge",
    },

    // true -> 브라우저를 띄우지 않고 행함, false -> 브라우저를 띄우고 행함
    headless: false,
  },

  /* 해당 섹션에 적혀있는 브라우저들 마다 테스트가 진행됨 */
  projects: [
    //{
    //  name: "chromium",
    //  use: {
    //    channel: "chrome",
    //    //...devices["Desktop Chrome"],
    //  },
    //},

    //{
    //  name: "firefox",
    //  use: { ...devices["Desktop Firefox"] },
    //},

    //{
    //  name: "webkit",
    //  use: { ...devices["Desktop Safari"] },
    //},

    {
      name: "edge",
      use: {
        channel: "msedge",
      },
    },

    /* Test against mobile viewports. */
    // {
    //   name: 'Mobile Chrome',
    //   use: { ...devices['Pixel 5'] },
    // },
    // {
    //   name: 'Mobile Safari',
    //   use: { ...devices['iPhone 12'] },
    // },

    /* Test against branded browsers. */
    // {
    //   name: 'Microsoft Edge',
    //   use: { ...devices['Desktop Edge'], channel: 'msedge' },
    // },
    // {
    //   name: 'Google Chrome',
    //   use: { ...devices['Desktop Chrome'], channel: 'chrome' },
    // },
  ],

  /* Run your local dev server before starting the tests */
  // webServer: {
  //   command: 'npm run start',
  //   url: 'http://127.0.0.1:3000',
  //   reuseExistingServer: !process.env.CI,
  // },
});
