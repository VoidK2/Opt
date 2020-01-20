project(Opt)
#set(Data_Structure_file "Src/DataStructure/*.C" "Src/DataStructure/*.h")
#set(Main_file "Src/Main/*.C" "Src/Main/*.h")
#set(Method_file "Src/Method/*.C" "Src/Method/*.h")
#set(Problem_file "Src/Problem/*.C" "Src/Problem/*.h")
#set(RNG_file "Src/RNG/*.C" "Src/RNG/*.h")
#set(Control_file "Control.C" "Control.h")
#add_library(Opt Src/DataStructure/Matrix.C
#        Src/DataStructure/Sample.C
#        Src/DataStructure/Solution.C
#        Src/Main/Control.C
#        Src/Method/CrossEntropy.C
#        Src/Method/Method.C
#        Src/Problem/OneMax.C
#        Src/Problem/Kmedian.C
#        Src/Problem/Problem.C
#        Src/RNG/RNG.C
#        Control.C)
add_executable(Opt main.cpp)
#add_library(Opt Control.C Src/DataStructure/Matrix.C )