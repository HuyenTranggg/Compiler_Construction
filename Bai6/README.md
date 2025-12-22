# Bài 6 - Semantic Analysis cho ngôn ngữ KPL

## Mô tả
Semantic Analyzer thực hiện phân tích ngữ nghĩa (semantic analysis) cho ngôn ngữ KPL. Chương trình đọc file mã nguồn KPL, kiểm tra tính đúng đắn của cú pháp và thực hiện các kiểm tra ngữ nghĩa như:
- Kiểm tra khai báo identifier
- Kiểm tra phạm vi (scope)
- Kiểm tra tính tương thích của kiểu dữ liệu
- Quản lý bảng ký hiệu (symbol table)

## Yêu cầu
- GCC compiler
- MinGW Make (cho Windows)

## Biên dịch

```bash
cd Bai6
cd incompleted
```
 
```bash
mingw32-make
```

## Chạy chương trình

```bash
.\kplc.exe ..\tests\<file_name>
```

## Ví dụ
 
```bash
.\kplc.exe ..\tests\example1.kpl
```

```bash
.\kplc.exe ..\tests\example2.kpl
```

```bash
.\kplc.exe ..\tests\example3.kpl
```

```bash
.\kplc.exe ..\tests\example4.kpl
```

```bash
.\kplc.exe ..\tests\example5.kpl
```

```bash
.\kplc.exe ..\tests\example6.kpl
```

## So sánh với kết quả mong đợi
Kết quả khớp với các file trong thư mục tests:
- `result1.txt` - kết quả phân tích cho `example1.kpl`
- `result2.txt` - kết quả phân tích cho `example2.kpl`
- `result3.txt` - kết quả phân tích cho `example3.kpl`
- `result4.txt` - kết quả phân tích cho `example4.kpl`
- `result5.txt` - kết quả phân tích cho `example5.kpl`
- `result6.txt` - kết quả phân tích cho `example6.kpl`

### So sánh bằng lệnh (CMD):
```cmd
kplc.exe ..\tests\example1.kpl > output1.txt
fc output1.txt ..\tests\result1.txt
```

### So sánh bằng PowerShell:
```powershell
.\kplc.exe ..\tests\example1.kpl | Out-File output1.txt
Compare-Object (Get-Content output1.txt) (Get-Content ..\tests\result1.txt)
```
*Nếu không có output nghĩa là 2 file giống nhau → test passed*

## Cấu trúc thư mục
```
Bai6/
├── incompleted/           # Mã nguồn semantic analyzer
│   ├── main.c            # Entry point
│   ├── parser.c          # Parser (syntax analyzer)
│   ├── semantics.c       # Semantic analyzer (phân tích ngữ nghĩa)
│   ├── symtab.c          # Symbol table management
│   ├── scanner.c         # Scanner (lexical analyzer)
│   ├── reader.c          # Đọc file input
│   ├── token.c           # Quản lý token
│   ├── error.c           # Xử lý lỗi
│   ├── charcode.c        # Phân loại ký tự
│   ├── debug.c           # Debug utilities
│   └── Makefile          # Build script
└── tests/                # Test cases và kết quả mong đợi
    ├── example1.kpl      # Test case 1
    ├── result1.txt       # Kết quả mong đợi 1
    ├── example2.kpl      # Test case 2
    ├── result2.txt       # Kết quả mong đợi 2
    └── ...
```

## Tính năng

### Phân tích cú pháp (Syntax Analysis)
- Khai báo hằng (CONST)
- Khai báo kiểu (TYPE)
- Khai báo biến (VAR)
- Hàm (FUNCTION) và thủ tục (PROCEDURE)
- Các câu lệnh: IF-THEN-ELSE, WHILE-DO, FOR-TO-DO
- Lệnh gọi hàm/thủ tục (CALL)
- Biểu thức số học và logic
- Mảng (ARRAY)

### Phân tích ngữ nghĩa (Semantic Analysis)
- **Kiểm tra khai báo (Declaration Checking)**
  - Kiểm tra identifier đã được khai báo trước khi sử dụng
  - Phát hiện khai báo trùng lặp trong cùng scope
  
- **Quản lý phạm vi (Scope Management)**
  - Quản lý scope lồng nhau (nested scopes)
  - Tìm kiếm identifier theo thứ tự từ scope hiện tại ra ngoài
  
- **Kiểm tra kiểu (Type Checking)**
  - Kiểm tra tương thích kiểu trong phép gán
  - Kiểm tra kiểu tham số khi gọi hàm/thủ tục
  - Kiểm tra kiểu trong biểu thức
  
- **Bảng ký hiệu (Symbol Table)**
  - Lưu trữ thông tin về constants, types, variables, functions, procedures
  - Hỗ trợ nested scopes
  - Quản lý thuộc tính của từng loại object

## Kiểm tra ngữ nghĩa được thực hiện

### Trong `semantics.c`:
1. `lookupObject()` - Tìm kiếm object trong symbol table
2. `checkFreshIdent()` - Kiểm tra identifier chưa được khai báo trong scope hiện tại
3. `checkDeclaredIdent()` - Kiểm tra identifier đã được khai báo
4. `checkDeclaredConstant()` - Kiểm tra constant đã được khai báo
5. `checkDeclaredType()` - Kiểm tra type đã được khai báo
6. `checkDeclaredVariable()` - Kiểm tra variable đã được khai báo
7. `checkDeclaredFunction()` - Kiểm tra function đã được khai báo
8. `checkDeclaredProcedure()` - Kiểm tra procedure đã được khai báo
9. `checkDeclaredLValueIdent()` - Kiểm tra LValue (biến, tham số, tên hàm)

### Trong `parser.c`:
- Kiểm tra identifier mới khi khai báo constants, types, variables
- Kiểm tra identifier mới khi khai báo functions, procedures, parameters
- Kiểm tra sử dụng constants đã được khai báo
- Kiểm tra sử dụng types đã được khai báo
- Kiểm tra sử dụng variables đã được khai báo
- Kiểm tra gọi procedures đã được khai báo
- Kiểm tra LValue trong phép gán

## Các loại lỗi ngữ nghĩa
- `ERR_UNDECLARED_IDENT` - Identifier chưa được khai báo
- `ERR_UNDECLARED_CONSTANT` - Constant chưa được khai báo
- `ERR_UNDECLARED_TYPE` - Type chưa được khai báo
- `ERR_UNDECLARED_VARIABLE` - Variable chưa được khai báo
- `ERR_UNDECLARED_FUNCTION` - Function chưa được khai báo
- `ERR_UNDECLARED_PROCEDURE` - Procedure chưa được khai báo
- `ERR_DUPLICATE_IDENT` - Khai báo trùng lặp identifier
- `ERR_INVALID_CONSTANT` - Sử dụng không đúng constant
- `ERR_INVALID_TYPE` - Sử dụng không đúng type
- `ERR_INVALID_VARIABLE` - Sử dụng không đúng variable
- `ERR_INVALID_FUNCTION` - Sử dụng không đúng function
- `ERR_INVALID_PROCEDURE` - Sử dụng không đúng procedure
- `ERR_INVALID_IDENT` - Sử dụng không đúng identifier
- `ERR_TYPE_INCONSISTENCY` - Kiểu dữ liệu không tương thích

## Kết quả test
Tất cả 6 test cases đã pass thành công!
