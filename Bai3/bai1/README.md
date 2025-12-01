# Bài 3.1 - Parser cho ngôn ngữ KPL

## Mô tả
Parser thực hiện phân tích cú pháp (syntax analysis) cho ngôn ngữ KPL. Chương trình đọc file mã nguồn KPL và kiểm tra tính đúng đắn của cấu trúc chương trình theo ngữ pháp đã định nghĩa.

## Yêu cầu
- GCC compiler
- MinGW Make (cho Windows)

## Biên dịch

```bash
cd Bai3
cd bai1
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
 
```bash
.\parser.exe ..\test\example1.kpl
```

```bash
.\parser.exe ..\test\example2.kpl
```

```bash
.\parser.exe ..\test\example3.kpl
```

```bash
.\parser.exe ..\test\example4.kpl
```

## So sánh với kết quả mong đợi
Kết quả khớp với các file trong thư mục test:
- `result1.txt` - kết quả parsing cho `example1.kpl`
- `result2.txt` - kết quả parsing cho `example2.kpl`
- `result3.txt` - kết quả parsing cho `example3.kpl`
- `result4.txt` - kết quả parsing cho `example4.kpl`

## Cấu trúc thư mục
```
bai1/
├── incompleted/           # Mã nguồn parser
│   ├── parser.c          # Chương trình parser chính
│   ├── scanner.c         # Scanner (lexical analyzer)
│   ├── reader.c          # Đọc file input
│   ├── token.c           # Quản lý token
│   ├── error.c           # Xử lý lỗi
│   ├── charcode.c        # Phân loại ký tự
│   ├── main.c            # Entry point
│   └── Makefile          # Build script
└── test/                 # Test cases và kết quả mong đợi
    ├── example1.kpl      # Test case 1
    ├── result1.txt       # Kết quả mong đợi 1
    ├── example2.kpl      # Test case 2
    ├── result2.txt       # Kết quả mong đợi 2
    └── ...
```

## Tính năng
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
