#ifndef NONCOPYCLASS_HPP_
#define NONCOPYCLASS_HPP_

class NonCopyClass {
public:
    // Default constructor
    NonCopyClass() = default;

    // Destructor (defaulted as there's no custom cleanup)
    ~NonCopyClass() = default;

    // Delete the copy constructor and assignment operator
    NonCopyClass(const NonCopyClass&) = delete;
    NonCopyClass& operator=(const NonCopyClass&) = delete;
};

#endif  // NONCOPYCLASS_HPP_
