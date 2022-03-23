//
// Created by leeiozh on 22.03.2022.
//

#ifndef MINI_PROJECT_EXCEPTION_HPP
#define MINI_PROJECT_EXCEPTION_HPP

#include <exception>
#include <sstream>
#include <string>

class BaseException : public std::exception {
    /* Базовый класс исключения в пакетах С++ */
protected:
    /* Поля класса */
    std::string message_;

public:
    /* Конструкторы класса */
    /** Constructor (C++ STL strings).
       *  @param message The error message.
     */
    inline explicit BaseException(const std::string &message) noexcept: BaseException(message.c_str()) {}

    /** Constructor (C strings).
       *  @param message C-style string error message.
       *                 The string contents are copied upon construction.
       *                 Hence, responsibility for deleting the char* lies
       *                 with the caller.
     */
    inline explicit BaseException(const char *message) noexcept: message_(message) {}

    /*  Методы класса */
    /** Returns a pointer to the (constant) error description.
       *  @return A pointer to a const char*. The underlying memory
       *          is in posession of the Exception object. Callers must
       *          not attempt to free the memory.
     */
    [[nodiscard]] const char *what() const noexcept { return message_.c_str(); };
};


#endif //MINI_PROJECT_EXCEPTION_HPP
