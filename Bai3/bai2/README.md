# Bài 3.2 - Parser mở rộng cho ngôn ngữ KPL

## Mô tả
Parser mở rộng thực hiện phân tích cú pháp (syntax analysis) cho ngôn ngữ KPL với các tính năng mở rộng:
- **REPEAT-UNTIL**: Vòng lặp kiểm tra điều kiện sau khi thực thi
- **Multi-variable Assignment**: Gán nhiều biến cùng lúc

## Yêu cầu
- GCC compiler
- MinGW Make (cho Windows)

## Biên dịch

```bash
cd Bai3
cd bai2
cd incompleted
```
 
```bash
mingw32-make
```

## Chạy chương trình

```bash
.\parser.exe ..\test\<file_name>
```

## Ví dụ

### Test các file example gốc
```bash
.\parser.exe ..\test\example1.kpl
.\parser.exe ..\test\example2.kpl
.\parser.exe ..\test\example3.kpl
.\parser.exe ..\test\example4.kpl
```

### Test tính năng REPEAT-UNTIL
```bash
.\parser.exe ..\test\test_repeat.kpl
```
Kết quả mong đợi: Phải thấy "Parsing a repeat statement ...." và "Repeat statement parsed ...."

### Test tính năng Multi-variable Assignment
```bash
.\parser.exe ..\test\test_multi_assign.kpl
```
Kết quả mong đợi: Phải thấy "Parsing an assign statement ...." và "Assign statement parsed ...."

### Test kết hợp cả 2 tính năng
```bash
.\parser.exe ..\test\test_combined.kpl
```
Kết quả mong đợi: Parse thành công cả 2 tính năng trong cùng 1 file

## Cấu trúc thư mục
```
bai2/
├── incompleted/           # Mã nguồn parser
│   ├── parser.c          # Parser với tính năng mở rộng
│   ├── scanner.c         # Scanner (lexical analyzer)
│   ├── reader.c          # Đọc file input
│   ├── token.c           # Quản lý token (có REPEAT, UNTIL)
│   ├── token.h           # Định nghĩa token types
│   ├── parser.h          # Header của parser
│   ├── error.c           # Xử lý lỗi
│   ├── charcode.c        # Phân loại ký tự
│   ├── main.c            # Entry point
│   └── Makefile          # Build script
└── test/                 # Test cases
    ├── example1.kpl      # Test case gốc 1
    ├── example2.kpl      # Test case gốc 2
    ├── example3.kpl      # Test case gốc 3
    ├── example4.kpl      # Test case gốc 4
    ├── test_repeat.kpl   # Test REPEAT-UNTIL
    ├── test_multi_assign.kpl  # Test multi-variable assignment
    └── test_combined.kpl      # Test kết hợp cả 2 tính năng
```

## Tính năng

### Tính năng cơ bản (từ bai1)
- Phân tích cú pháp chương trình KPL
- Hỗ trợ:
  - Khai báo hằng (CONST)
  - Khai báo kiểu (TYPE)
  - Khai báo biến (VAR)
  - Hàm (FUNCTION) và thủ tục (PROCEDURE)
  - Các câu lệnh: IF-THEN-ELSE, WHILE-DO, FOR-TO-DO
  - Lệnh gọi hàm (CALL)
  - Biểu thức số học và logic
  - Mảng (ARRAY)
- Báo lỗi cú pháp với vị trí dòng và cột

### Tính năng mở rộng (bai2)

#### 1. REPEAT-UNTIL Statement
Cú pháp:
```
REPEAT
  <statement>
UNTIL <condition>
```

Ví dụ:
```kpl
REPEAT
  i := i + 1
UNTIL i = 10
```

**Đặc điểm:**
- Thực thi statement ít nhất 1 lần
- Kiểm tra điều kiện sau khi thực thi
- Lặp lại cho đến khi điều kiện đúng (khác với WHILE)

#### 2. Multi-variable Assignment
Cú pháp:
```
<var1>, <var2>, <var3> := <expr1>, <expr2>, <expr3>
```

Ví dụ:
```kpl
x, y, z := 1, 2, 3;
a, b := x + y, z * 2
```

**Đặc điểm:**
- Gán nhiều biến trong một câu lệnh
- Số lượng biến và expression phải khớp nhau
- Hỗ trợ expression phức tạp ở cả hai vế
