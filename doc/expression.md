# Technical Documentation on Expression Processing and Optimization
## Introduction
This document outlines the methods used in processing expressions with key optimizations including Constant Propagation and Common Subexpression Elimination (CSE). These techniques enhance expression evaluation efficiency and are integral to high-performance computing applications.

## Optimization Techniques and Their Benefits
### Constant Propagation
**Definition**: Constant Propagation involves evaluating expressions with constant operands at compile time, thereby replacing them with their computed values.

**Benefits**:

- Performance Enhancement: Reduces runtime computation by pre-computing constant expressions.
- Code Simplification: Results in simpler, more readable code by substituting constants directly into expressions.
- Memory Efficiency: Lessens the memory footprint by reducing the number of operations stored in memory.

### Common Subexpression Elimination (CSE)
**Definition**: CSE is an optimization that identifies and removes duplicate subexpressions, ensuring each unique expression is computed only once.

**Benefits**:

- Decreased Redundancy: Avoids repeated calculations by recognizing and reusing previously computed expressions.
- Execution Efficiency: Speeds up program execution by minimizing unnecessary computations.
- Resource Optimization: Saves computational resources and memory by eliminating duplicate storage of identical expressions.

## Approach to Expression Tree Processing
In my implementation, the optimization processes are separated from the traversal of the expression tree to simplify the handling logic.

### Expression Tree to Array Conversion
1. Tree Traversal: Initially, the expression tree is traversed without performing any optimization.
2. Node Array Creation: Nodes from the tree are sequentially pushed into an array. This conversion allows for easier manipulation and optimization of nodes outside the complex tree structure.
### Array Processing for Optimization
1. Sequential Evaluation: The array is processed from beginning to end, ensuring that nodes dependent on previous calculations are handled appropriately.
2. Constant Evaluation: As each node is examined, any constant expressions that can be computed are evaluated, and dependencies are updated accordingly.

## Functions Deduplication Logic
### Overview
The deduplication of function nodes involves identifying and storing only unique operations within an array, thereby eliminating redundant evaluations.

### Detailed Steps
1. Initialization:

- Create an empty list named unique to hold function nodes that are distinct.

2. Node Traversal and Comparison:

- For each function node in the expression array, perform a series of checks to ascertain its uniqueness.

3. Function Identity Check:

- Function Name: Compare the function name of the current node against those in the unique list. If a match is found, proceed to compare parameters.

4. Parameter Comparison:

- Recursive Evaluation: Each function node includes parameters which are also nodes. Conduct a recursive comparison of these parameters with those in the nodes within unique.
  
- Parameter Count: Ensure the number of parameters is the same. If they differ, the nodes are distinct and the comparison stops.

- If all parameters match recursively, the function nodes are identical.

5. Adding Unique Nodes:

- If no identical node is found in unique, add the current function node to the list.

### Example
Consider two nodes, f1 and f2, both representing the function "add" with [x, y] as parameters:

- Function Name Check: Verify that both nodes are named "add".

- Parameter Recursion: Recursively verify:
  - First parameter of f1 (x) with f2 (x).
  - Second parameter of f1 (y) with f2 (y).
  
- If both checks pass, f1 and f2 are duplicates, and only one is stored in unique.

### Conclusion
This systematic approach ensures only unique function operations are retained, thus optimizing the expression evaluation process by avoiding redundant calculations and reducing memory usage.
