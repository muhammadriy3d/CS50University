class Interpreter:
    def __init__(self):
        self.variables = {}

    def run(self, code):
        lines = code.split('\n')
        for line in lines:
            self.execute(line)

    def execute(self, line):
        tokens = line.split()
        if len(tokens) == 0:
            return

        if tokens[0] == "PRINT":
            self.print(tokens[1:])
        elif tokens[0] == "SET":
            self.set_variable(tokens[1], tokens[3])
        elif tokens[0] == "GET":
            self.get_variable(tokens[1])
        elif tokens[0] == "exit()":
            quit()

    def print(self, values):
        print(" ".join(values))

    def set_variable(self, name, value):
        self.variables[name] = value

    def get_variable(self, name):
        if name in self.variables:
            print(f"{name} = {self.variables[name]}")
        else:
            print(f"Variable {name} is not defined.")


if __name__ == "__main__":
    interpreter = Interpreter()

    # exit = ['exit()', "^D"]
    while True:
        program = input(">> ")

        # for e in exit:
        #     if program == e:
        #         break

        interpreter.run(program)
