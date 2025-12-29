# Bài 7: Phân tích ngữ nghĩa với Type Checking (Semantic Analysis with Type Checking)

## Mô tả
Chương trình thực hiện phân tích ngữ nghĩa đầy đủ (semantic analysis) cho ngôn ngữ KPL, bao gồm **type checking** (kiểm tra kiểu dữ liệu). Chương trình xây dựng bảng ký hiệu (symbol table) để quản lý các khai báo và thực hiện các kiểm tra ngữ nghĩa:

- **Xây dựng và quản lý bảng ký hiệu** (symbol table)
- **Quản lý phạm vi** (scope) lồng nhau
- **Kiểm tra khai báo** (declared/undeclared identifiers)
- **Kiểm tra kiểu dữ liệu** (type checking):
  - Kiểm tra tính nhất quán kiểu trong phép gán
  - Kiểm tra kiểu tham số và đối số trong lời gọi hàm/thủ tục
  - Kiểm tra kiểu trong biểu thức số học
  - Kiểm tra kiểu trong điều kiện so sánh
  - Kiểm tra chỉ số mảng và kiểu mảng
  - Kiểm tra kiểu trong vòng lặp FOR
- **Kiểm tra tính hợp lệ** của các đối tượng (lvalue, constant, variable, etc.)

## Yêu cầu
- GCC compiler
- MinGW Make (cho Windows)

## Biên dịch
```bash
cd Bai7/incompleted
mingw32-make clean
mingw32-make
```

## Chạy chương trình
```bash
# Chạy với các file test
.\kplc ..\tests\example1.kpl
.\kplc ..\tests\example2.kpl
.\kplc ..\tests\example3.kpl
.\kplc ..\tests\example4.kpl
.\kplc ..\tests\example5.kpl
.\kplc ..\tests\example6.kpl
```

## Kết quả mong đợi

### Chương trình hợp lệ
Nếu không có lỗi ngữ nghĩa, chương trình sẽ in ra cấu trúc bảng ký hiệu:
- Tên chương trình (Program name)
- Các khai báo hằng số với giá trị (Const name = value)
- Các khai báo kiểu dữ liệu (Type name = Int/Char/Arr)
- Các khai báo biến với kiểu (Var name : type)
- Các khai báo hàm với tham số và kiểu trả về (Function name : returnType)
- Các khai báo thủ tục với tham số (Procedure name)
- Scope lồng nhau được thể hiện bằng indentation (4 spaces)
- Exit code = 0

### Chương trình có lỗi
Nếu phát hiện lỗi ngữ nghĩa, chương trình sẽ báo lỗi với thông tin:
- Loại lỗi (type inconsistency, undeclared identifier, etc.)
- Số dòng và cột gây lỗi
- Exit code ≠ 0

## Ví dụ output

### Example 1 (chương trình đơn giản):
```
Program EXAMPLE1
```

### Example 4 (chương trình phức tạp):
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

### Example với lỗi type (tự tạo):
```kpl
Program Test;
Var a: Integer;
    c: Char;
Begin
  a := 'x';  (* Lỗi: gán char cho int *)
End.
```
Output: `Error at line X, col Y: Type inconsistency`

## Các loại lỗi được phát hiện
- `ERR_TYPE_INCONSISTENCY` - Kiểu không nhất quán
- `ERR_UNDECLARED_IDENT` - Biến/hàm/thủ tục chưa khai báo
- `ERR_UNDECLARED_VARIABLE` - Biến chưa khai báo
- `ERR_UNDECLARED_FUNCTION` - Hàm chưa khai báo
- `ERR_UNDECLARED_PROCEDURE` - Thủ tục chưa khai báo
- `ERR_DUPLICATE_IDENT` - Khai báo trùng lặp
- `ERR_INVALID_LVALUE` - Lvalue không hợp lệ
- `ERR_INVALID_BASICTYPE` - Kiểu cơ bản không hợp lệ
- `ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY` - Tham số và đối số không khớp

## Cấu trúc file

### incompleted/
- `parser.h` / `parser.c`: Parser tích hợp phân tích ngữ nghĩa và type checking
- `semantics.h` / `semantics.c`: **Các hàm kiểm tra kiểu dữ liệu**
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

## Chi tiết các hàm type checking đã hoàn thành

### semantics.c
1. **`checkIntType(Type* type)`** - Kiểm tra type có phải INT không
2. **`checkCharType(Type* type)`** - Kiểm tra type có phải CHAR không
3. **`checkBasicType(Type* type)`** - Kiểm tra type có phải kiểu cơ bản (INT/CHAR) không
4. **`checkArrayType(Type* type)`** - Kiểm tra type có phải ARRAY không
5. **`checkTypeEquality(Type* type1, Type* type2)`** - Kiểm tra 2 type có bằng nhau không (đệ quy cho array)

### parser.c
1. **`compileLValue()`** - Parse lvalue và trả về type của nó
2. **`compileAssignSt()`** - Kiểm tra type consistency trong phép gán
3. **`compileForSt()`** - Kiểm tra biến FOR và expressions phải là INT
4. **`compileArgument()`** - Kiểm tra type của argument khớp với parameter
5. **`compileArguments()`** - Kiểm tra danh sách arguments khớp với parameters
6. **`compileCondition()`** - Kiểm tra 2 vế điều kiện cùng basic type
7. **`compileFactor()`** - Trả về type của factor
8. **`compileIndexes()`** - Kiểm tra indexes và trả về element type

## Tác giả
- Bài tập Compiler Construction
- Ngôn ngữ: KPL (Kid Programming Language)
