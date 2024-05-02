import subprocess as sb
import os

filename="FamilyTree.cpp"

#region Set directory of subprocesses to current directory
# Get the current directory of the Python script
cwd = os.path.dirname(os.path.realpath(__file__))
# cwd = os.getcwd()

# Change directory to the current directory
os.chdir(cwd)
#endregion

def RunTest():
    sb.run(f'g++ -fprofile-arcs -ftest-coverage --coverage -o my_executable {filename}', shell=True) #not sure of the flags or their meaning
    sb.run(f'./my_executable', shell=True) #must execute for coverage to be determined
    sb.run(f'gcov {filename}', shell=True) #This command will generate mycode.cpp.gcov file containing coverage information.
    sb.run(f'genhtml -o coverage_report {filename}', shell=True) #This command will generate an HTML report in the coverage_report directory

def DeleteTestFiles():
    sb.run('find . -name "*.gcov" -type f -delete', shell=True)
    sb.run('find . -name "*.out" -type f -delete', shell=True)
    sb.run('find . -name "*.gcno" -type f -delete', shell=True)
    sb.run('find . -name "*.gcda" -type f -delete', shell=True)

if __name__=="__main__":
    sb.run("pwd")
    DeleteTestFiles()
    RunTest()
    DeleteTestFiles()