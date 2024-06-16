#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

class Book {
private:
    std::string title;
    std::string author;
    int id;
    bool available;

public:
    Book(const std::string& title, const std::string& author, int id, bool available)
        : title(title), author(author), id(id), available(available) {}

    virtual void display() const {
        std::cout << "ID: " << id << "\nTitle: " << title << "\nAuthor: " << author << "\nAvailable: " << (available ? "Yes" : "No") << std::endl;
    }

    int getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    bool isAvailable() const { return available; }
    void setAvailable(bool available) { this->available = available; }

    virtual ~Book() = default;
};

#endif // BOOK_H
