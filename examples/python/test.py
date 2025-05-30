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

def test():
    data = open("../data/data.bin","rb").read()
    m = pyminia.Minia("../config/config.toml")
    print(m(data))

test()

# output: {'A': -8209, 'B': 9.003742218017578, 'C': 570082033589109458}