const { test, expect, request } = require("@playwright/test");

class APIUtil {
  constructor(apiContext, loginData) {
    this.apiContext = apiContext;
    this.loginData = loginData;
    this.token = this.getToken();
  }

  async getToken() {
    const loginResponse = await this.apiContext.post(
      "https://rahulshettyacademy.com/api/ecom/auth/login",
      {
        data: this.loginData,
      }
    );

    return loginResponse.json().token;
  }

  async addToCart(addPayload) {
    const addCartResponse = await this.apiContext.post(
      "https://rahulshettyacademy.com/api/ecom/user/add-to-cart",
      {
        data: addPayload,
        headers: {
          Authorization: this.token,
          "Content-Type": "application/json",
        },
      }
    );

    return addCartResponse.json();
  }

  async createOrder(orderPayload) {
    const orderResponse = await this.apiContext.post(
      "https://rahulshettyacademy.com/api/ecom/order/create-order",
      {
        data: orderPayload,
        headers: {
          Authorization: this.token,
          "Content-Type": "application/json",
        },
      }
    );

    return orderResponse.json();
  }
}

module.exports = { APIUtil };
