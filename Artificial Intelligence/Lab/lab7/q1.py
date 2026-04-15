from ortools.sat.python import cp_model

def solve_shift_assignment():
    model = cp_model.CpModel()

    alice = model.NewIntVar(0, 2, 'Alice')
    bob = model.NewIntVar(0, 2, 'Bob')
    charlie = model.NewIntVar(0, 2, 'Charlie')

    model.AddAllDifferent([alice, bob, charlie])
    
    model.Add(alice != 0)

    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
        shifts = {0: 'Morning', 1: 'Afternoon', 2: 'Evening'}
        print(f"Alice   : {shifts[solver.Value(alice)]} Shift ({solver.Value(alice)})")
        print(f"Bob     : {shifts[solver.Value(bob)]} Shift ({solver.Value(bob)})")
        print(f"Charlie : {shifts[solver.Value(charlie)]} Shift ({solver.Value(charlie)})")
    else:
        print("No solution found.")

if __name__ == '__main__':
    solve_shift_assignment()
