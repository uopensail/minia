# Minia
Minia is an open-source C++ feature processing library designed to streamline the feature processing for model training and inference. By simply configuring a file, Minia ensures consistency in feature processing across both training and inference phases.

## Table of Contents
- [Minia](#minia)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Features](#features)
    - [Custom Expression Design with ANTLR](#custom-expression-design-with-antlr)
    - [Configuration-Based Processing](#configuration-based-processing)
    - [FlatBuffers-Based Feature Input](#flatbuffers-based-feature-input)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Expressions](#expressions)
    - [Supported Operations](#supported-operations)
  - [Data Types](#data-types)
  - [Contributing](#contributing)
  - [License](#license)
  - [Contact](#contact)

## Introduction
Minia aims to solve the discrepancies often encountered between feature processing during model training and inference. By leveraging a configuration-driven approach, users can define feature transformations using intuitive expressions, ensuring that the same transformations are applied consistently across different stages of model deployment.

## Features
### Custom Expression Design with ANTLR
Minia utilizes ANTLR to design custom expressions for feature transformation. This allows users to define complex feature transformations in a straightforward manner. 

### Configuration-Based Processing
Minia supports configuration-based processing using the TOML format, which simplifies the specification and management of feature transformations. The configuration system incorporates several key optimizations to enhance processing efficiency and performance:

- Expression Deduplication: Automatically identifies and removes duplicate expressions, reducing unnecessary computations and improving clarity.

- Constant Propagation: Analyzes and substitutes constant values directly into expressions wherever possible, reducing runtime calculations and enhancing execution speed.

- Constant Folding: Evaluates constant expressions at compile time instead of runtime, minimizing computational overhead.

- Common Subexpression Elimination: Detects and eliminates repeated subexpressions within the transformations, optimizing resource usage by avoiding redundant calculations.


Example Expressions:
```python
expressions = ['x = 5 + 5 + h', 'y = sqrt(x)', 'z = y * y']

```

### FlatBuffers-Based Feature Input
Features are inputted in FlatBuffers format, and Minia supports a variety of data types to handle diverse data inputs. This flexibility ensures that Minia can be integrated into various data workflows.

## Installation
Minia can be easily installed as a Python package using the provided setup.py. This allows for seamless integration into existing Python projects.
```bash
python setup.py install
```

## Usage
Minia's Python interface makes it easy to apply feature transformations. Below is a basic usage example:

```python
import pyminia

# Example configuration
m = pyminia.Minia(['x = 5 + 5 + h', 'y = sqrt(cast(x))', 'z = y*y'])
print(m({"c": {"type": 0, "value": 5}}))

# output: {'a': 1, 'b': 6}
```

## Expressions
The expressions are written in strings , which define how features should be transformed. This approach simplifies the process of updating and managing feature transformations.

### Supported Operations
| Operation      | Description                                                    |
| -------------- | -------------------------------------------------------------- |
| hash           | Computes a hash value for the input.                           |
| <              | Checks if the left operand is less than the right operand. | 
| <=             | Checks if the left operand is less than or equal to the right operand. | 
| ==             | Checks if the left operand is equal to the right operand. | 
| !=             | Checks if the left operand is not equal to the right operand. | 
| >=             | Checks if the left operand is greater than or equal to the right operand. | 
| >              | Checks if the left operand is greater than the right operand. | 
| contains       | Checks if a value exists within an iterable (e.g., list, tuple, or string). | 
| &              | Logical AND operation; returns True if both operands are True. | 
| \|              | Logical OR operation; returns True if at least one operand is True. | 
| !              | Logical NOT operation; negates the truth value of the operand. |
| +              | Performs addition of numbers or arrays.                        |
| -              | Performs subtraction between numbers or arrays.                |
| \*             | Multiplies numbers or arrays.                                  |
| /              | Divides numbers or arrays.                                     |
| %              | Computes the modulus of numbers.                               |
| abs            | Calculates the absolute value.                                 |
| ceil           | Rounds a number up to the nearest integer.                     |
| cosh           | Computes the hyperbolic cosine of a number.                    |
| cos            | Computes the cosine of a number.                               |
| exp            | Calculates the exponential of a number.                        |
| floor          | Rounds a number down to the nearest integer.                   |
| log            | Computes the natural logarithm of a number.                    |
| log10          | Computes the base-10 logarithm of a number.                    |
| log2           | Computes the base-2 logarithm of a number.                     |
| pow            | Raises a number to the power of another number.                |
| round          | Rounds a number to the nearest integer.                        |
| sqrt           | Computes the square root of a number.                          |
| sigmoid        | Applies the sigmoid function.                                  |
| sinh           | Computes the hyperbolic sine of a number.                      |
| sin            | Computes the sine of a number.                                 |
| tanh           | Computes the hyperbolic tangent of a number.                   |
| avg            | Calculates the average of a set of numbers.                    |
| max            | Finds the maximum value in a set of numbers.                   |
| min            | Finds the minimum value in a set of numbers.                   |
| min_max        | Computes both the minimum and maximum values.                  |
| binary         | Converts numbers to binary format.                             |
| bucket         | Classifies data into buckets or ranges.                        |
| box_cox        | Applies the Box-Cox transformation to stabilize variance.      |
| norm           | Computes the norm of a vector.                                 |
| normalize      | Scales data to have zero mean and unit variance.               |
| var            | Computes the variance of a set of numbers.                     |
| z_score        | Computes the z-score of a number.                              |
| std            | Calculates the standard deviation of a set of numbers.         |
| year           | Extracts the year from a date.                                 |
| month          | Extracts the month from a date.                                |
| day            | Extracts the day from a date.                                  |
| curdate        | Retrieves the current date.                                    |
| unix_timestamp | Converts a date to a Unix timestamp.                           |
| from_unixtime  | Converts a Unix timestamp to a date.                           |
| date_add       | Adds a specified time interval to a date.                      |
| date_sub       | Subtracts a specified time interval from a date.               |
| datediff       | Computes the difference between two dates.                     |
| datediff       | Alternate name for computing the difference between two dates. |
| concat         | Concatenates strings together.                                 |
| concat_ws      | Concatenates strings with a specified delimiter.               |
| cross          | Computes the Cartesian product of two sets.                    |
| reverse        | Reverses a string.                                             |
| substr         | Extracts a substring from a string.                            |
| upper          | Converts a string to uppercase.                                |
| lower          | Converts a string to lowercase.                                |
| cast           | Converts a value from one type to another.                     |
| to_string      | Converts a value to a string representation.                   |
| topk           | Retrieves the top k elements from a set.                       |
| count          | Counts the number of occurrences of in a vector.               |
| len            | Returns the number of elements in a vector.                    |

## Data Types
Minia supports a range of data types to accommodate various data needs. The following table outlines the supported data types:

| DataType | Description                                      |
| -------- | ------------------------------------------------ |
| 0        | Represents a 64-bit integer                      |
| 1        | Represents a 32-bit floating-point               |
| 2        | Represents a string                              |
| 3        | Represents a vector of 64-bit integers           |
| 4        | Represents a vector of 32-bit floats             |
| 5        | Represents a vector of strings                   |
| 127      | Represents an error state or undefined data type |


FlatBuffers input for features:

Since FlatBuffers does not provide built-in support for map or dictionary-like data structures, we implemented a design strategy that flattens key-value pairs into linear structures, effectively working around this architectural constraint while maintaining serialization efficiency.

```flatbuffers
// features.fbs
// /opt/homebrew/Cellar/flatbuffers/25.2.10/bin/flatc --cpp features.fbs
namespace minia;

table FlatFloatArray {
    value: [float];
}

table FlatFloatValue {
    value: float;
}

table FlatInt64Array {
    value: [int64];
}

table FlatInt64Value {
    value: int64;
}

table FlatStringArray {
    value: [string];
}

table FlatStringValue {
    value: string;
}

table FlatNil {}

union FlatValue {
  FlatInt64Value,
  FlatFloatValue,
  FlatStringValue,
  FlatInt64Array,
  FlatFloatArray,
  FlatStringArray,
  FlatNil
}

table FlatFeature {
  name: string (key);
  value: FlatValue;
}

table FlatFeatures {
  values: [FlatFeature];
}

table FlatMaterial {
  id: string (key);
  features: FlatFeatures;
}

table FlatMaterialCollection {
  version: string;
  meterials: [FlatMaterial];
}


```

## Contributing
Contributions to Minia are welcome! Please feel free to submit issues or pull requests to improve the project.

## License
Minia is licensed under the  AGPL-3.0 License.

## Contact
For more information, please contact uopensail at timepi123@gmail.com.