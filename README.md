# Tic-Tac-Toe Kernel Conversion for Raspberry Pi 3

This GitHub repository is dedicated to the creation of a Tic-Tac-Toe kernel specifically for the Raspberry Pi 3 ARM architecture. Specifically using the existing kernel structure from rsta2/circle.

## Table of Contents
- [Introduction](#introduction)
- [Project Goal](#project-goal)
- [Getting Started](#getting-started)
- [Contributing](#contributing)
- [License](#license)

## Introduction

Tic-Tac-Toe is a classic game enjoyed by people of all ages. This project aims to adapt a bare-metal kernel to the ARM architecture, making it compatible with the Raspberry Pi 3, a popular single-board computer. 

## Project Goal

The primary goal of this project is to build an rasberry pi kernel and make it compatible with the pi's ARM architecture. By doing this, we will enable the game to run smoothly on the Raspberry Pi 3, which is widely used for educational, hobbyist, and embedded computing projects. This conversion will allow enthusiasts and developers to enjoy playing Tic-Tac-Toe on their Raspberry Pi 3 devices but showcases how difficult it can be to implement your own kernel.

## Getting Started

Before you begin contributing or using the converted Tic-Tac-Toe kernel, please make sure you have the necessary tools and software installed. Follow these steps:

1. **Raspberry Pi 3**: Ensure you have a Raspberry Pi 3 board available.

2. **Linux Distribution**: Install a compatible Linux distribution on your Raspberry Pi 3. Raspbian is a popular choice, and you can download it from the official Raspberry Pi website.

3. **Cross-Compilation Setup**: You will need a cross-compiler to build the ARM-compatible kernel. Set up your development environment following the Raspberry Pi documentation for cross-compilation.

4. **Clone This Repository**: Clone this repository to your local machine using the following command:

   ```bash
   git clone https://github.com/Chasinggoodgrades/FranckenatorProductions.git
   ```

5. **Build and Run**: Follow the instructions in the repository to build and run the Tic-Tac-Toe kernel on your Raspberry Pi 3.

## Contributing

We welcome contributions from the open-source community to help us achieve the project's goal. If you have ideas, improvements, or bug fixes, please feel free to open issues and submit pull requests.

Please adhere to the following guidelines when contributing:

- Fork this repository and create your branch from the `main` branch.
- Keep your code clean and well-documented.
- Test your changes thoroughly before submitting a pull request.
- Be respectful and constructive in your interactions with other contributors.

## Additional Resources

- [Create Your Own Kernel In C#](https://www.codeproject.com/Articles/1225196/Create-Your-Own-Kernel-In-C-2) - This CodeProject article provides valuable insights into creating a kernel in C# and was our primary inspiration for this project. 
- [Circle Bare Metal Project](https://github.com/rsta2/circle) - Our project was built off using the kernel structure of this project and allowing us to use USB devices. 


## License

This project is open-source and is released under the GNU License. Please see the [LICENSE](LICENSE) file for more details.

Thank you for your interest in the Tic-Tac-Toe Kernel Conversion for Raspberry Pi 3 project! We look forward to your contributions and hope that this project will be a fun and educational experience for all involved.
