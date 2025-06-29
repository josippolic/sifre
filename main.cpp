#include <iostream>
#include <fstream>
#include <ctime>
#include "generator.hpp"
#include "checker.hpp"

std::string getCurrentTimestamp() {
    time_t now = time(0);
    char* dt = ctime(&now);
    std::string result(dt);
    // Ukloni newline sa kraja
    if (!result.empty() && result.back() == '\n') result.pop_back();
    return result;
}

int main() {
    int length;
    bool upper, lower, digits, symbols;

    std::cout << "Duzina lozinke: ";
    std::cin >> length;

    std::cout << "Koristiti velika slova? (1/0): "; std::cin >> upper;
    std::cout << "Koristiti mala slova? (1/0): "; std::cin >> lower;
    std::cout << "Koristiti brojeve? (1/0): "; std::cin >> digits;
    std::cout << "Koristiti simbole? (1/0): "; std::cin >> symbols;

    std::string password = generatePassword(length, upper, lower, digits, symbols);

    int charsetSize = 0;
    if (upper) charsetSize += 26;
    if (lower) charsetSize += 26;
    if (digits) charsetSize += 10;
    if (symbols) charsetSize += 32;

    double entropy = calculateEntropy(length, charsetSize);

    std::cout << "\nGenerisana lozinka: " << password << std::endl;
    std::cout << "Entropija: " << entropy << " bita" << std::endl;

    std::string wordlistPath = "~usr/share/wordlists/rockyou.txt";
    bool isBlacklisted = isPasswordBlacklisted(password, wordlistPath);

    if (isBlacklisted) {
        std::cout << "⚠️  UPOZORENJE: Ova lozinka postoji u poznatoj wordlisti!" << std::endl;
    } else {
        std::cout << "✅ Lozinka nije pronađena u wordlisti." << std::endl;
    }

    // 📝 Spremi u passwords5.txt
    std::ofstream outFile("passwords5.txt", std::ios::app); // dodaj na kraj
    if (outFile.is_open()) {
        outFile << "---------------------------\n";
        outFile << "Vrijeme: " << getCurrentTimestamp() << "\n";
        outFile << "Lozinka: " << password << "\n";
        outFile << "Entropija: " << entropy << " bita\n";
        outFile << "Blacklisted: " << (isBlacklisted ? "DA" : "NE") << "\n";
        outFile.close();
        std::cout << "✅ Lozinka spremljena u 'passwords5.txt'.\n";
    } else {
        std::cerr << "❌ Greška pri pisanju u 'passwords5.txt'.\n";
    }

    return 0;
}
