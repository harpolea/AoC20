import numpy as np
import sys
import re

def valid_passwords(passwords):

    pattern = re.compile(r'(\d+)-(\d+) (\w): (\w+)')

    n_valid = 0
    new_n_valid = 0

    for line in passwords:
        m = re.search(pattern, line)

        num_min, num_max = m.group(1, 2)
        num_min = int(num_min)
        num_max = int(num_max)
        letter = m.group(3)
        pword = m.group(4)

        n_repeats = pword.count(letter)
        if n_repeats >= num_min and n_repeats <= num_max:
            n_valid += 1

        if ((num_min <= len(pword) and pword[num_min-1] == letter) and (num_max > len(pword) or pword[num_max-1] != letter)) or (pword[num_min-1] != letter and num_max <= len(pword) and pword[num_max-1] == letter):
            new_n_valid += 1

    return n_valid, new_n_valid

if __name__ == "__main__":
    with open(sys.argv[1]) as f:
        password_policies = f.readlines()

        n_valid, new_n_valid = valid_passwords(password_policies)

        print(f'There are {n_valid} valid passwords using the first policy')
        print(f'There are {new_n_valid} valid passwords using the second policy')