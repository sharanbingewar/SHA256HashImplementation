# SHA-256 Hashing of the Book of Mark

## Project Overview

This project implements the **SHA-256** hashing algorithm to generate a unique cryptographic hash for the entire *Book of Mark* from the Revised Standard Version Bible. SHA-256 is a widely used hash function that ensures data integrity by producing a unique output for every input. If the input data changes, even slightly, the hash will completely change, making it an essential tool in fields like blockchain technology.

By applying SHA-256 to the *Book of Mark*, this project demonstrates how the algorithm works and how it ensures the immutability of data. Think of this as creating a **digital fingerprint** for the *Book of Mark*—this fingerprint is unique and will change only if the original text is altered.

## Technologies and Tools Used

- **C++**: The main programming language used to implement the SHA-256 algorithm.
- **SHA-256**: A secure hash algorithm that produces a 256-bit (32-byte) hash value from the input data.

## What is SHA-256?

SHA-256 is a cryptographic hash function from the SHA-2 family, designed to take any input, like the *Book of Mark*, and produce a fixed-length output—a 64-character hexadecimal string. This output serves as a unique identifier for the input data. Even the smallest change to the input results in a completely different hash, making it highly useful for data integrity checks and digital security.

### How Does the SHA-256 Algorithm Work?

1. **Padding**: The text is padded to ensure that its length is a multiple of 512 bits, allowing the algorithm to function correctly.
2. **Chunking**: The padded text is divided into 512-bit chunks.
3. **Processing**: Each chunk undergoes multiple rounds of complex mathematical operations that mix the data. These operations make it computationally infeasible to reverse-engineer the original input from the hash.
4. **Hash Output**: After processing all the chunks, the algorithm outputs a **256-bit hash**, represented as a 64-character hexadecimal string.

This final hash acts as the digital fingerprint for the text—the same input will always produce the same hash, while even the smallest modification to the input will produce a completely different hash.


## Possible Improvements

- **URL-based Input**: Currently, the program reads the text from a file. Future versions could read directly from a URL, simplifying the process of fetching data from the web.
- **Larger Dataset Optimization**: While this implementation works well for the *Book of Mark*, it could be optimized to handle larger datasets more efficiently.
- **Parallelization**: For larger datasets, parallelizing parts of the algorithm could significantly speed up the hashing process.

---

Thank you for exploring this project on **SHA-256 Hashing of the Book of Mark**!
