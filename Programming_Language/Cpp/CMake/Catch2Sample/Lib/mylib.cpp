unsigned int factorial(unsigned int n) {
    return n <= 1 ? n : n * factorial(n - 1);
}