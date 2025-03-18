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

m = minia.Minia("../config/config.toml")
features = {
    "label": {"type": 0, "value": 0},
    "C_0": {"type": 2, "value": "68fd1e64"},
    "C_1": {"type": 2, "value": "04e09220"},
    "C_2": {"type": 2, "value": "95e13fd4"},
    "C_3": {"type": 2, "value": "a1e6a194"},
    "C_4": {"type": 2, "value": "25c83c98"},
    "C_5": {"type": 2, "value": "fe6b92e5"},
    "C_6": {"type": 2, "value": "f819e175"},
    "C_7": {"type": 2, "value": "062b5529"},
    "C_8": {"type": 2, "value": "a73ee510"},
    "C_9": {"type": 2, "value": "ab9456b4"},
    "C_10": {"type": 2, "value": "6153cf57"},
    "C_11": {"type": 2, "value": "8882c6cd"},
    "C_12": {"type": 2, "value": "769a1844"},
    "C_13": {"type": 2, "value": "b28479f6"},
    "C_14": {"type": 2, "value": "69f825dd"},
    "C_15": {"type": 2, "value": "23056e4f"},
    "C_16": {"type": 2, "value": "d4bb7bd8"},
    "C_17": {"type": 2, "value": "6fc84bfb"},
    "C_18": {"type": 2, "value": "nan"},
    "C_19": {"type": 2, "value": "nan"},
    "C_20": {"type": 2, "value": "5155d8a3"},
    "C_21": {"type": 2, "value": "nan"},
    "C_22": {"type": 2, "value": "be7c41b4"},
    "C_23": {"type": 2, "value": "ded4aac9"},
    "C_24": {"type": 2, "value": "nan"},
    "C_25": {"type": 2, "value": "nan"},
    "I_0": {"type": 1, "value": 0.0},
    "I_1": {"type": 1, "value": -1.0},
    "I_2": {"type": 1, "value": 19.0},
    "I_3": {"type": 1, "value": 35.0},
    "I_4": {"type": 1, "value": 30251.0},
    "I_5": {"type": 1, "value": 247.0},
    "I_6": {"type": 1, "value": 1.0},
    "I_7": {"type": 1, "value": 35.0},
    "I_8": {"type": 1, "value": 160.0},
    "I_9": {"type": 1, "value": 0.0},
    "I_10": {"type": 1, "value": 1.0},
    "I_11": {"type": 1, "value": 0.0},
    "I_12": {"type": 1, "value": 35.0},
}
v = json.dumps(features)
print(m(v))

# Output: {'x': [20, 30, 40], 'y': [4.4721360206604, 5.4772257804870605, 6.324555397033691], 'z': [20.0, 30.000001907348633, 40.0]}
