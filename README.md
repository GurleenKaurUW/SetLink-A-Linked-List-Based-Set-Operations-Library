# SetLink-A-Linked-List-Based-Set-Operations-Library
Developed a C++ library that implements set operations (union, intersection, etc.) using linked lists, including advanced features like move semantics and operator overloading. Ensured efficient memory management and functionality for insertion, deletion, and search operations.

# SetLink: A Linked List-Based Set Operations Library

## Overview

SetLink is a C++ library that implements a set of mathematical operations and data structure functionalities based on linked lists. The library supports the creation, modification, and manipulation of sets using various operations like union, intersection, difference, and symmetric difference. It provides efficient methods for adding, removing, and searching elements, while maintaining the properties of a set (unique elements).

This project focuses on leveraging the flexibility of linked lists to perform set operations without duplicating data. It also supports advanced features like move semantics, merge operations, and comparison operators.

## Key Features

- **Set Operations**: 
  - Union (`|`), Intersection (`&`), Symmetric Difference (`^`), and Difference (`-`)
  - Overloaded operators for easy manipulation of sets (e.g., `|=`, `&=`, `^=`, `-=`).

- **Basic Operations**:
  - Insertion (`insert()`), Deletion (`erase()`), and Search (`find()`).
  - Checking if the set is empty (`empty()`), and retrieving the size (`size()`).
  - Merge (`merge()`) to combine sets with unique values.

- **Advanced Functionality**:
  - Copy and Move Constructors
  - Copy and Move Assignment Operators
  - Subset Comparison Operators (`>=`, `<=`, `>`, `<`, `==`, `!=`)

- **Efficient Memory Management**: Uses a linked list to store elements, ensuring that there is no redundant data and that elements are accessed efficiently.

## Example Usage

```cpp
#include "SetLink.h"

int main() {
    // Create a set using an initializer list
    Set set1{1, 2, 3, 4, 5};

    // Perform set operations
    set1 |= Set{4, 5, 6};  // Union
    set1 &= Set{3, 4};     // Intersection
    set1 -= Set{1};        // Difference

    // Check set properties
    std::cout << "Set size: " << set1.size() << std::endl;  // Output: 3
    std::cout << "Set is empty: " << set1.empty() << std::endl;  // Output: false

    return 0;
}

Installation
Clone the repository to your local machine:

bash
Copy code
git clone https://github.com/your-username/setlink.git


