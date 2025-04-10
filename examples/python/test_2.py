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

import json
import minia

"""
# example
[transform]
expressions = ['a = true; b = a and c; d = 5 in [5,6,7]; e = g not in ["a" , "b", "c"]']
features = ['a','b', 'd', 'e']
"""
m = minia.Minia("../config/config_2.toml")
features = {
    "c": {"type": 0, "value": 4},
    "g": {"type": 2, "value": "a"},
}
v = json.dumps(features)
print(m(v))

# Output: {'x': [20, 30, 40], 'y': [4.4721360206604, 5.4772257804870605, 6.324555397033691], 'z': [20.0, 30.000001907348633, 40.0]}
