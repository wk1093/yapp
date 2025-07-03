build/custom/yappc srcyapp/decl_utils.yapp -c -o build/custom  -- -- -c -o build/custom/decl_utils.o
build/custom/yappc srcyapp/visitor.yapp -c -o build/custom  -- -- -c -o build/custom/visitor.o
build/custom/yappc srcyapp/file_writer.yapp -c -o build/custom  -- -- -c -o build/custom/file_writer.o
build/custom/yappc srcyapp/main.yapp -c -o build/custom  -- -- -c -o build/custom/main.o
clang++ -o build/custom/yappc build/custom/decl_utils.o build/custom/visitor.o build/custom/file_writer.o build/custom/main.o -lclang