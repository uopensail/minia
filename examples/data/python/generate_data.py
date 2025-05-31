#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# `Minia` - A C++ tool for feature transformation and hashing
# Copyright (C) 2019 - present Uopensail <timepi123@gmail.com>
# This software is distributed under the GNU Affero General Public License (AGPL3.0)
# For more information, please visit: https://www.gnu.org/licenses/agpl-3.0.html
#
# This program is free software: you are free to redistribute and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Refer to the
# GNU Affero General Public License for more details.
#

import flatbuffers
from minia import (
    FlatFeatures,
    FlatInt64Value,
    FlatFloatValue,
    FlatStringValue,
    FlatInt64Array,
    FlatFloatArray,
    FlatStringArray,
    FlatFeature,
    FlatValue,
)
import random
import string


def generate_random_string(length=10):
    """
    @brief Generate a random string to be used as a key
    @param length The length of the random string to generate (default: 10)
    @return A random string containing letters and digits
    @details Creates a random string using ASCII letters and digits for testing purposes
    """
    return "".join(random.choices(string.ascii_letters + string.digits, k=length))


def create_float_value(builder, value):
    """
    @brief Create a FlatFloatValue object
    @param builder The FlatBuffers builder instance
    @param value The float value to store
    @return Offset of the created FlatFloatValue object
    @details Constructs a FlatFloatValue flatbuffer object with the specified float value
    """
    FlatFloatValue.Start(builder)
    FlatFloatValue.AddValue(builder, value)
    return FlatFloatValue.End(builder)


def create_int64_value(builder, value):
    """
    @brief Create a FlatInt64Value object
    @param builder The FlatBuffers builder instance
    @param value The int64 value to store
    @return Offset of the created FlatInt64Value object
    @details Constructs a FlatInt64Value flatbuffer object with the specified integer value
    """
    FlatInt64Value.Start(builder)
    FlatInt64Value.AddValue(builder, value)
    return FlatInt64Value.End(builder)


def create_string_value(builder, value):
    """
    @brief Create a FlatStringValue object
    @param builder The FlatBuffers builder instance
    @param value The string value to store
    @return Offset of the created FlatStringValue object
    @details Constructs a FlatStringValue flatbuffer object with the specified string value
    """
    str_offset = builder.CreateString(value)
    FlatStringValue.Start(builder)
    FlatStringValue.AddValue(builder, str_offset)
    return FlatStringValue.End(builder)


def create_float_array(builder, values):
    """
    @brief Create a FlatFloatArray object
    @param builder The FlatBuffers builder instance
    @param values List of float values to store in the array
    @return Offset of the created FlatFloatArray object
    @details Constructs a FlatFloatArray flatbuffer object containing the specified float values
    @note Values are added in reverse order due to FlatBuffers stack-based construction
    """
    FlatFloatArray.StartValueVector(builder, len(values))
    for val in reversed(values):
        builder.PrependFloat32(val)
    values_offset = builder.EndVector()
    FlatFloatArray.Start(builder)
    FlatFloatArray.AddValue(builder, values_offset)
    return FlatFloatArray.End(builder)


def create_int64_array(builder, values):
    """
    @brief Create a FlatInt64Array object
    @param builder The FlatBuffers builder instance
    @param values List of int64 values to store in the array
    @return Offset of the created FlatInt64Array object
    @details Constructs a FlatInt64Array flatbuffer object containing the specified integer values
    @note Values are added in reverse order due to FlatBuffers stack-based construction
    """
    FlatInt64Array.StartValueVector(builder, len(values))
    for val in reversed(values):
        builder.PrependInt64(val)
    values_offset = builder.EndVector()
    FlatInt64Array.Start(builder)
    FlatInt64Array.AddValue(builder, values_offset)
    return FlatInt64Array.End(builder)


def create_string_array(builder, values):
    """
    @brief Create a FlatStringArray object
    @param builder The FlatBuffers builder instance
    @param values List of string values to store in the array
    @return Offset of the created FlatStringArray object
    @details Constructs a FlatStringArray flatbuffer object containing the specified string values
    @note String offsets are created first, then added in reverse order due to FlatBuffers construction
    """
    str_offsets = []
    for val in values:
        str_offsets.append(builder.CreateString(val))

    FlatStringArray.StartValueVector(builder, len(values))
    for offset in reversed(str_offsets):
        builder.PrependUOffsetTRelative(offset)
    values_offset = builder.EndVector()
    FlatStringArray.Start(builder)
    FlatStringArray.AddValue(builder, values_offset)
    return FlatStringArray.End(builder)


