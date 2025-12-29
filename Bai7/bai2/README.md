# Bài tập KPL - Bai7/bai2

## Mô tả
Thư mục này chứa các bài tập viết chương trình KPL và sử dụng compiler/interpreter để chạy.

## Cấu trúc thư mục
```
Bai7/bai2/
├── kplc.exe          # KPL compiler
├── interpreter.exe   # KPL interpreter
├── program1.kpl      # Bài 1: Tính tổng, hiệu, tích
├── program2.kpl      # Bài 2: Tính tổng các chữ số
└── README.md         # File này
```

## Bài 1: program1.kpl

### Yêu cầu
Viết chương trình KPL để:
- Khai báo 2 biến số nguyên: a và b
- Tính và in ra màn hình:
  - Tổng của a và b
  - Hiệu (a - b)
  - Tích (a * b)

### Cách compile và chạy
```bash
.\kplc.exe program1.kpl program1
```

### Kết quả compilation
```
Program PROGRAM1
    Var A : Int
    Var B : Int
    Var SUM : Int
    Var DIFF : Int
    Var PROD : Int
```

### Giải thích
Chương trình:
- Khai báo 5 biến: a, b (giá trị đầu vào), sum, diff, prod (kết quả)
- Gán giá trị a = 10, b = 5
- Tính sum = a + b = 15
- Tính diff = a - b = 5
- Tính prod = a * b = 50
- In kết quả ra màn hình

## Bài 2: program2.kpl

### Yêu cầu
Viết chương trình KPL để:
- Nhập vào một số nguyên n
- Tính tổng các chữ số của n
- In kết quả ra màn hình

Ví dụ: n = 1234 => in ra 1+2+3+4 = 10

### Cách compile và chạy
```bash
.\kplc.exe program2.kpl program2
```

### Kết quả compilation
```
Program PROGRAM2
    Var N : Int
    Var DIGIT : Int
    Var SUMDIGITS : Int
    Var TEMP : Int
    Var QUOTIENT : Int
```

### Giải thích
Chương trình:
- Nhập số nguyên n từ người dùng sử dụng `READI`
- Sử dụng vòng lặp WHILE để tách từng chữ số:
  - Tính quotient = temp / 10 (phép chia nguyên)
  - Tính digit = temp - quotient * 10 (lấy chữ số cuối)
  - Cộng digit vào sumDigits
  - Cập nhật temp = quotient để loại bỏ chữ số cuối
- In kết quả tổng các chữ số

**Lưu ý**: Chương trình sử dụng phép tính `digit = temp - (temp / 10) * 10` thay vì toán tử modulo `%` vì phiên bản KPL compiler ở Bai7 chưa hỗ trợ toán tử `%`.

## Hướng dẫn sử dụng (Windows)

### Compile chương trình
```bash
.\kplc.exe <input_file.kpl> <output_name>
```

### Chạy chương trình (nếu có interpreter hỗ trợ code generation)
```bash
.\interpreter.exe <output_name>
```

**Lưu ý**: Phiên bản kplc.exe hiện tại trong Bai7 chỉ thực hiện phân tích ngữ nghĩa (semantic analysis) và không sinh ra mã thực thi. Do đó, chỉ có thể kiểm tra tính đúng đắn về mặt cú pháp và ngữ nghĩa của chương trình.

## Kết quả đạt được
- Cả hai chương trình đều compile thành công
- Không có lỗi cú pháp hay ngữ nghĩa
- Các biến được khai báo và sử dụng đúng kiểu dữ liệu
- Logic chương trình chính xác

## Ghi chú kỹ thuật

### Các hàm built-in của KPL được sử dụng:
- `READI`: Đọc một số nguyên từ input (trả về giá trị)
- `READC(var)`: Đọc một ký tự vào biến
- `CALL WRITEI(value)`: In một số nguyên
- `CALL WRITEC(char)`: In một ký tự
- `CALL WRITELN`: In xuống dòng

### Cú pháp KPL quan trọng:
- Keyword viết hoa: `PROGRAM`, `VAR`, `BEGIN`, `END`, `WHILE`, `DO`, `CALL`
- Khai báo biến: `VAR name : Type;`
- Gán giá trị: `variable := expression;`
- Các statement cuối cùng trước `END` không cần dấu `;`
- Comment: `(* comment *)`
