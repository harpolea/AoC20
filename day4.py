import numpy as np
import sys
import re

def process_batch_file(f):
    dat = f.read().split('\n\n')
    dat = [l.replace('\n', ' ') for l in dat]
    r = re.compile(r'(\w+):([\w#]+)')

    required_fields = set(['byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid'])

    n_valid = 0

    for passport in dat:
        fields = set()
        for m in re.finditer(r, passport):
            fields.add(m.group(1))

        if fields.issuperset(required_fields):
            n_valid += 1

    new_n_valid = 0

    for passport in dat:
        fields = set()
        valid = True
        for m in re.finditer(r, passport):
            fields.add(m.group(1))

            # check birth year
            if m.group(1) == 'byr':
                if int(m.group(2)) < 1920 or int(m.group(2)) > 2002:
                    valid = False
                    break 

            # check issue year 
            if m.group(1) == 'iyr':
                if int(m.group(2)) < 2010 or int(m.group(2)) > 2020:
                    valid = False
                    break 

            # check expiration year 
            if m.group(1) == 'eyr':
                if int(m.group(2)) < 2020 or int(m.group(2)) > 2030:
                    valid = False
                    break 

            # check height
            if m.group(1) == 'hgt':
                height = m.group(2)
                if height[-2:] == 'cm':
                    if int(height[:-2]) < 150 or int(height[:-2]) > 193:
                        valid = False
                        break 
                elif height[-2:] == 'in':
                    if int(height[:-2]) < 59 or int(height[:-2]) > 76:
                        valid = False
                        break 
                else:
                    valid = False
                    break 

            # check hair colour 
            if m.group(1) == 'hcl':
                hcl = m.group(2)

                rr = re.compile(r'#[0-9a-z]{6}')
                if not re.fullmatch(rr, hcl):
                    valid = False
                    break

            # check eye colour 
            if m.group(1) == 'ecl':
                if not (m.group(2) in ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth']):
                    valid = False
                    break

            # check passport id 
            if m.group(1) == 'pid':
                if not re.fullmatch(re.compile(r'\d{9}'), m.group(2)):
                    valid = False
                    break

        if fields.issuperset(required_fields) and valid:
            new_n_valid += 1

    return n_valid, new_n_valid


if __name__ == "__main__":
    with open(sys.argv[1]) as f:
        n, m = process_batch_file(f)
        print(f'There are {n} valid passports')
        print(f'There are {m} valid passports')
