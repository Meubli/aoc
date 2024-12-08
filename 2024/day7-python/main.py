
with open("input.txt") as f:
    lines = f.read().splitlines()

ans = 0
for line in lines:
    line = line.strip()
    # parse all numbers in the line. line has the form: '650: 56 56 79' and converts them to int
    check = line.split(":")[0]
    numbers = line.split(":")[1].split(" ")
    numbers = [num for num in numbers if num != ""]
    numbers = [int(num) for num in numbers]
    check = int(check)

    good = False
    for opmask in range(1 << (len(numbers) - 1)):
        result = numbers[0]
        for i in range(1, len(numbers)):
            op = (opmask >> (i - 1)) & 1
            if op == 1:
                result = result * numbers[i]
            else:
                result = result + numbers[i]
        if result == check:
            print(check)
            good = True
            break
    ans += good * check

print('Result: ' + str(ans))
