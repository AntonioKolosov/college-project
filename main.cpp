#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include "Book.h"
#include "User.h"
#include "EBook.h"
#include "PrintedBook.h"

void addBook(std::vector<Book*>& library, Book* newBook) {
    for (const auto& book : library) {
        if (book->getId() == newBook->getId()) {
            std::cout << "Book with ID " << newBook->getId() << " already exists." << std::endl;
            delete newBook;
            return;
        }
    }
    library.push_back(newBook);
    std::cout << "Book added: " << newBook->getTitle() << std::endl;
}

void removeBook(std::vector<Book*>& library, int bookId) {
    for (auto it = library.begin(); it != library.end(); ++it) {
        if ((*it)->getId() == bookId) {
            std::cout << "Book removed: " << (*it)->getTitle() << std::endl;
            delete *it;
            library.erase(it);
            return;
        }
    }
    std::cout << "Book ID " << bookId << " not found." << std::endl;
}

void searchBook(const std::vector<Book*>& library, const std::string& title) {
    for (const auto& book : library) {
        if (book->getTitle() == title) {
            book->display();
            return;
        }
    }
    std::cout << "Book with title \"" << title << "\" not found." << std::endl;
}

void saveToFile(const std::vector<Book*>& library, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file " + filename);
    }

    for (const auto& book : library) {
        if (dynamic_cast<EBook*>(book)) {
            EBook* ebook = dynamic_cast<EBook*>(book);
            file << ebook->getId() << "\n"
                 << ebook->getTitle() << "\n"
                 << ebook->getAuthor() << "\n"
                 << ebook->isAvailable() << "\n"
                 << "E " << ebook->getFormat() << "\n"
                 << ebook->getFileSize() << "\n";
        } else if (dynamic_cast<PrintedBook*>(book)) {
            PrintedBook* printedBook = dynamic_cast<PrintedBook*>(book);
            file << printedBook->getId() << "\n"
                 << printedBook->getTitle() << "\n"
                 << printedBook->getAuthor() << "\n"
                 << printedBook->isAvailable() << "\n"
                 << "P " << printedBook->getPages() << "\n";
        } else {
            file << book->getId() << "\n"
                 << book->getTitle() << "\n"
                 << book->getAuthor() << "\n"
                 << book->isAvailable() << "\n";
        }
    }
    std::cout << "Library data saved to " << filename << std::endl;
}

void loadFromFile(std::vector<Book*>& library, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file " + filename);
    }

    library.clear();
    std::string title;
    std::string author;
    int id;
    bool available;
    std::string format;
    double fileSize;
    int pages;
    char bookType;

    while (file >> id >> std::ws && std::getline(file, title) && std::getline(file, author) && file >> available) {
        file >> bookType;
        if (bookType == 'E') {
            file >> std::ws >> format >> fileSize;
            library.push_back(new EBook(title, author, id, available, format, fileSize));
        } else if (bookType == 'P') {
            file >> std::ws >> pages;
            library.push_back(new PrintedBook(title, author, id, available, pages));
        } else {
            library.push_back(new Book(title, author, id, available));
        }
    }
    std::cout << "Library data loaded from " << filename << std::endl;
}

void updateAvailability(std::vector<Book*>& library, int bookId, bool available) {
    for (auto& book : library) {
        if (book->getId() == bookId) {
            book->setAvailable(available);
            std::cout << "Book ID " << bookId << " availability updated to " << (available ? "Yes" : "No") << std::endl;
            return;
        }
    }
    std::cout << "Book ID " << bookId << " not found." << std::endl;
}

// Рекурсивная функция для подсчета страниц
int countTotalPages(const std::vector<Book*>& library, int index = 0) {
    if (index == library.size()) {
        return 0;
    }
    PrintedBook* printedBook = dynamic_cast<PrintedBook*>(library[index]);
    int pages = printedBook ? printedBook->getPages() : 0;
    return pages + countTotalPages(library, index + 1);
}

// Функция сортировки книг по названию
void sortBooksByTitle(std::vector<Book*>& library) {
    std::sort(library.begin(), library.end(), [](Book* a, Book* b) {
        return a->getTitle() < b->getTitle();
    });
}

int main() {
    std::vector<Book*> library;

    try {
        EBook* ebook = new EBook("1984", "George Orwell", 2, true, "EPUB", 1.5);
        PrintedBook* printedBook = new PrintedBook("To Kill a Mockingbird", "Harper Lee", 3, true, 281);

        addBook(library, ebook);
        addBook(library, printedBook);

        library[0]->display();
        library[1]->display();

        searchBook(library, "1984");
        searchBook(library, "Unknown Book");

        saveToFile(library, "library.txt");
        library.clear();
        loadFromFile(library, "library.txt");
        if (!library.empty()) {
            library[0]->display();
        }

        updateAvailability(library, 2, false);

        std::cout << "Total pages in printed books: " << countTotalPages(library) << std::endl;

        sortBooksByTitle(library);
        std::cout << "Books sorted by title:" << std::endl;
        for (const auto& book : library) {
            book->display();
        }

        removeBook(library, 2);

        User exampleUser("John Doe", 101);
        exampleUser.display();

        // Освобождение памяти
        for (auto& book : library) {
            delete book;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
