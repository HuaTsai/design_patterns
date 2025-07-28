#!/usr/bin/env python3
"""
Gym15 Test Runner Script
Automatically compiles and runs all test cases, generating comparison reports
"""

import sys
import subprocess
import tempfile
import difflib
from pathlib import Path


class Color:
    """Terminal color helper class"""

    GREEN = "\033[92m"
    RED = "\033[91m"
    YELLOW = "\033[93m"
    BLUE = "\033[94m"
    ENDC = "\033[0m"
    BOLD = "\033[1m"


class TestResult:
    """Test result class"""

    def __init__(self, name: str, passed: bool, diff_output: str = ""):
        self.name = name
        self.passed = passed
        self.diff_output = diff_output


def get_project_root() -> Path:
    """Get project root directory"""
    script_dir = Path(__file__).parent.absolute()
    return script_dir.parent  # gym15/.. (WBC directory)


def build_project(project_root: Path) -> bool:
    """Build the project"""
    print(f"{Color.BLUE}🔨 Building project...{Color.ENDC}")

    try:
        # Check if build directory exists
        build_dir = project_root / "build"
        if not build_dir.exists():
            print(
                f"{Color.YELLOW}⚠️  Build directory does not exist, creating...{Color.ENDC}"
            )
            build_dir.mkdir()

            # Execute cmake initialization
            cmake_cmd = ["cmake", "-B", str(build_dir), str(project_root)]
            result = subprocess.run(
                cmake_cmd, cwd=project_root, capture_output=True, text=True
            )
            if result.returncode != 0:
                print(f"{Color.RED}❌ CMake initialization failed:{Color.ENDC}")
                print(result.stderr)
                return False

        # Execute compilation
        nproc_result = subprocess.run(["nproc"], capture_output=True, text=True)
        nproc = nproc_result.stdout.strip() if nproc_result.returncode == 0 else "4"

        build_cmd = ["cmake", "--build", "build", f"-j{nproc}"]
        result = subprocess.run(
            build_cmd, cwd=project_root, capture_output=True, text=True
        )

        if result.returncode == 0:
            print(f"{Color.GREEN}✅ Build successful{Color.ENDC}")
            return True
        else:
            print(f"{Color.RED}❌ Build failed:{Color.ENDC}")
            print(result.stderr)
            return False

    except Exception as e:
        print(f"{Color.RED}❌ Error occurred during build: {e}{Color.ENDC}")
        return False


def find_test_files(data_dir: Path) -> list[tuple[Path, Path]]:
    """Find all test file pairs (.in, .out)"""
    test_pairs = []

    # Use glob to find all .in files
    in_files = list(data_dir.glob("**/*.in"))

    for in_file in in_files:
        # Corresponding .out file
        out_file = in_file.with_suffix(".out")

        if out_file.exists():
            test_pairs.append((in_file, out_file))
        else:
            print(
                f"{Color.YELLOW}⚠️  Cannot find corresponding expected output file: {out_file}{Color.ENDC}"
            )

    return sorted(test_pairs)


def run_test(executable: Path, input_file: Path, expected_file: Path) -> TestResult:
    """Execute a single test"""
    test_name = input_file.relative_to(input_file.parents[1]).as_posix()

    try:
        # Create secure temporary file
        with tempfile.NamedTemporaryFile(
            mode="w+", suffix=".out", delete=False
        ) as temp_file:
            temp_output_path = Path(temp_file.name)

        try:
            # Execute program
            with open(input_file, "r") as inf:
                result = subprocess.run(
                    [str(executable), str(input_file)],
                    stdin=inf,
                    stdout=open(temp_output_path, "w"),
                    stderr=subprocess.PIPE,
                    text=True,
                    timeout=30,  # 30 second timeout
                )

            if result.returncode != 0:
                return TestResult(
                    test_name,
                    False,
                    f"Program execution error (return code: {result.returncode})\n{result.stderr}",
                )

            # Compare output
            with (
                open(expected_file, "r") as exp_f,
                open(temp_output_path, "r") as out_f,
            ):
                expected_lines = exp_f.readlines()
                actual_lines = out_f.readlines()

            # Strip trailing whitespace for comparison
            expected_lines = [line.rstrip() + '\n' for line in expected_lines]
            actual_lines = [line.rstrip() + '\n' for line in actual_lines]
            
            if expected_lines == actual_lines:
                return TestResult(test_name, True)
            else:
                # Generate diff report
                diff = difflib.unified_diff(
                    expected_lines,
                    actual_lines,
                    fromfile=f"expected ({expected_file.name})",
                    tofile=f"actual ({temp_output_path.name})",
                    lineterm="",
                )
                diff_output = "".join(diff)
                return TestResult(test_name, False, diff_output)

        finally:
            # Clean up temporary file
            if temp_output_path.exists():
                temp_output_path.unlink()

    except subprocess.TimeoutExpired:
        return TestResult(test_name, False, "Test execution timeout (>30 seconds)")
    except Exception as e:
        return TestResult(
            test_name, False, f"Error occurred during test execution: {str(e)}"
        )


