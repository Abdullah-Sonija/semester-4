from ortools.sat.python import cp_model

def solve_production():
    model = cp_model.CpModel()

    laptops = model.new_int_var(10,100,"Laptops")
    phones = model.new_int_var(10,100,"Phones")
    tablets = model.new_int_var(10,100,"Tablets")

    model.add(2*laptops + phones + tablets <= 100)
    model.add(laptops + phones + tablets <= 80)
    model.add(laptops + phones + 2 * tablets <= 120)

    model.maximize(500 * laptops + 300 * phones + 400 * tablets)

    solver = cp_model.CpSolver()
    status = solver.solve(model)

    if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
        print(f"Maximum Total Daily Profit: ${solver.ObjectiveValue():.0f}")
        print("\nUnits to Manufacture:")
        print(f"Laptops : {solver.Value(laptops)}")
        print(f"Phones  : {solver.Value(phones)}")
        print(f"Tablets : {solver.Value(tablets)}")
    else:
        print("No solution found.")

if __name__ == '__main__':
    solve_production()
