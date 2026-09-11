import time
def compute(x):
    return x*x- x*x + x*4- x*5 + x + x
def main():
    while True:
        inp = input("Enter number of iterations (or non-number to exit): ")
        if inp.isdigit():
            n = int(inp)
        else:
            print("Non-numeric input. Exiting.")
            break
        x = 1.234
        start = time.perf_counter()
        for _ in range(n):
            compute(x)
        end = time.perf_counter()
        print(f"Time for {n} iterations: {end- start:.6f} seconds")
if __name__ == "__main__":
    main()