def print_results_table(results: list[TestResult]):
    """Print test results table"""
    print(f"{Color.BOLD}📊 Test Results Summary{Color.ENDC}")
    print("=" * 70)

    passed_count = sum(1 for r in results if r.passed)
    total_count = len(results)

    print(f"Total test cases: {total_count}")
    print(f"Passed: {Color.GREEN}{passed_count}{Color.ENDC}")
    print(f"Failed: {Color.RED}{total_count - passed_count}{Color.ENDC}")
    print(f"Success rate: {passed_count / total_count * 100:.1f}%")

    print("\n" + "=" * 70)
    print(f"{'Test Name':<60} {'Result':<10}")
    print("-" * 70)

    for result in results:
        status = (
            f"{Color.GREEN}✅ PASS{Color.ENDC}"
            if result.passed
            else f"{Color.RED}❌ FAIL{Color.ENDC}"
        )
        print(f"{result.name:<60} {status}")

    # Show details of failed tests
    failed_tests = [r for r in results if not r.passed]
    if failed_tests:
        print(f"{Color.BOLD}❌ Failed Test Details{Color.ENDC}")
        print("=" * 70)

        for result in failed_tests:
            print(f"{Color.RED}📋 {result.name}{Color.ENDC}")
            print(result.diff_output)


def main():
    """Main function"""
    print(f"{Color.BOLD}🧪 Gym15 Automated Testing System{Color.ENDC}")
    print("=" * 70)

    # Get paths
    project_root = get_project_root()
    gym15_dir = project_root / "gym15"
    data_dir = gym15_dir / "data"
    executable = project_root / "build" / "gym15"

    print(f"Project root: {project_root}")
    print(f"Data directory: {data_dir}")
    print(f"Executable: {executable}")

    # Check if paths exist
    if not data_dir.exists():
        print(f"{Color.RED}❌ Data directory does not exist: {data_dir}{Color.ENDC}")
        return 1

    # Step 1: Build project
    if not build_project(project_root):
        print(f"{Color.RED}❌ Build failed, testing terminated{Color.ENDC}")
        return 1

    # Check if executable exists
    if not executable.exists():
        print(f"{Color.RED}❌ Executable does not exist: {executable}{Color.ENDC}")
        return 1

    # Step 2: Find test files
    print(f"{Color.BLUE}🔍 Searching for test files...{Color.ENDC}")
    test_pairs = find_test_files(data_dir)

    if not test_pairs:
        print(f"{Color.RED}❌ No test files found{Color.ENDC}")
        return 1

    print(f"{Color.GREEN}📋 Found {len(test_pairs)} test cases{Color.ENDC}")

    # Step 3: Execute tests
    print(f"{Color.BLUE}🚀 Starting test execution...{Color.ENDC}\n")
    results = []

    for i, (input_file, expected_file) in enumerate(test_pairs, 1):
        result = run_test(executable, input_file, expected_file)
        results.append(result)

    # Step 4: Display results
    print_results_table(results)

    # Return appropriate exit code
    return 0 if all(r.passed for r in results) else 1


if __name__ == "__main__":
    sys.exit(main())
