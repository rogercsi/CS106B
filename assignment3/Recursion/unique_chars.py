import sys


def countUniqueChars(filename, out=False):
    """
    returns number of unique chars in a given textfile

    filename - name of a text file
    """
    char_set = set([])
    with open(filename, 'r') as f:
        for line in f:
            for char in line:
                char_set.add(char)
    if out:
        print("Unique chars:", char_set)
    return len(char_set)


def main():
    if (len(sys.argv) != 2):
        print('Invalid usage: python3 unique_chars.py filename')
        return 1
    else:
        try:
            print("Number of unique chars in {file} is {number}".format(file=sys.argv[1], number=countUniqueChars(sys.argv[1])))
        except FileNotFoundError:
            print("Error: file {filename} not found".format(filename=sys.argv[1]))
            return 1
        return 0


if __name__ == '__main__':
    sys.exit(main())
