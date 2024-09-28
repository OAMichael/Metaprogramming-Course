import random
import subprocess
import os
import shutil

MAX_POINTER_TYPES = 8
NUM_TESTS = 1000
TEST_FILENAME = 'test'
COMPILER = 'g++'

def generateType(num_ptr_types):
    # "*" or "[]" (make at least 1 pointer type)
    type_str = 'char '
    num_arrays = random.randint(0, 1)
    num_pointers = num_ptr_types - num_arrays
    if random.choice([0, 1]) == 1:          # add const or not
        if random.choice([0, 1]) == 1:      # east/west const
            type_str = type_str + 'const '
        else:
            type_str = 'const ' + type_str
            
    for _ in range(num_pointers):
        type_str += '*'
        if random.choice([0, 1]) == 1:
            type_str += 'const '

    # num_arrays is 0 or 1
    if num_arrays == 1:
        type_str += '[]'

    if type_str[-1] == ' ':
        type_str = type_str[:-1]

    return type_str


def compileTest():
    curr_file_dir      = os.path.dirname(os.path.abspath(__file__))
    tmp_dir            = os.path.join(curr_file_dir, 'tmp')
    testqual_file_path = os.path.join(curr_file_dir, '..', 'TestQual.cpp')
    lexer_file_path    = os.path.join(curr_file_dir, '..', 'Lexer.cpp')
    test_file_path     = os.path.join(tmp_dir, f'{TEST_FILENAME}.cpp')
    output_file_path   = os.path.join(tmp_dir, f'{TEST_FILENAME}')

    body = ''
    body += '#include <type_traits>\n'
    body += '#include <iostream>\n\n'
    body += '#include "../../TestQual.h"\n\n'
    body += 'int main() {\n'
    body += 'bool testqual = false;\n'
    body += 'bool compiler = false;\n'
    body += 'unsigned passed_count = 0;\n'
    body += 'std::cout << "Test No.' + ' ' * (len(f"Test {NUM_TESTS}:") - len('Test No.') + 3) + 'Status Testqual Compiler   (T1 -> T2)" << std::endl;\n\n'
    longest_conv_len = 0
    for i in range(NUM_TESTS):
        num_ptr_types = random.randint(1, MAX_POINTER_TYPES)
        T1 = generateType(num_ptr_types)
        T2 = generateType(num_ptr_types)
        body += f'    std::cout << "Test {i + 1}:' + ' ' * (len(str(NUM_TESTS)) - len(str(i + 1)) + 4) + '";\n'
        body += f'    testqual = TestQual::testqual("{T1}", "{T2}");\n'
        body += f'    compiler = std::is_convertible_v<{T1}, {T2}>;\n'
        body +=  '    if (testqual == compiler) { ++passed_count; std::cout << " OK "; } else { std::cout << "FAIL"; }\n'
        body += f'    std::cout << (testqual ? "    true " : "    false");\n'
        body += f'    std::cout << (compiler ? "    true " : "    false");\n'
        body += f'    std::cout << "    ({T1} -> {T2})" << std::endl;\n\n'
        longest_conv_len = max(longest_conv_len, len(f'({T1} -> {T2})'))
    dash_count = len(f"Test {NUM_TESTS}:") + 4 + len(" OK ") + 4 + len("true ") + 4 + len("true ") + 4 + longest_conv_len
    body +=  '    std::cout << "' + '-' * dash_count + '" << std::endl;\n'
    body += f'    std::cout << "Passed tests: " << passed_count << "/{NUM_TESTS}" << std::endl;\n\n'
    body +=  '    return 0;\n'
    body +=  '}\n'

    try:
        if os.path.exists(tmp_dir) and os.path.isdir(tmp_dir):
            shutil.rmtree(tmp_dir)
        os.mkdir(tmp_dir)

        with open(f'{test_file_path}', 'w') as f:
            f.write(body)

        subprocess.run([f'{COMPILER}', f'{test_file_path}', f'{testqual_file_path}', f'{lexer_file_path}', '-o', f'{output_file_path}'])
        subprocess.run([f'{output_file_path}'])
        shutil.rmtree(tmp_dir)
    except:
        shutil.rmtree(tmp_dir)



def main():
    compileTest()
    return 0


if __name__ == "__main__":
    main()
