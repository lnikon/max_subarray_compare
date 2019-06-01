import random
import subprocess

def main():
    expr_count = 25

    recursive = "./recursive"
    brute_force = "./brute_force"

    for expr_step in range(1, expr_count):
        numbers = []
        for n in range(1, expr_step + 1):
            numbers.append(random.randint(-100, 100))

        infile = open("input_numbers.txt", 'w')
        infile.write('\n'.join(map(str, numbers)))
        infile.close()

        print("Iteration: " + str(expr_step))

        popen = subprocess.Popen(recursive, stdout=subprocess.PIPE);
        popen.wait()
        output = popen.stdout.read()
        print("Recursive: ", end='')
        print(output)

        popen = subprocess.Popen(brute_force, stdout=subprocess.PIPE);
        popen.wait()
        output = popen.stdout.read()
        print("Brute force: ", end='')
        print(output)
    pass

main()
