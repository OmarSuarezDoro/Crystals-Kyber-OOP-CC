# Implementation of Crystals Kyber Algorithm
Authors:
- **Omar Suárez Doro** (alu0101483474@ull.edu.es)
- **Edgar Pérez Ramos** (alu0101207667@ull.edu.es)
- **Pino Caballero Gil** (pcaballe@ull.edu.es)
## 1. Index
- [1. Index](#1-index)
- [2. Abstract](#2-abstract)
- [3. Why C++?](#3-why-c)
- [4. Main Concepts](#4-main-concepts)
- [5. Components](#5-components)
  - [a) Data Structures](#a-data-structures)
  - [b) Keccak](#b-keccak)
  - [c) ]()



## 2. Abstract
This repository contains a C++ implementation of **Crystals Kyber Algorithm**(CKA). The CKA is a standard in **Post Quantum Cryptography**(PQC), which development is driven by National Institute of Standards and Technology ([NIST](https://www.nist.gov/)).

## 3. Why C++?
The main purpouse of this repository is to document the CKA in a **didactic way**. Despite the fact that C++ is a language which learning curve is really steep, it provides a lot of features that may help by the time you are learning how Kyber works. One of this features is the **Object Oriented Programming**(POO), that allow us to understand kyber as some pieces or components that work together to bring us Well Developed cryptographyc scheme.

## 4. Main Concepts

| Concept | Short Description |
| ------- | ----------------- |
| Lattice | A lattice is a mathematic structure, which is built by lineal combinations of a n -vectors, where n define the dimention of the lattice. |
|LWE problem | The **learning with errors** problem consist in, having a vectorial base and a point (P) in the plane. Discover which lineal combination of the vectors should we use, in order to be in the closest point to P.
 

## 5. Components

### a) Data Structures
Our implementation of CKA is based in two **primitive** structures, which hold the main data.

1. **Polynomial**: This class represents a polynomial and provide us with some useful functionalities such as the *addition*, *print_operation*, etc.. It is mapped using a **vector structure** of T, where T is a template parameter.

Example of use:
```c++
Polynomial<int> poly1_ = Polynomial<int>(3);
Polynomial<int> poly2_ = Polynomial<int>(3);
    poly1_[0] = 1;
    poly1_[1] = 2;
    poly1_[2] = 3;
    poly2_[0] = 4;
    poly2_[1] = 5;
    poly2_[2] = 6;
Polynomial<int> result = poly1_ + poly2_;
```

2. **Matrix**: This class represents a matrix of T type, which T is the template parameter, as the previous one. This class follows a desing pattern called **Facade** in order to make easy to work with a 3 dimensional vectors structure.

Example of use:
```c++
Matrix<Polynomial<int>> mat4_ = Matrix<Polynomial<int>>(2, 2, 3);
Matrix<Polynomial<int>> mat5_ = Matrix<Polynomial<int>>(2, 2, 3);
    Polynomial<int> p1 = Polynomial<int>(3);
    p1[0] = 3;
    p1[1] = 2;
    p1[2] = 1;
    Polynomial<int> p2 = Polynomial<int>(3);
    p2[0] = 4;
    p2[1] = 3;
    p2[2] = 2;
    mat4_(0, 0) = p1;
    mat4_(0, 1) = p2;
    mat5_(0, 0) = p1;
Matrix<Polynomial<int>> result = mat4_ + mat5_;
```

3. **Bytes**: This class implements a set of bytes. They are mapped as `std::string` object, due to its facility in char(which have a size of 1 Byte, as 8 bits). The main reason of using our own **Byte Structure** is to follow facade patterns, in order to simplify the management of some custom **data structures** that libraries like [Crypto++](https://github.com/weidai11/cryptopp) use.

The bytes structure work with each bytes as **Little Endian** way, that means that the left Byte is the less significant. However, bits are interpreted from right to left (the common way to read binary).


The bytes structure allow us to make operations with Bytes in a simple way. Hereis a list of some methods that are included in this class:
- operator+ : which make the concatenation
- bitwise operations like and (&), or (|), not(~)..
- operator<< and operator>> : which will make a shift in any char that the string has. **CAREFUL!** It doesn't take care of carrying bits, it will make shift operation in any byte, and the bits that are overflowed will dissapear. **TAKE CARE OF THIS**.
- A few methods of transformation:
  - FromBytesToBits: Return a string of the bit representation of each byte.
  - FromBytesToHex: Return a string of hex representation of each byte.
  - FromBytesToNumbers: Return a long with the value of the bytes, It iterates, adding each bit * 2^n to the result.
  - GetBytesAsNumbersVector: Return an int vector that contains each separated int value of the bytes.
 

### b) Keccak
The Keccak component consists in a set of **Cryptographic functions** which are provided by the [Crypto++](https://github.com/weidai11/cryptopp) library. Keccak is structured by static methods (this is because, in our opinion, it is easy to understand the kyber as boxes that implements a set of functions that we will need), that we will call **"Logic Gates"**.

This Logic Gates operates with privates methods which use the functions of the library Cryto++ and return our custom byte structure. This logic gates are:

|Gate | Description |
| --- | --- |
|Extendable-output function (**XOF**)| Is an extension of the cryptographic hash that allows its output to be arbitrarily long.|
|Pseudorandom function family(**PRF**)|Is a collection of efficiently-computable functions which emulate a random oracle in the following way: no efficient algorithm can distinguish (with significant advantage) between a function chosen randomly from the PRF family and a random oracle (a function whose outputs are fixed completely at random).|
|Key derivation function (**KDF**) | Is a cryptographic algorithm that derives one or more secret keys from a secret value such as a master key, a password, or a passphrase using a pseudorandom function|


- G : TODO - FALTA PONER QUE PROPÓSITO REAL TIENEN Y ACRÓNIMO
- H : TODO - FALTA PONER QUE PROPÓSITO REAL TIENEN Y ACRÓNIMO


### c) Bytes



