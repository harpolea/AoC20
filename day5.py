import numpy as np
import sys

def find_ids(passes):
    ids = set()

    for p in passes:
        rows = [0, 127]
        columns = [0, 7]
        for r in p[:8]:
            if r == 'F':
                rows[1] = (rows[1] - rows[0] - 1) / 2 + rows[0]
            else:
                rows[0] = (rows[1] - rows[0] + 1) / 2 + rows[0]

            if (rows[0] == rows[1]):
                break

        for c in p[-3:]:
            if c == 'L':
                columns[1] = (columns[1] - columns[0] - 1) / 2 + columns[0]
            else:
                columns[0] = (columns[1] - columns[0] + 1) / 2 + columns[0]
            
            if (columns[0] == columns[1]):
                break

        ids.add(int(rows[0] * 8 + columns[0]))

    return ids

def find_missing_seat(ids):
    for i in range(max(ids)):
        if i not in ids and (i-1 in ids and i+1 in ids):
            return i

if __name__ == "__main__":
    with open(sys.argv[1]) as f:
        passes = f.readlines()
        passes = [l.replace('\n', '') for l in passes]

        ids = find_ids(passes)

        print(f'Max id = {max(ids)}')

        missing_id = find_missing_seat(ids)

        print(f'Missing id = {missing_id}')