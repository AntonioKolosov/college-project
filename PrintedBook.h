#ifndef PRINTEDBOOK_H
#define PRINTEDBOOK_H

#include "Book.h"

class PrintedBook : public Book {
private:
    int pages;

public:
    PrintedBook(const std::string& title, const std::string& author, int id, bool available, int pages)
        : Book(title, author, id, available), pages(pages) {}

    void display() const override {
        Book::display();
        std::cout << "Pages: " << pages << std::endl;
    }

    int getPages() const { return pages; }
};

#endif // PRINTEDBOOK_H
