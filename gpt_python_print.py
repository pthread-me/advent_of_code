# I DID NOT WRITE THIS, JUST CANT BE BOTHERED WITH WRITING
# A TABLE SCRIPT LOL
import os
import subprocess
import time
import re

def run_programs(base_path):
    results = {}
    
    for day in sorted(os.listdir(base_path), key=lambda x: int(re.match(r'day(\d+)', x).group(1)) if re.match(r'day(\d+)', x) else float('inf')):
        day_path = os.path.join(base_path, day)
        if os.path.isdir(day_path):
            part1_path = os.path.join(day_path, "build", "part1")
            part2_path = os.path.join(day_path, "build", "part2")
            
            day_results = []

            # Check if part1 exists and run it
            if os.path.isfile(part1_path):
                part1_times = []
                
                for _ in range(10):
                    start_time = time.perf_counter()
                    subprocess.run([part1_path], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
                    elapsed_time = time.perf_counter() - start_time
                    part1_times.append(elapsed_time)
                
                part1_slowest = max(part1_times)
                part1_fastest = min(part1_times)
                part1_average = sum(part1_times) / len(part1_times)
                
                day_results.append(('Part 1', part1_fastest, part1_slowest, part1_average))
            
            # Check if part2 exists and run it
            if os.path.isfile(part2_path):
                part2_times = []
                
                for _ in range(10):
                    start_time = time.perf_counter()
                    subprocess.run([part2_path], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
                    elapsed_time = time.perf_counter() - start_time
                    part2_times.append(elapsed_time)
                
                part2_slowest = max(part2_times)
                part2_fastest = min(part2_times)
                part2_average = sum(part2_times) / len(part2_times)
                
                day_results.append(('Part 2', part2_fastest, part2_slowest, part2_average))

            if day_results:
                results[day] = day_results
    
    return results

def generate_markdown_tables(results):
    tables = []
    
    for day, data in results.items():
        table = [
            f"## {day}",
            "| Part | Fastest (s) | Slowest (s) | Average (s) |",
            "| ---- | ------------ | ------------ | ------------ |"
        ]
        for part, fastest, slowest, average in data:
            table.append(f"| {part} | {fastest:.6f} | {slowest:.6f} | {average:.6f} |")
        
        tables.append("\n".join(table))
    
    return "\n\n".join(tables)

def write_to_readme(content):
    with open(f"{base_path}/README.md", "w") as file:
        file.write("# Program Outputs\n")
        file.write("## Execution times for part1 and part2 programs\n\n")
        file.write(content)

if __name__ == "__main__":
    base_path = "2024"
    results = run_programs(base_path)
    markdown_tables = generate_markdown_tables(results)
    write_to_readme(markdown_tables)
    print("Output written to README.md")

