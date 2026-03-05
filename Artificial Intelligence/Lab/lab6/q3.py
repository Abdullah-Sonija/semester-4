import random

cost_matrix = [
    [4, 6, 8, 7, 5],
    [7, 5, 6, 8, 4],
    [6, 4, 7, 5, 8],
    [5, 8, 6, 4, 7],
    [8, 6, 5, 7, 4],
    [7, 4, 8, 6, 5],
    [6, 7, 4, 5, 8],
    [5, 6, 7, 8, 4],
    [4, 7, 5, 6, 8],
    [8, 5, 6, 4, 7]
]

def get_cost(chromosome):
    return sum(cost_matrix[task][machine] for task, machine in enumerate(chromosome))

def get_fitness(chromosome):
    return 1 / get_cost(chromosome)

def generate_population(size):
    return [[random.randint(0, 4) for _ in range(10)] for _ in range(size)]

def crossover(parent1, parent2):
    point = random.randint(1, 8)
    return parent1[:point] + parent2[point:]

def mutate(chromosome):
    task = random.randint(0, 9)
    chromosome[task] = random.randint(0, 4)
    return chromosome

def genetic_algorithm(pop_size, generations=100):
    population = generate_population(pop_size)
    best_overall = None
    best_cost_overall = float('inf')
    best_gen = 0

    for gen in range(generations):
        population.sort(key=lambda x: get_fitness(x), reverse=True)
        
        current_best_cost = get_cost(population[0])
        if current_best_cost < best_cost_overall:
            best_cost_overall = current_best_cost
            best_overall = population[0]
            best_gen = gen

        survivors = population[:pop_size // 2]
        next_gen = survivors[:]

        while len(next_gen) < pop_size:
            p1, p2 = random.sample(survivors, 2)
            child = crossover(p1, p2)
            if random.random() < 0.1:
                child = mutate(child)
            next_gen.append(child)
            
        population = next_gen
        
    return best_overall, best_cost_overall, 1/best_cost_overall, best_gen

for size in [10, 30]:
    best_chrom, cost, fitness, gen = genetic_algorithm(size)
    print(f"    Population Size: {size}")
    print(f"Best Chromosome: {best_chrom}")
    print(f"Total Cost: {cost}")
    print(f"Fitness: {fitness:.4f}")
    print(f"Found in Generation: {gen}\n")
