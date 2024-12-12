# I DID NOT WRITE THIS, JUST CANT BE BOTHERED WITH WRITING
# A TABLE SCRIPT LOL
import os
import subprocess
import time

def run_programs(base_path):
    results = []
    
    for day in os.listdir(base_path):
        day_path = os.path.join(base_path, day)
        if os.path.isdir(day_path):
            part1_path = os.path.join(day_path, "build", "part1")
            part2_path = os.path.join(day_path, "build", "part2")
            
            if os.path.isfile(part1_path) and os.path.isfile(part2_path):
                part1_times = []
                part2_times = []
                
                # Run part1 10 times
                for _ in range(10):
                    start_time = time.perf_counter()
                    subprocess.run([part1_path], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
                    elapsed_time = time.perf_counter() - start_time
                    part1_times.append(elapsed_time)
                
                # Run part2 10 times
                for _ in range(10):
                    start_time = time.perf_counter()
                    subprocess.run([part2_path], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
                    elapsed_time = time.perf_counter() - start_time
                    part2_times.append(elapsed_time)
                
                # Calculate statistics
                part1_slowest = max(part1_times)
                part1_fastest = min(part1_times)
                part1_average = sum(part1_times) / len(part1_times)
                
                part2_slowest = max(part2_times)
                part2_fastest = min(part2_times)
                part2_average = sum(part2_times) / len(part2_times)
                
                results.append((day, part1_fastest, part1_slowest, part1_average, part2_fastest, part2_slowest, part2_average))
    
    return results

def generate_makefile_table(results):
    table = [
        "| Day | Part 1 Fastest (s) | Part 1 Slowest (s) | Part 1 Average (s) | Part 2 Fastest (s) | Part 2 Slowest (s) | Part 2 Average (s) |",
        "| --- | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ | ------------------ |"
    ]
    
    for day, part1_fastest, part1_slowest, part1_average, part2_fastest, part2_slowest, part2_average in results:
        table.append(f"| {day} | {part1_fastest:.6f} | {part1_slowest:.6f} | {part1_average:.6f} | {part2_fastest:.6f} | {part2_slowest:.6f} | {part2_average:.6f} |")
    
    return "\n".join(table)

def write_to_readme(base_path, table):
    with open(f'{base_path}/README.md', "w") as file:
        file.write("# Program Outputs\n")
        file.write("## Execution times for part1 and part2 programs\n\n")
        file.write(table)

if __name__ == "__main__":
    base_path = "2024"
    results = run_programs(base_path)
    makefile_table = generate_makefile_table(results)
    write_to_readme(base_path, makefile_table)
    print("Output written to README.md")

