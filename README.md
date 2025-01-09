# Data Structures Project

## Overview
This project is a data structures assignment focused on managing a set of pizza stores and their branches using data structures like **Hash Tables**, **Linked Lists**, and **2D-Trees**. It supports various operations such as adding and removing stores, managing branches, searching for nearby stores, and undoing previous operations.

---

## Features

- **Add Neighborhood:** Add a neighborhood with specified rectangular coordinates.
- **Add Main Pizza Store:** Add a main pizza store at specified coordinates.
- **Add Pizza Store Branch:** Add a branch of an existing pizza store at specified coordinates.
- **Remove Pizza Store Branch:** Remove a branch of a pizza store at specified coordinates.
- **List All Pizza Stores in a Neighborhood:** List all pizza stores located within a specified neighborhood.
- **List All Branches of a Pizza Store:** List all branches of a specified pizza store.
- **Find Nearest Pizza Store:** Find the nearest pizza store to specified coordinates.
- **Find Nearest Branch of a Pizza Store:** Find the nearest branch of a pizza store to specified coordinates.
- **List All Accessible Pizza Stores:** List all pizza stores within a specified radius from given coordinates.
- **Find Pizza Store with Most Branches:** Find the pizza store with the most branches.
- **Undo Operations:** Revert the program to a previous state based on a specified number of undo steps.

---

## Requirements
- C++ compiler supporting C++11 or later
- Console for input and output

---

## Commands

### **Add Neighborhood**
```bash
Add-N [NEIGHBORHOOD_NAME] [X1] [Y1] [X2] [Y2]
```
* Adds a neighborhood with the specified name and rectangular coordinates (X1, Y1) to (X2, Y2).

### **Add Main Pizza Store**
```bash
Add-P [PIZZA_STORE_NAME] [X] [Y]
```
* Adds a main pizza store with the specified name at coordinates (X, Y).

### **Add Pizza Store Branch**
```bash
Add-Br [BRANCH_NAME] [PIZZA_STORE_NAME] [X] [Y]
```
* Adds a branch for an existing pizza store at coordinates (X, Y).

### **Remove Pizza Store Branch**
```bash
Del-Br [BRANCH_NAME] [X] [Y]
```
* Removes the specified branch of a pizza store at the given coordinates.

### **List All Pizza Stores in a Neighborhood**
```bash
List-P [NEIGHBORHOOD_NAME]
```
* Lists all pizza stores located within the specified neighborhood.

### **List All Branches of a Pizza Store**
```bash
List-Brs [PIZZA_STORE_NAME]
```
* Lists all branches of the specified pizza store.

### **Find Nearest Pizza Store**
```bash
Near-P [X] [Y]
```
* Finds the nearest pizza store to the specified coordinates.

### **Find Nearest Branch of a Pizza Store**
```bash
Near-Br [PIZZA_STORE_NAME] [X] [Y]
```
* Finds the nearest branch of a pizza store at the specified coordinates.

### **List All Accessible Pizza Stores**
```bash
Avail-P [X] [Y] [RADIUS]
```
* Lists all pizza stores within the specified radius from the given coordinates.

### **Find Pizza Store with Most Branches**
```bash
Most-Brs
```
* Finds the pizza store with the most branches.

### **Undo Operations**
```bash
Undo [NUMBER_OF_STEPS]
```
* Reverts the program to a previous state based on the specified number of undo steps.

---

## Example
```bash
Add-N Downtown 0 0 10 10
Add-P PizzaHut 5 5
Add-Br Branch1 PizzaHut 6 6
List-P Downtown
Near-P 5 5
Undo 1
```

---

## Important Notes

- All searches and queries are based on the **2D-Tree** data structure.
- **Hash Tables** and **Linked Lists** are used for efficient data storage and management.
- Comprehensive error handling is implemented for invalid inputs and operations.
- The project follows object-oriented principles and adheres to C++ best practices.