def create_value_feature(builder, column, value_type, value_offset):
    """
    @brief Create a FlatFeature object
    @param builder The FlatBuffers builder instance
    @param column The column name of this feature
    @param value_type The type enumeration of the wrapped value
    @param value_offset The offset of the value object to wrap
    @return Offset of the created FlatFeature object
    @details Creates a wrapper that encapsulates a value with its type information
    """
    str_offset = builder.CreateString(column)
    FlatFeature.Start(builder)
    FlatFeature.AddName(builder, str_offset)
    FlatFeature.AddValue(builder, value_offset)
    FlatFeature.AddValueType(builder, value_type)
    return FlatFeature.End(builder)


def create_feature_data(builder, column, value_type):
    """
    @brief Create a feature with randomly generated data based on type
    @param builder The FlatBuffers builder instance
    @param column The column name of this feature
    @param value_type Integer representing the type of value to create (1-6)
    @return Offset of the created FlatFeature object
    @details Creates different types of values based on value_type:
             - 1: Int64Value with random integer
             - 2: FloatValue with random float
             - 3: StringValue with random string
             - 4: Int64Array with random integers
             - 5: FloatArray with random floats
             - 6: StringArray with random strings
    """
    if value_type == 1:  # Int64Value
        value = random.randint(-10000, 10000)
        obj = create_int64_value(builder, value)
        field_type_enum = FlatValue.FlatValue.FlatInt64Value

    elif value_type == 2:  # FloatValue
        value = random.uniform(-100.0, 100.0)
        obj = create_float_value(builder, value)
        field_type_enum = FlatValue.FlatValue.FlatFloatValue

    elif value_type == 3:  # StringValue
        value = generate_random_string(random.randint(5, 15))
        obj = create_string_value(builder, value)
        field_type_enum = FlatValue.FlatValue.FlatStringValue

    elif value_type == 4:  # Int64Array
        array_size = random.randint(3, 10)
        values = [random.randint(-1000, 1000) for _ in range(array_size)]
        obj = create_int64_array(builder, values)
        field_type_enum = FlatValue.FlatValue.FlatInt64Array

    elif value_type == 5:  # FloatArray
        array_size = random.randint(3, 10)
        values = [random.uniform(-100.0, 100.0) for _ in range(array_size)]
        obj = create_float_array(builder, values)
        field_type_enum = FlatValue.FlatValue.FlatFloatArray

    elif value_type == 6:  # StringArray
        array_size = random.randint(3, 7)
        values = [
            generate_random_string(random.randint(3, 10)) for _ in range(array_size)
        ]
        obj = create_string_array(builder, values)
        field_type_enum = FlatValue.FlatValue.FlatStringArray

    # Create FlatFeature
    return create_value_feature(builder, column, field_type_enum, obj)


def create_features(num_fields=6):
    """
    @brief Create a FlatFeatures object with randomly generated field data
    @param num_fields Number of fields to generate (default: 6)
    @return Serialized FlatBuffers data as bytes
    @details Creates a FlatFeatures object containing key-value pairs where:
             - Keys are generated as "col_0", "col_1", etc.
             - Values are randomly generated based on cycling through data types 1-6
             The function creates the complete FlatBuffers structure and returns serialized data
    @note The data type cycles through 1-6, with 0 mapped to 6 to avoid invalid type
    """
    builder = flatbuffers.Builder(1024)

    # Create field wrapper arrays
    field_wrapper_offsets = []
    for i in range(num_fields):
        dtype = i % 6
        if dtype == 0:
            dtype = 6
        field_wrapper_offsets.append(create_feature_data(builder, f"col_{i}", dtype))

    # Add field wrappers to values vector
    FlatFeatures.StartValuesVector(builder, len(field_wrapper_offsets))
    for offset in reversed(field_wrapper_offsets):
        builder.PrependUOffsetTRelative(offset)
    fields_vector = builder.EndVector()

    # Create the final FlatFeatures object
    FlatFeatures.Start(builder)
    FlatFeatures.AddValues(builder, fields_vector)
    features = FlatFeatures.End(builder)

    builder.Finish(features)
    return builder.Output()


if __name__ == "__main__":
    """
    @brief Main execution block
    @details Generates sample feature data and writes it to a binary file named 'data.bin'
    """
    data = create_features()
    with open('../data.bin', 'wb') as f:
        f.write(data)
