# Bài 5: Phân tích ngữ nghĩa (Semantic Analysis)

## Mô tả
Chương trình thực hiện phân tích ngữ nghĩa (semantic analysis) cho ngôn ngữ KPL. Chương trình xây dựng bảng ký hiệu (symbol table) để quản lý các khai báo (hằng, biến, kiểu, hàm, thủ tục) và kiểm tra tính đúng đắn về mặt ngữ nghĩa của chương trình theo các quy tắc đã định nghĩa.

Chương trình tích hợp phân tích ngữ nghĩa vào parser, thực hiện:
- Xây dựng và quản lý bảng ký hiệu (symbol table)
- Quản lý phạm vi (scope) lồng nhau
- Kiểm tra khai báo (declared/undeclared)
- Kiểm tra kiểu dữ liệu (type checking)
- Kiểm tra tính hợp lệ của các đối tượng

## Yêu cầu
- GCC compiler
- MinGW Make (cho Windows)

## Biên dịch
```bash
cd Bai5/bai1/incompleted
mingw32-make
```

## Chạy chương trình
```bash
# Chạy với file input cụ thể
.\kplc ..\tests\example1.kpl
.\kplc ..\tests\example2.kpl
.\kplc ..\tests\example3.kpl
.\kplc ..\tests\example4.kpl
.\kplc ..\tests\example5.kpl
.\kplc ..\tests\example6.kpl
```

## Kết quả mong đợi
Chương trình sẽ in ra cấu trúc bảng ký hiệu với các thông tin:
- Tên chương trình
- Các khai báo hằng số với giá trị (Const name = value)
- Các khai báo kiểu dữ liệu (Type name = Int/Char/Arr)
- Các khai báo biến với kiểu (Var name : type)
- Các khai báo hàm với tham số và kiểu trả về (Function name : returnType)
- Các khai báo thủ tục với tham số (Procedure name)
- Scope lồng nhau được thể hiện bằng indentation (4 spaces)

### Ví dụ output cho example4.kpl:
```
Program EXAMPLE4
    Const MAX = 10
    Type T = Int
    Var A : Arr(10,Int)
    Var N : Int
    Var CH : Char
    Procedure INPUT
        Var I : Int
        Var TMP : Int

    Procedure OUTPUT
        Var I : Int

    Function SUM : Int
        Var I : Int
        Var S : Int
```

## Cấu trúc file

### incompleted/
- `parser.h` / `parser.c`: Parser tích hợp phân tích ngữ nghĩa
- `symtab.h` / `symtab.c`: Quản lý bảng ký hiệu
- `debug.h` / `debug.c`: In thông tin debug bảng ký hiệu
- `scanner.h` / `scanner.c`: Phân tích từ vựng
- `token.h` / `token.c`: Quản lý token
- `reader.h` / `reader.c`: Đọc file nguồn
- `charcode.h` / `charcode.c`: Xử lý ký tự
- `error.h` / `error.c`: Xử lý lỗi
- `main.c`: Chương trình chính
- `Makefile`: File biên dịch

### tests/
- `example1.kpl` - Chương trình đơn giản
- `example2.kpl` - Factorial với hàm đệ quy
- `example3.kpl` - Tower of Hanoi với thủ tục
- `example4.kpl` - Mảng và các thủ tục/hàm
- `example5.kpl` - Nested scope
- `example6.kpl` - Declarations phức tạp
