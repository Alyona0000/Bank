#include <iostream>
#include <cstdlib>
#include <ctime>

#include "httplib.h"
#include "Bank.h"
#include "User.h"
#include "Deposit.h"
#include "Credit.h"
#include "Security.h"

Bank<double> bank(100000);

int main() {
    srand(time(NULL));

    bank.addUser(User(1, "Anna"));
    bank.addUser(User(2, "Oleh"));
    bank.addUser(User(3, "Maria"));
    bank.addUser(User(4, "Ivan"));

    bank.addSecurity(Security("Apple", "stock", 180, 10, 0.12));
    bank.addSecurity(Security("Tesla", "stock", 220, 8, 0.15));
    bank.addSecurity(Security("Government Bond", "bond", 100, 20, 0.05));

    httplib::Server server;

    server.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_file_content("index.html", "text/html; charset=UTF-8");
    });

    server.Post("/api/deposit", [](const httplib::Request& req, httplib::Response& res) {
        double amount = atof(req.body.c_str());
        bank.addManualDeposit(amount);
        res.set_content(bank.toJson(), "application/json");
    });

    server.Post("/api/credit", [](const httplib::Request& req, httplib::Response& res) {
        double amount = atof(req.body.c_str());
        bank.giveManualCredit(amount);
        res.set_content(bank.toJson(), "application/json");
    });

    server.Post("/api/buy-stock", [](const httplib::Request&, httplib::Response& res) {
        bank.buyRandomSecurity();
        res.set_content(bank.toJson(), "application/json");
    });

    server.Post("/api/sell-stock", [](const httplib::Request&, httplib::Response& res) {
        bank.sellRandomSecurity();
        res.set_content(bank.toJson(), "application/json");
    });

    server.Post("/api/simulate-day", [](const httplib::Request&, httplib::Response& res) {
        bank.simulateNextDay();
        res.set_content(bank.toJson(), "application/json");
    });

    server.Get("/api/state", [](const httplib::Request&, httplib::Response& res) {
        res.set_content(bank.toJson(), "application/json");
    });

    std::cout << "Server started: http://localhost:8080\n";
    server.listen("localhost", 8080);

    return 0;
}