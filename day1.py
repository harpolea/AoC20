import numpy as np
import sys

def expenses(filename):

    with open(filename) as f:
        entries = np.loadtxt(f, 'int') 
        
        for i, e in enumerate(entries):
            for ee in entries[i+1:]:
                if e + ee == 2020:
                    return e * ee

def triple_expenses(filename):

    with open(filename) as f:
        entries = np.loadtxt(f, 'int') 
        
        for i, e in enumerate(entries):
            for j, ee in enumerate(entries[i+1:]):
                for k, eee in enumerate(entries[j+1:]):
                    if e + ee + eee == 2020:
                        return e * ee * eee

if __name__ == "__main__":
    print(f'Double product = {expenses(sys.argv[1])}')
    print(f'Triple product = {triple_expenses(sys.argv[1])}')