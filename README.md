Authors:
- **Omar Suárez Doro** (alu0101483474@ull.edu.es)
- **Edgar Pérez Ramos** (alu0101207667@ull.edu.es)
- **Pino Caballero Gil** (pcaballe@ull.edu.es)
## 1. Index
- [1. Index](#1-index)
- [2. Abstract](#2-abstract)
- [3. Why C++?](#3-why-c)
- [4. Main Concepts](#4-main-concepts)
  - [a) Lattices](#a-lattices)
  - [b) Learning With Errors Problem](#b-learning-with-errors-problem)
  - [c) Polynomial Ring](#c-polynomial-ring)
  - [d) Finite Field](#d-finite-field)
- [5. Parameters and Specifications](#5-parameters-and-specifications)
- [6. Components](#6-components)
  - [a) Data Structures](#a-data-structures)
  - [b) Keccak](#b-keccak)
  - [c) Sampling Unit](#c-sampling-unit)
  - [d) NTT](#d-ntt-number-theoric-transform)



## 2. Abstract
This repository contains a C++ implementation of **Crystals Kyber Algorithm**(CKA). The CKA is a standard in **Post Quantum Cryptography**(PQC), which development is driven by National Institute of Standards and Technology ([NIST](https://www.nist.gov/)).


## 3. Why C++?
The main purpouse of this repository is to document the CKA in a **didactic way**. Despite the fact that C++ is a language which learning curve is really steep, it provides a lot of features that may help by the time you are learning how Kyber works. One of this features is the **Object Oriented Programming**(POO), that allow us to understand kyber as some pieces or components that work together to bring us Well Developed cryptographyc scheme.

## 4. Main Concepts

The first thing we need to do, in order to understand Kyber is learning about **Mathematical fundamentals** that Kyber is based (don't be afraid, I am bad at Maths too). In cryptography, we need problems that are easy to solve for the device we are communication with, and hard for others, for example, attackers that are sniffing the traffic over the network where messages are being sent. Crystals Kyber Algorithm uses mathematical structures known as **lattices**, and the problem that we are going to use is the Learning With Errors Problem

### a) Lattices
A lattice is a mathematical structure which is created using integer lineal combinations  of a **vectorial base**. This means that having two vectors $\vec{a}$ and $\vec{u}$ and making some lineal combinations like ($2 \cdot \vec{a} + 1 \cdot \vec{u}$) or ($2 \cdot \vec{u}$) we can generate a lattice. Here is a visual way:

<div align="center"><img src="https://upload.wikimedia.org/wikipedia/commons/c/c3/Bravais_Lattices.gif" height=200px /> </div>
<br>

> [!note]
> It is important to keep in mind that **different vectors** can generate the **same** lattice
>

### b) Learning With Errors Problem
Suppose that somehow we can represent messages in the points of the lattice that we are going to use and we have a *equations system* that we need to solve, in order to get the key, and therefore, decypher the encrypted message. The solution of this system is the exact lineal combination to get the point that represent the message. This sounds weird, because seems like bruteforce mixed with Gauss Method, substitution could break this scheme.
<br>

<div align="center"> <img src="https://latex.codecogs.com/svg.image?\inline&space;\LARGE&space;\bg{white}{\color{White}\begin{eqnarray}2x&plus;y=1\\x&plus;y=4\\x&plus;y&plus;z=6\end{eqnarray}}" title="{\color{White}\begin{eqnarray}2x+y=1\\x+y=4\\x+y+z=6\end{eqnarray}}" /> </div>

<br>

The answer is **YES**. That is the reason that we are going to introduce a little "noise" or "error" in the system:

<br>

<div align="center"> <img src="https://latex.codecogs.com/svg.image?\inline&space;\LARGE&space;\bg{white}{\color{White}\begin{eqnarray}2x&plus;y=1-{\color{red}1}\\x&plus;y=4-{\color{red}3}\\x&plus;y&plus;z=6-{\color{red}2}\end{eqnarray}}" title="{\color{White}\begin{eqnarray}2x+y=1-{\color{red}1}\\x+y=4-{\color{red}3}\\x+y+z=6-{\color{red}2}\end{eqnarray}}" /> </div>

<br>

The change is simple, but the problem is a way **different**. The problem now consists in guessing the closest point to the solution. The thing here is that if we know the secret key, that could be compared to having a good vectorial base, solve this problem is a way easier than didn't have it, which means having a bad base.


### c) Polynomial ring
Crystals Kyber Algorithm use numbers contained in a polynomial ring, which allow us to work with modular operations, enhancing memory space needed and working in a finite field:

<div align="center"> <img src="https://latex.codecogs.com/svg.image?\inline&space;\LARGE&space;\bg{white}{\color{White}\{\mathbb{Z}_q[x]/(x^n&plus;1)\}}" title="{\color{White}\{\mathbb{Z}_q[x]/(x^n+1)\}}" /> </div>
<br>

Which basically means numbers contained in the interval of module operation.
Here it's a table that resume the main concepts that you should keep in mind:

| Concept | Short Description |
| ------- | ----------------- |
| Lattice | A lattice is a mathematic structure, which is built by lineal combinations of a n -vectors, where n define the dimention of the lattice. |
|LWE problem | The **learning with errors** problem consist in, having a vectorial base and a point (P) in the plane. Discover which lineal combination of the vectors should we use, in order to be in the closest point to P.
|Big O notation (**O(n)**)| Is a standard which function describe the time that an algorithm needs to be completed. This notation focussed in the **worst case** with a sample of n elements.|
 
 <br>

### d) Finite field
A Finite field, also known as *Body*, is a finite set of elements on which algebraic operations such as addition, subtraction, multiplication, and division (except for zero) are defined, which fulfill certain properties:

- Finite number of elements: A finite body contains a finite number of elements, generally denoted as $\mathbb{F} _q$ , where  q is the number of elements in the field.
- Modular Arithmetic: Operations in a finite body often use modular arithmetic, are performed in modulus q, where q is the prime established.
- Properties of operations: The addition, subtraction, multiplication and division (except for 0) are well defined operations and fulfill the associative, commutative, distributive properties and have neutral elements.

<br>

## 5. Parameters and Specifications

Crystals Kyber Algorithm needs a set of parameters, here it is an explanation of each one:
| Parameter | In code | Description |
| --- | --- | --- |
| n | n | The grade of the polynomials that we will use (the size).|
| q | q | The prime that we will use to make the module.|
| k | k | The size of the matrix.|
| $\eta_1$, $\eta_2$ | n1, n2 | The parameters that we will use to generate the random distribution. |
| du, dv | du, dv | The parameters of compressions, in order to reduce the size of the keys and cyphered|

Once we know about the parameters, we can talk about the differents specifications of Crystals Kyber:

| Specification | NIST Security Level | Compared to | n | k | q | Size secret-key(bytes) | Size public-key(bytes) | Size cyphered-text(bytes) |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Kyber512 | 1 |  RSA-2048 o AES-128 | 256 | 2 | 3329 | 1632 | 800 | 768 |
| Kyber768 | 3 |  RSA-3072 o AES-192 | 256 | 3 | 3329 | 2400 | 1184 | 1088 |
| Kyber1024 | 4 |  RSA-4096 o AES-256 | 256 | 4 | 3329 | 3168 | 1568 | 1568 |


### Why do we select this numbers?
- The **n(256)** and **q(3329)** numbers are selected in order to equilibrate between security and efficiency. Notice that the prime is close to a power of 2. being easier the calculations.
- The $\eta$ value (2) keeps the value low, because we want to have a little error, and recuperate the original point.

## 6. Components

### a) Data Structures
Our implementation of CKA is based in two **primitive** structures, which hold the main data.

- **Polynomial**: This class represents a polynomial and provide us with some useful functionalities such as the *addition*, *print_operation*, etc.. It is mapped using a **vector structure** of T, where T is a template parameter.

Example of use:
```c++
Polynomial<int> poly1_ = Polynomial<int>(3);
Polynomial<int> poly2_ = Polynomial<int>(3);
    poly1_[0] = 1;
    poly2_[1] = 5;
Polynomial<int> result = poly1_ + poly2_; // [6, 0, 0]
```
<br>
<br>

- **Matrix**: This class represents a matrix of T type, which T is the template parameter, as the previous one. This class follows a desing pattern called **Facade** in order to make easy to work with a 3 dimensional vectors structure.

Example of use:
```c++
Matrix<Polynomial<int>> mat4_ = Matrix<Polynomial<int>>(2, 2, 3);
Matrix<Polynomial<int>> mat5_ = Matrix<Polynomial<int>>(2, 2, 3);
    Polynomial<int> p1 = Polynomial<int>(3);
    // Initialize the values
    Polynomial<int> p2 = Polynomial<int>(3);
    // Initialize the values
    mat4_(0, 1) = p2;
    mat5_(0, 0) = p1;
Matrix<Polynomial<int>> result = mat4_ + mat5_;
```

<br>
<br>


- **Bytes**: This class implements a set of bytes. They are mapped as `std::vector<unsigned char>` object, this is because we have the entire **8 bits** range representation. If we have used normal char 1 bit is used for sign representation, this is not a real problem in representation operations, but it is **highly** important in arithmethic operations. If we want to operate in a signed way, we can use the signed version of methods. The main reason of using our own **Byte Structure** is to follow facade patterns, in order to simplify the management of some custom **data structures** that libraries like [Cryptopp](https://github.com/weidai11/cryptopp) use.

The bytes structure work with each bytes as **Little Endian** way, that means that the left Byte is the less significant. However, bits are interpreted from right to left (the common way to read binary).



The bytes structure allow us to make operations with Bytes in a simple way. Hereis a list of some methods that are included in this class:

| **Method**                      | **Description**                                                                                                                                                                |
|----------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `operator+`                      | Performs concatenation of byte sequences.                                                                                                                                      |
| Bitwise operations               | Supports bitwise operations such as `and (&)`, `or (|)`, and `not (~)`.                                                                                                       |
| `operator<<` and `operator>>`    | Performs a shift operation on each byte in the string. **CAREFUL**: Does not manage carry bits; overflowed bits are discarded. **TAKE CARE OF THIS**.                          |
| **Transformation Methods**       | **Description**                                                                                                                                                               |
| `FromBytesToBits`                | Returns a string with the bit representation of each byte.                                                                                                                    |
| `FromBytesToHex`                 | Returns a string with the hex representation of each byte.                                                                                                                    |
| `FromBytesToNumbers`             | Returns a long integer representing the value of the bytes by iterating over each bit and adding `bit * 2^n` to the result.                                                   |
| `GetBytesAsNumbersVector`        | Returns a vector of integers, each representing the individual value of each byte.                                                                                            |

<br>

### b) Keccak
The Keccak component consists in a set of **Cryptographic functions** which are provided by the [Cryptopp](https://github.com/weidai11/cryptopp) library, also known as Crypto++. Keccak is structured by static methods (this is because, in our opinion, it is easy to understand the kyber as boxes that implements a set of functions that we will need) that we will refer to them, for simplicity, **"Logic Gates"**.

This Logic Gates operates with privates methods which use the functions of the library Crytopp and return our custom `Byte` structure. This logic gates are:

|Gate | Description |
| --- | --- |
|Extendable-output function (**XOF**)| Is an extension of the cryptographic hash that allows its output to be arbitrarily long.|
|Pseudorandom function family(**PRF**)|Is a collection of efficiently-computable functions which emulate a random oracle in the following way: no efficient algorithm can distinguish (with significant advantage) between a function chosen randomly from the PRF family and a random oracle (a function whose outputs are fixed completely at random).|
|Key derivation function (**KDF**) | Is a cryptographic algorithm that derives one or more secret keys from a secret value such as a master key, a password, or a passphrase using a pseudorandom function|
|(**H**) |Hash function used to derive cryptographic material (seed for public matrix A, coins, shared keys) from arbitrary-length byte strings. Output is a 32-byte string.|
|(**G**)|Hash function used to generate noise polynomials for the secret key. Output is a concatenation of two 32-byte strings.|

<br>

### c) Sampling Unit
The Sampling unit is a component that is going to generate samples of noise (the errors, which envolves the LWE problem, described at [b) Learning With Errors Problem](#b-learning-with-errors-problem)) and also will be used to generate random polynomials which satisfies the security of the scheme. We need to keep in mind that to guarantee that the algorithm works, we need to introduce a distribution close to 0, so that the error is tiny, in order to recover the original data.

To make this possible *CKA* use **CBD(Central Binomial Distribution)**, which have:
- An accurate control of the noise generated
- Computacional efficiency (less complex operations)
- Ensures the security of the scheme (ensures that the sample generated fulfill security conditions)


> [!NOTE]
> 
> ### Why do we use a Binomial distribution instead of a Normal(Gaussian) Distribution?
>
> First, we need to consider that the Binomial distribution is discrete instead of continuous, this is convenient because we need to generate 0s or 1s, we are not interested in values like 0.9.
> But we also consider: 
> - The simplicity of implementation
> - The accuracy in noice management

This component has two main methods, `GenerateDistributionMatrix` and `CBD_`.

The `GenerateDistributionMatrix` is used to generate a matrix of k x 1 dimention using the CBD:
```c++
std::pair<Matrix<Polynomial<int>>, int> SamplingUnit::GenerateDistribuitionMatrix(const Bytes& sigma, int eta, int N) {
  Matrix<Polynomial<int>> result_matrix(k_, 1, n_);
  for (int i = 0; i < k_; i++) {
    Bytes bytes_post_prf = Keccak::PRF(sigma, N, 64 * eta);
    Polynomial<int> result_poly = CBD_(bytes_post_prf, eta);
    result_matrix(i, 0) = result_poly;
    N += 1;
  }
  return {result_matrix, N};
}
```
By applying a** PRF logic gate** prior to the CBD, we can guarantee the determinism of the output, prevent biases in the distribution generation due to uncontrolled input factors, and enhance resistance to attacks by ensuring that the CBD input is always  pseudorandom. Notice that the valyue of N will be increased k times by 1, that means `N = N + k`.


The other method is `CBD_` which implements the **Central Binomial Distribution**:

```c++
Polynomial<int> SamplingUnit::CBD_(const Bytes& input_bytes, int eta) {
  if (64 >= input_bytes.GetBytesSize()) {
    throw std::invalid_argument("Input length is not correct.");
  }
  Polynomial<int> coefficients(n_);
  // REALLY IMPORTANT TO REVERT THE BYTES HERE!!!
  Bytes reverted_input_byte = input_bytes.ChangeByteDirection();
  std::string list_of_bits = reverted_input_byte.FromBytesToBits();
  for (int i = 0; i < n_; i++) {
    int a = 0;
    int b = 0;
    for (int j = 0; j < eta; j++) {
      a += list_of_bits[2 * i * eta + j] - '0';
      b += list_of_bits[2 * i * eta + eta + j] - '0';
    }
    coefficients[i] = a - b;
  }
  return coefficients;
}
```

Inversion of byte management in CBD sampling in Crystals-Kyber is done for **several key technical reasons**:
- Compatibility with internal representation of data and mathematical operations.
- Optimization of bit processing, improving sampling efficiency.
- Consistency in the order of the data, ensuring uniform and biased sampling.
- Prevention of biases that could compromise the safety of the scheme.
- Facilitating implementation in different hardware and software architectures.
- Compatibility with cryptographic standards and protocols.

### d) NTT (Number Theoretic Transform)

The NTT is a variant of the Discrete Fourier Transform (DFT), but it operates in a finite field instead of complex numbers. This allows for efficient computations with integers, which is crucial for cryptographic applications. The primary reason for using NTT in cryptographic schemes like Kyber is to **efficiently perform polynomial multiplication**.  

> [!Important]
>
> ### Complexity Decreased
> ---
> 
>The computational complexity is highly decreased due to this algorithm:
> <div align="center"> <img src="https://latex.codecogs.com/svg.image?\inline&space;\LARGE&space;\bg{white}{\color{White}O(n^2)\rightarrow&space;O(n\cdot&space;log(n))}" title="{\color{White}O(n^2)\rightarrow O(n\cdot log(n))}" /> </div>
>This happens because the following domain transformation is performed:
> <div align="center"> <img src="https://latex.codecogs.com/svg.image?\inline&space;\LARGE&space;\bg{white}{\color{White}R_q^{k\cdot&space;k}\rightarrow&space;R_q^k}" title="{\color{White}R_q^{k\cdot k}\rightarrow R_q^k}" /> </div>
> Where **q** is the prime that we are using in the algorithm and **k** the dimension.
> <div align="center"> <img src="https://latex.codecogs.com/svg.image?\inline&space;\LARGE&space;\bg{white}{\color{White}\begin{pmatrix}\begin{bmatrix}1&2&3\end{bmatrix}&\begin{bmatrix}1&2&3\end{bmatrix}\\\begin{bmatrix}1&2&3\end{bmatrix}&\begin{bmatrix}1&2&3\end{bmatrix}\end{pmatrix}_{R{^{k\cdot&space;k}_q}}\\\longrightarrow\begin{pmatrix}\begin{bmatrix}165\end{bmatrix}\\\begin{bmatrix}125\end{bmatrix}\\\end{pmatrix}_{R_q^k}}" title="{\color{White}\begin{pmatrix}\begin{bmatrix}1&2&3\end{bmatrix}&\begin{bmatrix}1&2&3\end{bmatrix}\\\begin{bmatrix}1&2&3\end{bmatrix}&\begin{bmatrix}1&2&3\end{bmatrix}\end{pmatrix}_{R{^{k\cdot&space;k}_q}}\\\longrightarrow\begin{pmatrix}\begin{bmatrix}165\end{bmatrix}\\\begin{bmatrix}125\end{bmatrix}\\\end{pmatrix}_{R_q^k}}" /> </div>
>
> ### How does it works?
> ---
> NTT takes a polynomial with coefficients in a **finite body** (explained at [d) Finite Field](#d-finite-field)), transform it into a way that makes **point-to-point** highly increasing the performance of the polynomial multiplication. We will see in PWMUnit section that this trasformations will make **pointwise multiplication** be a strong ally.
> <div align="center"> <img src="https://latex.codecogs.com/svg.image?{\color{White}x(k)=\sum_{j=0}^{n-1}x(j)\cdot\omega^{j\cdot%20k}\(mod\;q\)}" title="cosita" /> </div>




The main method that we need to use is the ``NTT_kyber`` which second parameter determinate if we are going to use **inverse NTT** or the **NTT operation**:
```C++
Polynomial<int> NTT::NTT_Kyber(const Polynomial<int>& kPolynomial, bool is_ntt) const{
  Polynomial<int> polynomial_copy = kPolynomial;
  if (kPolynomial.GetSize() != n_) {
    Polynomial<int> auxiliar(n_ - kPolynomial.GetSize());
    for (const auto& element : auxiliar.GetCoefficients()) {
      polynomial_copy.append(element);
    }
  }
  // Initialize polynomials
  Polynomial<int> even_coefficients = Polynomial<int>(0);
  Polynomial<int> odd_coefficients = Polynomial<int>(0);
  
  for (int i = 0; i < polynomial_copy.GetSize(); ++i) {
    (i % 2 == 0) ? even_coefficients.append(polynomial_copy[i]) : odd_coefficients.append(polynomial_copy[i]);
  }

  Polynomial<int> even_coefficients_ntt = is_ntt ? NTT_(even_coefficients) : INTT_(even_coefficients);
  Polynomial<int> odd_coefficients_ntt = is_ntt ? NTT_(odd_coefficients) : INTT_(odd_coefficients);
  // Merging results
  Polynomial<int> result = Polynomial<int>(0);
  for (int i = 0; i < n_; ++i) {
    (i % 2 == 0) ? result.append(even_coefficients_ntt[i / 2]) : result.append(odd_coefficients_ntt[(i - 1) / 2]);
  }
  return result;
}

```

This method split the polynomial coefficients using the index of the element in two different polynomials, then we apply the NTT or INTT to that polynomials, to end up merging the results.

Now lets see who `NTT_` method works:
```C++
Polynomial<int> NTT::NTT_(const Polynomial<int>& kPolynomial) const {
  int n = kPolynomial.GetSize();
  int mid_index = n / 2;
  // Calculate the first primitive root
  int phi = FirstPrimitiveRoot_(2 * n);

  Polynomial<int> result = kPolynomial;
  // Iterating over the polynomial - First we chunk the polynomial in sizes of 2 * i
  for (int i = 1; i < n; i *= 2) {
    // Iterating over the chunk that we've created
    for (int j = 0; j < i; ++j) {
      int left_interval = 2 * j * mid_index; 
      int right_interval = left_interval + mid_index - 1;
      int S = PowerWithMod_(phi, BitReverse_(i + j, n), q_);
      for (int k = left_interval; k <= right_interval; ++k) {
        int temp_element = result[k];
        int temp_mirror_element = result[k + mid_index];
        result[k] = (temp_element + temp_mirror_element * S) % q_;
        result[k + mid_index] = (temp_element - temp_mirror_element * S) % q_;
        while (result[k] < 0) { result[k] += q_; }
        while (result[k + mid_index] < 0) { result[k + mid_index] += q_; }
      }
    }
    mid_index /= 2;
  }
  return result;
}
```

To keep the explanation simple, here is the steps followed:
- Polynomial Reorganization: Before applying NTT, the polynomial coefficients are rearranged using a technique called bit reversal. This is necessary for subsequent operations to be performed efficiently.
- Block division: The polynomial is divided into blocks of increasing size (2, 4, 8, etc.), and operations are performed in each block that combine the coefficients.
- Multiplication with primitive roots: At each stage, the polynomial coefficients are combined using a scale factor that is calculated with a primitive root of the finite field.
- Modular addition and subtraction: The values of the coefficients are updated by adding and subtracting in a modular way (to ensure that the results are within the limits of the finite field).

The `INTT_`is the reverse method, and it is similar:
```C++
Polynomial<int> NTT::INTT_(const Polynomial<int>& kPolynomial) const {
  int n = kPolynomial.GetSize();
  int phi = FirstPrimitiveRoot_(2 * n);
  int phi_inverse = PowerWithMod_(phi, 2 * n - 1, q_);
  Polynomial<int> result = kPolynomial;
  int mid_index = n / 2;
  int k = 1;
  while (mid_index > 0) {
    for (int i = 0; i < mid_index; ++i) {
      int left_interval = 2 * i * k;
      int right_interval = left_interval + k - 1;
      int S = PowerWithMod_(phi_inverse, BitReverse_(mid_index + i, n), q_);
      for (int j = left_interval; j <= right_interval; ++j) {
        int temp_element = result[j];
        int temp_mirror_element = result[j + k];
        result[j] = (temp_element + temp_mirror_element) % q_;
        result[j + k] = ((temp_element - temp_mirror_element) * S) % q_;
        while (result[j] < 0) { result[j] += q_; }
        while (result[j + k] < 0) { result[j + k] += q_; }
      }      
    }
    mid_index /= 2;
    k *= 2;
  }
  // Every element in Zq pow q - 2 = inverse of n.
  int n_inverse = PowerWithMod_(n, q_ - 2 , q_);
  for (int i = 0; i < n; ++i) {
    result[i] = (result[i] * n_inverse) % q_; 
  }
  return result;
}
```

NTT also is used to generate a matrix by extending a seed, `GenerateMatrix` and `Parsepolynomial`:
```C++
Matrix<Polynomial<int>> NTT::GenerateMatrix_(int k_size, Bytes rho, bool traspose) const {
  Matrix<Polynomial<int>> matrix(k_size, k_size, n_);
  for (int i = 0; i < k_size; ++i) {
    for (int j = 0; j < k_size; ++j) {
      Bytes generated_bytes = Keccak::XOF(rho, Bytes(traspose ? j : i), Bytes(traspose ? i : j), 3 * n_);
      matrix(i, j) = ParsePolynomial_(generated_bytes);
    }
  }
  return matrix;
}

Polynomial<int> NTT::ParsePolynomial_(const Bytes& kBytes) const {
  Polynomial<int> polynomial(n_);
  int byte_index = 0;
  int list_index = 0;
  int size_bytes = kBytes.GetBytesSize();
  while ((list_index < n_) && (byte_index + 3 < size_bytes)) {
    int byte1 = kBytes[byte_index] + n_ * (kBytes[byte_index + 1] % 16);
    int byte2 = int(kBytes[byte_index + 1] / 16) + 16 * kBytes[byte_index + 2];
    if (byte1 < q_) {
      polynomial[list_index] = byte1;
      list_index++;
    }
    if (byte2 < q_ && list_index < n_) {
      polynomial[list_index] = byte2;
      list_index++;
    }
    byte_index += 3;
  }
  return polynomial;
}
```

The interesting method here is the `ParsePolynomial_` one:
- It loops though bytes three by three
- For each on, it calculates two numbers:
  - The first number is calculated by combining the first two bytes.
  - The second number is calculated from the second and third bytes.
  - If the calculated numbers are less than the q_ module, they are added to the polynomial.
- Repeat the process until the polynomial is complete or the bytes are exhausted.



### d) 
