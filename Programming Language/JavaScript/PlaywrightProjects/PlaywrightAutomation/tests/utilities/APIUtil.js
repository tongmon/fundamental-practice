class APIUtil {
  #token = "";

  constructor(apiContext, loginData) {
    this.apiContext = apiContext;
    this.loginData = loginData;
  }

  async #getToken() {
    if (this.#token.length) return this.#token;

    const loginResponse = await this.apiContext.post(
      "https://rahulshettyacademy.com/api/ecom/auth/login",
      {
        data: this.loginData,
      }
    );

    // 꼭 단계별로 나누어서 await을 박자...
    // const loginResponseToken = await loginResponse.json().token 요딴거 하면 바로 결과 박살난다.
    const loginResponseJson = await loginResponse.json();
    this.#token = loginResponseJson.token;

    return this.#token;
  }

  async addToCart(addPayload) {
    const addCartResponse = await this.apiContext.post(
      "https://rahulshettyacademy.com/api/ecom/user/add-to-cart",
      {
        data: addPayload,
        headers: {
          Authorization: await this.#getToken(),
          "Content-Type": "application/json",
        },
      }
    );

    return await addCartResponse.json();
  }

  async createOrder(orderPayload) {
    const orderResponse = await this.apiContext.post(
      "https://rahulshettyacademy.com/api/ecom/order/create-order",
      {
        data: orderPayload,
        headers: {
          Authorization: await this.#getToken(),
          "Content-Type": "application/json",
        },
      }
    );

    return await orderResponse.json();
  }
}

export { APIUtil };
