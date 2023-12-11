#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Created by panos on 12/10/23
# IDE: PyCharm
testcases = [
    ("horse", "ros", 3),
    ("intention", "execution", 5),
    ("a", "a", 0),
    ("a", "b", 1),
    ("ab", "b", 1),
    ("ab", "a", 1),
    ("ab", "ab", 0),
    ("ab", "ac", 1),
    ("ab", "bc", 2),
    ("ab", "cd", 2),
    ("a" * 4, "b" * 4, 4),
    ("a" * 8, "b" * 8, 8),
    ("a" * 16, "b" * 16, 16),
    ("a" * 32, "b" * 32, 32),
    ("a" * 64, "b" * 64, 64),
    ("a" * 128, "b" * 128, 128),
    ("a" * 256, "b" * 256, 256),
    ("a" * 512, "b" * 512, 512),
    ("a" * 1000, "b" * 1000, 1000),
    ("a" * 10000, "b" * 1000, 10000),
    # ("a" * 10000, "b" * 10000, 10000),
    # ("a" * 100000000, "b" * 100000000, 100000000),
]
