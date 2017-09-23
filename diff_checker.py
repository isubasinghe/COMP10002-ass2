import os
from os import listdir
import hashlib

IS_HUMAN = False

def get_diff_lines(line1, line2):
    flag = False
    if line1 != line2:
        print("="*78)
        print("\033[44;37m{}\033[m".format(line1))
        print("\033[44;30m{}\033[m".format(line2))
        print("="*78)
        flag = True
    return flag

def get_diff(file1, file2):
    f1_lines = []
    f2_lines = []

    flag = False


    with open(file1, 'r') as f1:
        f1_lines = f1.readlines()
        with open(file2, 'r') as f2:
            f2_lines = f2.readlines()

    if len(f1_lines) != len(f2_lines):
        flag = True

    for i in range(0, max((len(f1_lines), len(f2_lines)))):
        print("-"*78)
        if len(f1_lines) < i:
            print("\033[41;30m{}\033[m".format(f2_lines[i]))
        elif len(f2_lines) < i:
            print("\033[41;37m{}\033[m".format(f1_lines[i]))
        else:
            f1_line = f1_lines[i]
            f2_line = f2_lines[i]
            is_diff_lines = get_diff_lines(f1_line, f2_line)
            if is_diff_lines:
                print("line difference at line = {}".format(i+1))
            flag = flag or is_diff_lines
    
    return flag
            




def main():
    print("red background indicates a line missing mistake")
    print("blue background indicates a line different mistake")
    print("the test cases have a black foreground")
    print("the output cases have a white foreground")

    test_files = listdir('./test_cases/')
    output_files = listdir('./output_cases')

    if len(test_files) != len(output_files):
        print("Exiting the files do not match")
        exit(1)
    flag = False
    for i in range(0, len(test_files)):
        if IS_HUMAN:
            input("""Press <Enter> when you are ready for the next file, warning this process will clear the screen""")
        os.system('cls' if os.name == 'nt' else 'clear')
        if test_files[i].endswith('.txt'):
            flag = flag or get_diff('./test_cases/' + test_files[i], './output_cases/' + test_files[i])
    print("Exiting with:", flag)
    exit(int(flag))
        
    


if __name__ == '__main__':
    main()