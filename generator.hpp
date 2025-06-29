#pragma once
#include <string>
#include <random>
#include <ctime>
#include <cmath>

std::string generatePassword(int length, bool use_upper, bool use_lower, bool use_digits, bool use_symbols) {
    std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string lower = "abcdefghijklmnopqrstuvwxyz";
    std::string digits = "0123456789";
    std::string symbols = "!@#$%^&*()_+-=[]{}|;:',.<>?";

    std::string charset;
    if (use_upper) charset += upper;
    if (use_lower) charset += lower;
    if (use_digits) charset += digits;
    if (use_symbols) charset += symbols;

    std::string password;
    std::mt19937 rng(time(0));
    std::uniform_int_distribution<> dist(0, charset.size() - 1);

    for (int i = 0; i < length; ++i)
        password += charset[dist(rng)];

    return password;
}

double calculateEntropy(int length, int charsetSize) {
    return length * log2(charsetSize);
}
