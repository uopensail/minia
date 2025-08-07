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

import pyminia
import time


def test():
    exprs = open("exprs.txt").read().split("\n")
    # exprs = ['lower("HELLO WORLD")','lower(str0)']
    inputs = [f"out{i} = {expr}" for i, expr in enumerate(exprs)]
   
    m = pyminia.Minia(inputs)
    ret = m(
            {
                "int0": {
                    "type": pyminia.DataType.kInt64,
                    "value": 100,
                },
                "int1": {
                    "type": pyminia.DataType.kInt64,
                    "value": 200,
                },
                "f0": {
                    "type": pyminia.DataType.kFloat32,
                    "value": 6.7,
                },
                "f1": {
                    "type": pyminia.DataType.kFloat32,
                    "value": 8.9,
                },
                "int2": {
                    "type": pyminia.DataType.kInt64,
                    "value": 200,
                },
                "int3": {
                    "type": pyminia.DataType.kInt64,
                    "value": 300,
                },
                "f2": {
                    "type": pyminia.DataType.kFloat32,
                    "value": 100,
                },
                "f3": {
                    "type": pyminia.DataType.kFloat32,
                    "value": 100,
                },
                "int4": {
                    "type": pyminia.DataType.kInt64,
                    "value": 400,
                },
                "f4": {
                    "type": pyminia.DataType.kFloat32,
                    "value": 5.6,
                },
                "intlist0": {
                    "type": pyminia.DataType.kInt64s,
                    "value": [1, 2, 3, 4, 5, 6],
                },
                "floatlist0": {
                    "type": pyminia.DataType.kFloat32s,
                    "value": [5.6, 1.2, 1.3, 1.4],
                },
                "str0": {
                    "type": pyminia.DataType.kString,
                    "value": "str0",
                },
                "str1": {
                    "type": pyminia.DataType.kString,
                    "value": "str1",
                },
                "strlist0": {
                    "type": pyminia.DataType.kStrings,
                    "value": ["str1", "str2"],
                },
                "ts": {
                    "type": pyminia.DataType.kInt64,
                    "value": int(time.time()),
                },
            }
        )
    
    for (i, (input, expr)) in enumerate(zip(inputs, exprs)):
        key = f"out{i}"
        if key in ret:
            value = ret[key]
            print(expr, "=", value)
        else:
            print(f"{key} = {expr} {input} error")


test()
