# Bài 4: Phân tích ngữ nghĩa (Semantic Analysis)

## Mô tả
Chương trình thực hiện phân tích ngữ nghĩa (semantic analysis) cho ngôn ngữ KPL. Chương trình xây dựng bảng ký hiệu (symbol table) để quản lý các khai báo (hằng, biến, kiểu, hàm, thủ tục) và kiểm tra tính đúng đắn về mặt ngữ nghĩa của chương trình theo các quy tắc đã định nghĩa.

## Yêu cầu
- GCC compiler
- MinGW Make (cho Windows)

## Biên dịch
```bash
cd Bai4
cd incompleted
mingw32-make
```

## Chạy chương trình
```bash
.\symtab
```

## Kết quả mong đợi
Chương trình sẽ in ra cấu trúc bảng ký hiệu với các thông tin:
- Tên chương trình
- Các khai báo hằng số với giá trị
- Các khai báo kiểu dữ liệu
- Các khai báo biến với kiểu
- Các khai báo hàm/thủ tục với tham số và scope lồng nhau

## Cấu trúc file
- `symtab.h` / `symtab.c`: Quản lý bảng ký hiệu
- `debug.h` / `debug.c`: In thông tin debug
- `main.c`: Chương trình test
- `Makefile`: File biên dịch
