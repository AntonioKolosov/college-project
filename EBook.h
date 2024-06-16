#ifndef EBOOK_H
#define EBOOK_H

#include "Book.h"

class EBook : public Book {
private:
    std::string format;
    double fileSize;

public:
    EBook(const std::string& title, const std::string& author, int id, bool available, const std::string& format, double fileSize)
        : Book(title, author, id, available), format(format), fileSize(fileSize) {}

    void display() const override {
        Book::display();
        std::cout << "Format: " << format << "\nFile Size: " << fileSize << " MB" << std::endl;
    }

    std::string getFormat() const { return format; }
    double getFileSize() const { return fileSize; }
};

#endif // EBOOK_H
