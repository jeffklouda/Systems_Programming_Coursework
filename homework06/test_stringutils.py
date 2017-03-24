#!/usr/bin/env python2.7

import ctypes
import unittest

# String Utils - Library
#   Explicitly set return types

stringutils = ctypes.CDLL('./libstringutils.so')
stringutils.string_lowercase.restype        = ctypes.c_char_p
stringutils.string_uppercase.restype        = ctypes.c_char_p
stringutils.string_startswith.restype       = ctypes.c_bool
stringutils.string_endswith.restype         = ctypes.c_bool
stringutils.string_chomp.restype            = ctypes.c_char_p
stringutils.string_strip.restype            = ctypes.c_char_p
stringutils.string_reverse.restype          = ctypes.c_char_p
stringutils.string_reverse_words.restype    = ctypes.c_char_p
stringutils.string_translate.restype        = ctypes.c_char_p
stringutils.string_to_integer.restype       = ctypes.c_int

# String Utils - Test Case

class StringUtils(unittest.TestCase):

    def test_00_string_lowercase(self):
        for s in map(ctypes.create_string_buffer, ['', 'abc', 'ABC', 'AbC']):
            target = s.value.lower()
            self.assertTrue(stringutils.string_lowercase(s) == target)

    def test_01_string_uppercase(self):
        for s in map(ctypes.create_string_buffer, ['', 'abc', 'ABC', 'AbC']):
            target = s.value.upper()
            self.assertTrue(stringutils.string_uppercase(s) == target)

    def test_02_string_startswith(self):
        self.assertTrue(stringutils.string_startswith('', ''))
        self.assertTrue(stringutils.string_startswith('abc', ''))
        self.assertTrue(stringutils.string_startswith('abc', 'a'))
        self.assertTrue(stringutils.string_startswith('abc', 'ab'))
        self.assertTrue(stringutils.string_startswith('abc', 'abc'))

        self.assertFalse(stringutils.string_startswith('', 'a'))
        self.assertFalse(stringutils.string_startswith('abc', 'bc'))
        self.assertFalse(stringutils.string_startswith('abc', 'aabc'))
        self.assertFalse(stringutils.string_startswith('abc', ' abc'))

    def test_03_string_endswith(self):
        self.assertTrue(stringutils.string_endswith('', ''))
        self.assertTrue(stringutils.string_endswith('abc', ''))
        self.assertTrue(stringutils.string_endswith('abc', 'c'))
        self.assertTrue(stringutils.string_endswith('abc', 'bc'))
        self.assertTrue(stringutils.string_endswith('abc', 'abc'))

        self.assertFalse(stringutils.string_endswith('', 'a'))
        self.assertFalse(stringutils.string_endswith('abc', 'a'))
        self.assertFalse(stringutils.string_endswith('abc', 'ab'))
        self.assertFalse(stringutils.string_endswith('abc', 'abc '))
        self.assertFalse(stringutils.string_endswith('bc', 'abc '))
    
    def test_04_string_chomp(self):
        self.assertTrue(stringutils.string_chomp('') == '')
        self.assertTrue(stringutils.string_chomp('\n') == '')
        self.assertTrue(stringutils.string_chomp('abc\n') == 'abc')
        self.assertTrue(stringutils.string_chomp('\nabc') == '\nabc')

    def test_05_string_strip(self):
        for s in map(ctypes.create_string_buffer, ['', ' ', ' A', 'A ', ' A ', ' A B ']):
            target = s.value.strip()
            self.assertTrue(stringutils.string_strip(s) == target)

    def test_06_string_reverse(self):
        for s in map(ctypes.create_string_buffer, ['', ' ', ' A', 'A ', ' A ', ' A B ']):
            target= s.value[::-1]
            self.assertTrue(stringutils.string_reverse(s) == target)

    def test_07_string_reverse_words(self):
        tests = (
            ('', ''),
            (' ', ' '),
            (' A', 'A '),
            (' A ', ' A '),
            (' A B', 'B A '),
            ('AB CD', 'CD AB'),
            (' AB CD ', ' CD AB '),
        )
        for s, t in tests:
            self.assertTrue(stringutils.string_reverse_words(s) == t)

    def test_08_string_translate(self):
        self.assertTrue(stringutils.string_translate('', '', '') == '')
        self.assertTrue(stringutils.string_translate('hello', '', '430') == 'hello')
        self.assertTrue(stringutils.string_translate('hello', 'aeo', '') == 'hello')
        self.assertTrue(stringutils.string_translate('hello', 'aeo', '430') == 'h3ll0')
        self.assertTrue(stringutils.string_translate(' hello ', 'aeo', '430') == ' h3ll0 ')
        self.assertTrue(stringutils.string_translate(' hello ', 'aeol', '4301') == ' h3110 ')

    def test_09_string_to_integer(self):
        tests = (
            ('0', 2),
            ('1', 2),
            ('10', 2),
            ('11', 2),
            ('0', 8),
            ('44', 8),
            ('644', 8),
            ('0', 10),
            ('9', 10),
            ('10', 10),
            ('19', 10),
            ('0', 16),
            ('A', 16),
            ('AF', 16),
            ('a', 16),
            ('aF', 16),
        )

        for s, b in tests:
            self.assertTrue(stringutils.string_to_integer(s, b) == int(s, b))

# Main Execution

if __name__ == '__main__':
    unittest.main()
