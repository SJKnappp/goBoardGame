@echo on
cls
python setup.py build_ext --inplace
g++ main.cpp -o loop.exe && loop.exe
