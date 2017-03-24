#!/usr/bin/env python2.7

import ctypes
import os
import re
import unittest

# String Utils - Library
#   Explicitly set return types

stringutils = ctypes.CDLL('./libstringutils.so')
stringutils.string_lowercase.restype        = ctypes.c_char_p
stringutils.string_uppercase.restype        = ctypes.c_char_p
stringutils.string_startswith.restype       = ctypes.c_bool
stringutils.string_endswith.restype         = ctypes.c_bool
stringutils.string_strip.restype            = ctypes.c_char_p
stringutils.string_reverse.restype          = ctypes.c_char_p
stringutils.string_reverse_words.restype    = ctypes.c_char_p
stringutils.string_translate.restype        = ctypes.c_char_p
stringutils.string_to_integer.restype       = ctypes.c_int

# Translate - Test Case

class Translate(unittest.TestCase):
    Strings = (
        '',
        ' ',
        'we are the tide',
        ' wake me up inside ',
        'Hello, World!',
    )

    def do_test(self, source='', target='', flag='', func=None, valgrind=False):
        os.environ['LD_LIBRARY_PATH'] = ':'.join([os.curdir, os.environ['LD_LIBRARY_PATH']])
        for s in map(ctypes.create_string_buffer, Translate.Strings):
            command      = 'echo "{}" | {} ./translate-{} {} {} {} 2>&1'.format(
                    s.value,
                    'valgrind --leak-check=full' if valgrind else '',
                    'dynamic' if valgrind else 'static',
                    flag,
                    source,
                    target
            )
            translation1 = os.popen(command).read()[:-1]
            translation2 = stringutils.string_translate(s, source, target)
            if func:
                translation2 = func(translation2)
            if valgrind:
                errors = int(re.findall('ERROR\s+SUMMARY:\s+([0-9]+)\s+error', translation1)[0])
                self.assertTrue(errors == 0)
            else:
                self.assertTrue(translation1 == translation2)

    def test_00_echo(self):
        self.do_test()

    def test_00_echo_valgrind(self):
        self.do_test(valgrind=True)

    def test_01_translate(self):
        self.do_test('aeio', '4310')

    def test_01_translate_valgrind(self):
        self.do_test('aeio', '4310', valgrind=True)

    def test_02_strip(self):
        self.do_test('aeio', '4310', '-s', stringutils.string_strip)

    def test_02_strip_valgrind(self):
        self.do_test('aeio', '4310', '-s', stringutils.string_strip, valgrind=True)

    def test_03_reverse(self):
        self.do_test('aeio', '4310', '-r', stringutils.string_reverse)

    def test_03_reverse_valgrind(self):
        self.do_test('aeio', '4310', '-r', stringutils.string_reverse, valgrind=True)

    def test_04_reverse_words(self):
        self.do_test('aeio', '4310', '-w', stringutils.string_reverse_words)

    def test_04_reverse_words_valgrind(self):
        self.do_test('aeio', '4310', '-w', stringutils.string_reverse_words, valgrind=True)

    def test_05_lowercase(self):
        self.do_test('aeio', '4310', '-l', stringutils.string_lowercase)

    def test_05_lowercase_valgrind(self):
        self.do_test('aeio', '4310', '-l', stringutils.string_lowercase, valgrind=True)

    def test_06_uppercase(self):
        self.do_test('aeio', '4310', '-u', stringutils.string_uppercase)

    def test_06_uppercase_valgrind(self):
        self.do_test('aeio', '4310', '-u', stringutils.string_uppercase, valgrind=True)

# Main Execution

if __name__ == '__main__':
    unittest.main()
