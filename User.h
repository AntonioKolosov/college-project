#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

class User {
private:
    std::string name;
    int userId;

public:
    User(const std::string& name, int userId)
        : name(name), userId(userId) {}

    void display() const {
        std::cout << "User ID: " << userId << "\nName: " << name << std::endl;
    }

    int getUserId() const { return userId; }
};

#endif // USER_H
