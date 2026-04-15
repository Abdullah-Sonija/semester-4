from ortools.sat.python import cp_model

def solve():
    model = cp_model.CpModel()

    s = model.new_int_var(0,9,"S")
    e = model.new_int_var(0,9,"E")
    n = model.new_int_var(0,9,"N")
    d = model.new_int_var(0,9,"D")
    m = model.new_int_var(0,9,"M")
    o = model.new_int_var(0,9,"O")
    r = model.new_int_var(0,9,"R")
    y = model.new_int_var(0,9,"Y")

    letters = [s,e,n,d,m,o,r,y]
    model.add_all_different(letters)
    model.add(s != 0)
    model.add(m != 0)

    send = 1000 * s + 100 * e + 10 * n + d
    more = 1000 * m + 100 * o + 10 * r + e
    money = 10000 * m + 1000 * o + 100 * n + 10 * e + y

    model.add(send + more == money )

    solver = cp_model.CpSolver()
    status = solver.solve(model)

    if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
        for letter in letters:
            print(f"{letter.Name()} = {solver.value(letter)}")

        print("\nVerification:")
        print(f"  {solver.Value(s)}{solver.Value(e)}{solver.Value(n)}{solver.Value(d)}")
        print(f"+ {solver.Value(m)}{solver.Value(o)}{solver.Value(r)}{solver.Value(e)}")
        print("-------")
        print(f" {solver.Value(m)}{solver.Value(o)}{solver.Value(n)}{solver.Value(e)}{solver.Value(y)}")
        print("-------")
    else:
        print("No solution found.")

if __name__ == '__main__':
    solve()   
